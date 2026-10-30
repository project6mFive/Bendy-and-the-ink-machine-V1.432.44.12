import hashlib
import math
import os
import re
import sys

try:
    import pefile
except Exception as exc:
    print("pefile unavailable:", exc)
    pefile = None

SUSPICIOUS_API = re.compile(
    rb"(VirtualAllocEx|WriteProcessMemory|CreateRemoteThread|NtUnmapViewOfSection|"
    rb"SetWindowsHookEx|CreateToolhelp32Snapshot|IsDebuggerPresent|CheckRemoteDebuggerPresent|"
    rb"WinExec|ShellExecuteA?|URLDownloadToFile|InternetOpenA?|HttpSendRequestA?|"
    rb"RegSetValueEx|RegCreateKey|CryptEncrypt|CryptDecrypt|BCryptEncrypt|"
    rb"CryptStringToBinary|AdjustTokenPrivileges|LookupPrivilegeValue|"
    rb"GetAsyncKeyState|SetWindowsHookEx|FindWindowA?|GetForegroundWindow|"
    rb"CreateServiceA?|StartServiceA?|GetTempPathA?|GetWindowsDirectoryA?|"
    rb"SHGetFolderPathA?|CoCreateInstance|SHGetSpecialFolderLocation)",
    re.I,
)

SUSPICIOUS_TEXT = [
    (rb"powershell", "powershell"),
    (rb"cmd\.exe", "cmd.exe"),
    (rb"wscript", "wscript"),
    (rb"cscript", "cscript"),
    (rb"mshta", "mshta"),
    (rb"rundll32", "rundll32"),
    (rb"certutil", "certutil"),
    (rb"bitsadmin", "bitsadmin"),
    (rb"regsvr32", "regsvr32"),
    (rb"schtasks", "schtasks"),
    (rb"CurrentVersion\\Run", "autorun-persistence"),
    (rb"Startup", "startup-folder"),
    (rb"AppData", "appdata"),
    (rb"xmrig", "xmrig"),
    (rb"minerd", "miner"),
    (rb"stratum", "mining-pool"),
    (rb"monero", "monero"),
    (rb"wallet", "wallet"),
    (rb"discord(?:app)?\.com/api/webhooks", "discord-webhook"),
    (rb"api\.telegram\.org", "telegram-c2"),
    (rb"pastebin\.com", "pastebin"),
    (rb"ngrok\.io|ngrok-free\.app", "ngrok-tunnel"),
    (rb"\.onion", "tor-hidden-service"),
    (rb"ransom", "ransom-note"),
    (rb"your files have been encrypted", "ransom-note"),
    (rb"bitcoin|btc|monero|xmr", "crypto-payment"),
    (rb"passwords?\b.{0,20}(steal|dump|grab)", "credential-stealer"),
    (rb"keylog", "keylogger"),
    (rb"webcam", "webcam-spy"),
    (rb"screen ?capture", "screencap"),
    (rb"http://[^\x00\s\"']{6,}", "plain-http-url"),
    (rb"https?://[A-Za-z0-9._-]{6,}", "url"),
    (rb"\b(?:\d{1,3}\.){3}\d{1,3}\b", "ip-address"),
    (rb"eval\s*\(", "eval"),
    (rb"exec\s*\(", "exec"),
    (rb"FromBase64String", "base64-decode"),
    (rb"certutil -decode", "certutil-decode"),
    (rb"-enc(?:odedcommand)?\s+[A-Za-z0-9+/=]{20,}", "encoded-command"),
]

URL_RE = re.compile(rb"https?://[A-Za-z0-9\-._~:/?#\[\]@!$&'()*+,;=%]{6,}", re.I)
B64_RE = re.compile(rb"[A-Za-z0-9+/]{120,}={0,2}")
IP_RE = re.compile(rb"\b(?:\d{1,3}\.){3}\d{1,3}\b")


def entropy(data):
    if not data:
        return 0.0
    counts = [0] * 256
    for byte in data:
        counts[byte] += 1
    total = len(data)
    return -sum((c / total) * math.log2(c / total) for c in counts if c)


def strings(data, minlen=5):
    out = set()
    for match in re.finditer(rb"[\x20-\x7e]{%d,}" % minlen, data):
        out.add(match.group())
    for match in re.finditer(rb"(?:[\x20-\x7e]\x00){%d,}" % minlen, data):
        out.add(match.group().replace(b"\x00", b""))
    return out


