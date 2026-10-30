import re
import sys

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

path = sys.argv[1]
with open(path, "rb") as handle:
    data = handle.read()

pe = pefile.PE(data=data)
entry_rva = pe.OPTIONAL_HEADER.AddressOfEntryPoint
image_base = pe.OPTIONAL_HEADER.ImageBase
offset = pe.get_offset_from_rva(entry_rva)
print("entry rva 0x%x offset 0x%x imagebase 0x%x" % (entry_rva, offset, image_base))

md = Cs(CS_ARCH_X86, CS_MODE_32)
md.detail = False
code = data[offset:offset + 0x400]
for insn in md.disasm(code, image_base + entry_rva):
    print("  0x%08x  %-28s %s %s" % (insn.address, insn.bytes.hex(), insn.mnemonic, insn.op_str))
    if insn.mnemonic in ("ret", "retn") and insn.address > image_base + entry_rva + 0x40:
        break

print()
print("--- XOR single-byte scan for hidden markers in packed sections ---")
markers = [b"http://", b"https://", b"cmd.exe", b"powershell", b"AppData", b"Run", b"schtasks",
           b"vcredist", b"miner", b"wallet", b"discord", b"telegram", b".exe", b".dll",
           b"Windows\\Startup", b"SOFTWARE\\Microsoft", b"rundll32", b"reg add"]
packed = data
for key in range(0, 256):
    if key == 0:
        continue
    decoded = bytes(byte ^ key for byte in packed)
    for marker in markers:
        idx = decoded.find(marker)
        if idx != -1:
            context = decoded[max(0, idx - 40):idx + 80]
            printable = "".join(chr(c) if 32 <= c < 127 else "." for c in context)
            print("  xor 0x%02x marker %-18s at 0x%x : %s" % (key, marker.decode(), idx, printable))

print()
print("--- raw marker scan (unencrypted) ---")
for marker in markers:
    for match in re.finditer(re.escape(marker), packed):
        idx = match.start()
        context = packed[max(0, idx - 30):idx + 60]
        printable = "".join(chr(c) if 32 <= c < 127 else "." for c in context)
        print("  %-18s at 0x%x : %s" % (marker.decode(), idx, printable))