def analyze(path):
    print("=" * 100)
    print("FILE:", path)
    try:
        with open(path, "rb") as handle:
            data = handle.read()
    except Exception as exc:
        print("  cannot read:", exc)
        return
    print("  size   :", len(data))
    print("  sha256 :", hashlib.sha256(data).hexdigest())
    print("  md5    :", hashlib.md5(data).hexdigest())

    if pefile is not None:
        try:
            pe = pefile.PE(data=data, fast_load=False)
            print("  machine: 0x%04x  timestamp: %s  subsystem: %s" % (
                pe.FILE_HEADER.Machine,
                pe.FILE_HEADER.TimeDateStamp,
                pe.OPTIONAL_HEADER.Subsystem))
            print("  imagebase: 0x%x  entrypoint: 0x%x  dllchars: 0x%x" % (
                pe.OPTIONAL_HEADER.ImageBase,
                pe.OPTIONAL_HEADER.AddressOfEntryPoint,
                pe.OPTIONAL_HEADER.DllCharacteristics))
            print("  sections:")
            for sec in pe.sections:
                name = sec.Name.rstrip(b"\x00").decode("latin-1")
                raw = sec.get_data()
                print("    %-10s vaddr=0x%-8x vsize=0x%-8x rawsize=0x%-8x entropy=%.3f %s" % (
                    name, sec.VirtualAddress, sec.Misc_VirtualSize, sec.SizeOfRawData,
                    entropy(raw),
                    "EXEC" if sec.Characteristics & 0x20000000 else "",
                ))
            overlay_off = pe.get_overlay_data_start_offset()
            if overlay_off is not None:
                overlay = data[overlay_off:]
                print("  OVERLAY: offset=0x%x size=%d entropy=%.3f" % (
                    overlay_off, len(overlay), entropy(overlay)))
                head = overlay[:16]
                if head[:2] == b"MZ":
                    print("  !! overlay starts with MZ (embedded executable)")
                hits = [t for t in strings(overlay, 8) if SUSPICIOUS_API.search(t)]
                if hits:
                    print("  !! overlay suspicious API strings:", hits[:20])
            imports = []
            api_hits = set()
            if hasattr(pe, "DIRECTORY_ENTRY_IMPORT"):
                for entry in pe.DIRECTORY_ENTRY_IMPORT:
                    dll = entry.dll.decode("latin-1")
                    imports.append(dll)
                    for imp in entry.imports:
                        if imp.name:
                            api_hits.update(m.decode("latin-1") for m in SUSPICIOUS_API.findall(imp.name))
            print("  imports:", ", ".join(imports) if imports else "(none)")
            if api_hits:
                print("  !! suspicious imports:", sorted(api_hits))
            if hasattr(pe, "DIRECTORY_ENTRY_RESOURCE"):
                res_names = []
                for rtype in pe.DIRECTORY_ENTRY_RESOURCE.entries:
                    res_names.append(str(rtype.name or rtype.struct.Id))
                print("  resource types:", ",".join(res_names))
            if pe.is_exe() or pe.FILE_HEADER.Machine in (0x014c, 0x8664):
                cert = getattr(pe.OPTIONAL_HEADER, "DATA_DIRECTORY", None)
                print("  checksum:", pe.OPTIONAL_HEADER.CheckSum)
            pe.close()
        except Exception as exc:
            print("  PE parse failed:", exc)
    else:
        print("  pefile unavailable")

    hits = []
    for pattern, label in SUSPICIOUS_TEXT:
        for match in re.finditer(pattern, data, re.I):
            hits.append((label, match.group()[:120]))
    urls = sorted(set(URL_RE.findall(data)))[:60]
    ips = sorted(set(IP_RE.findall(data)))[:30]
    b64 = [b for b in B64_RE.findall(data) if not b.startswith(b"AAAAAAAA")][:10]

    if hits:
        print("  -- text hits --")
        seen = set()
        for label, snippet in hits:
            key = (label, snippet)
            if key in seen:
                continue
            seen.add(key)
            print("    [%s] %r" % (label, snippet))
    if urls:
        print("  -- urls --")
        for url in urls:
            print("    ", url.decode("latin-1"))
    if ips:
        print("  -- ip-like --")
        for ip in ips:
            print("    ", ip.decode("latin-1"))
    if b64:
        print("  -- long base64-like blobs --")
        for blob in b64:
            print("    ", len(blob), blob[:80].decode("latin-1"), "...")

    embedded = [m.start() for m in re.finditer(rb"MZ", data) if m.start() > 0x200]
    if embedded:
        print("  MZ signatures at:", embedded[:20])


def main():
    targets = sys.argv[1:]
    for target in targets:
        if os.path.isdir(target):
            for root, _dirs, files in os.walk(target):
                for fname in files:
                    analyze(os.path.join(root, fname))
        else:
            analyze(target)


if __name__ == "__main__":
    main()
