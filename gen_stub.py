"""Generate a clean, benign 32-bit steam_api.dll stub (C source + .def).

The layout is derived from CSteamworks.dll (Valve Steamworks.NET native shim):
every ISteam* wrapper resolves its target through SteamInternal_ContextInit()
and then indexes an interface vtable stored in the returned context object.
"""
import os
import re
import sys

MAP = sys.argv[1]
OUT_C = sys.argv[2]
OUT_DEF = sys.argv[3]

text = open(MAP, "r", encoding="utf-8-sig", errors="replace").read()

interfaces = {}
current = None
for line in text.splitlines():
    m = re.match(r"/\* context '(0x[0-9a-f]+)' \+ (0x[0-9a-f]+) : interface with (\d+) slots \*/", line.strip())
    if m:
        current = (m.group(1), int(m.group(2), 16))
        interfaces[current] = {}
        continue
    m = re.match(r"ctx (0x[0-9a-f]+)\s+vtable\[\s*(\d+)\]\s+args=(\d+)\s+(\S+)", line.strip())
    if m and current is not None:
        idx = int(m.group(2))
        nargs = int(m.group(3))
        name = m.group(4)
        interfaces[current][idx] = (nargs, name)

MAX_ARGS = max(nargs for slots in interfaces.values() for nargs, _ in slots.values())
print("interfaces:", len(interfaces), "max args:", MAX_ARGS)

# SteamAPI context = the one whose string address is 0x1001fb10 (Steamworks.NET uses "SteamAPI")
API_CTX = None
for key in interfaces:
    if key[0] == "0x1001fb10":
        API_CTX = key
        break
if API_CTX is None:
    raise SystemExit("SteamAPI context not found")

lines = []
lines.append("/*")
lines.append(" * steam_api.dll - clean offline stub for Bendy and the Dark Revival")
lines.append(" *")
lines.append(" * Replaces the unsigned, custom-packed ALI213 'Steam emulator' crack that shipped")
lines.append(" * with the game. The original DLL was packed with encrypted sections, imported")
lines.append(" * WS2_32/WINHTTP/ADVAPI32(RegSetValueEx)/PSAPI and carried registry/persistence")
lines.append(" * and network capability - i.e. it was the malware carrier in the release.")
lines.append(" *")
lines.append(" * This stub implements only the small ABI surface that CSteamworks.dll (the")
lines.append(" * legitimate Valve Steamworks.NET shim) actually calls, returns benign values,")
lines.append(" * performs no network I/O, no registry writes and no file writes.")
lines.append(" */")
lines.append("")
lines.append("#define WIN32_LEAN_AND_MEAN")
lines.append("#include <windows.h>")
lines.append("#include <string.h>")
lines.append("")
lines.append("typedef void (*fn_t)(void);")
lines.append("")
lines.append("/* generic __stdcall stubs: each pops exactly its own argument count */")
for n in range(0, MAX_ARGS + 1):
    params = ", ".join("void* a%d" % i for i in range(n)) if n else "void"
    body = "".join("    (void)a%d;\n" % i for i in range(n))
    lines.append("static int __stdcall stub%d(%s)\n{\n%s    return 0;\n}\n" % (n, params, body))

lines.append("/* --- behaviour the game actually observes ------------------------------- */")
lines.append("static int __stdcall fn_getachievement(const char* name, int* achieved)")
lines.append("{")
lines.append("    (void)name;")
lines.append("    if (achieved != NULL) {")
lines.append("        *achieved = 0;")
lines.append("    }")
lines.append("    return 0;")
lines.append("}")
lines.append("")
lines.append("static int __stdcall fn_dlcinstalled(int appid)")
lines.append("{")
lines.append("    (void)appid;")
lines.append("    return 1;")
lines.append("}")
lines.append("")
lines.append("static int __stdcall fn_getappid(void)")
lines.append("{")
lines.append("    return 622650;")
lines.append("}")
lines.append("")

# special-cased (context name, vtable index) -> implementation
SPECIAL = {
    ("0x1001fb10", 0x14, 6): "fn_getachievement",
    ("0x1001fb10", 0x18, 7): "fn_dlcinstalled",
    ("0x1001fb10", 0x0C, 9): "fn_getappid",
}

vtable_names = {}
for (ctx_name, ctx_off), slots in sorted(interfaces.items(), key=lambda kv: (kv[0][0], kv[0][1])):
    if ctx_name != API_CTX[0]:
        continue
    size = max(slots) + 1
    name = "vtbl_%02x" % ctx_off
    vtable_names[(ctx_name, ctx_off)] = name
    entries = []
    for idx in range(size):
        nargs, fname = slots.get(idx, (0, "(unused)"))
        special = SPECIAL.get((ctx_name, ctx_off, idx))
        if special:
            entries.append("(fn_t)%s" % special)
        else:
            entries.append("(fn_t)stub%d" % nargs)
    lines.append("static fn_t %s[%d] = {" % (name, size))
    for idx, entry in enumerate(entries):
        suffix = "," if idx < len(entries) - 1 else ""
        lines.append("    %s /* %s */%s" % (entry, slots.get(idx, (0, "unused"))[1], suffix))
    lines.append("};")
    lines.append("static fn_t* p_%s = %s;" % (name, name))
    lines.append("")

lines.append("/* context object: CSteamworks reads interface wrappers from fixed BYTE offsets */")
lines.append("#define CTX_SLOTS 0x60")
lines.append("static unsigned char g_ctx[CTX_SLOTS];")
lines.append("static char g_empty_path[1] = { 0 };")
lines.append("static int g_dummy = 0;")
lines.append("")
lines.append("static void ctx_put(unsigned int offset, void* value)")
lines.append("{")
lines.append("    memcpy(g_ctx + offset, &value, sizeof(value));")
lines.append("}")
lines.append("")
lines.append("static void BuildContext(void)")
lines.append("{")
lines.append("    unsigned int i;")
lines.append("    for (i = 0; i + sizeof(void*) <= CTX_SLOTS; i += sizeof(void*)) {")
lines.append("        ctx_put(i, (void*)&g_dummy);")
lines.append("    }")
for (ctx_name, ctx_off), vname in sorted(vtable_names.items(), key=lambda kv: kv[0][1]):
    lines.append("    ctx_put(0x%02X, (void*)&p_%s);" % (ctx_off, vname))
lines.append("}")
lines.append("")

lines.append("BOOL WINAPI DllMain(HINSTANCE inst, DWORD reason, LPVOID reserved)")
lines.append("{")
lines.append("    (void)reserved;")
lines.append("    if (reason == DLL_PROCESS_ATTACH) {")
lines.append("        BuildContext();")
lines.append("    }")
lines.append("    return TRUE;")
lines.append("}")
lines.append("")

EXPORTS = [
    ("SteamAPI_Init", "int", "", "1"),
    ("SteamAPI_Shutdown", "void", "", ""),
    ("SteamAPI_RestartAppIfNecessary", "int", "unsigned int appId", "0"),
    ("SteamAPI_ReleaseCurrentThreadMemory", "void", "", ""),
    ("SteamAPI_RunCallbacks", "void", "", ""),
    ("SteamAPI_IsSteamRunning", "int", "", "0"),
    ("SteamAPI_GetSteamInstallPath", "const char*", "", "g_empty_path"),
    ("SteamAPI_GetHSteamPipe", "unsigned int", "", "0"),
    ("SteamAPI_GetHSteamUser", "unsigned int", "", "0"),
    ("SteamAPI_SetTryCatchCallbacks", "void", "int enabled", ""),
    ("SteamAPI_RegisterCallback", "void", "void* callback, int id", ""),
    ("SteamAPI_UnregisterCallback", "void", "void* callback", ""),
    ("SteamAPI_RegisterCallResult", "void", "void* result, unsigned long long call", ""),
    ("SteamAPI_UnregisterCallResult", "void", "void* result, unsigned long long call", ""),
    ("SteamAPI_WriteMiniDump", "int", "unsigned int code, void* info, unsigned int build", "0"),
    ("SteamAPI_SetMiniDumpComment", "void", "const char* comment", ""),
    ("SteamAPI_UseBreakpadCrashHandler", "int", "const char* ver, const char* date, const char* time, int full, void* ctx, void* cb", "0"),
    ("SteamAPI_SetBreakpadAppID", "void", "unsigned int appId", ""),
    ("Steam_GetHSteamUserCurrent", "unsigned int", "", "0"),
    ("Steam_RunCallbacks", "void", "", ""),
    ("Steam_RegisterInterfaceFuncs", "int", "void* module", "1"),
    ("SteamInternal_CreateInterface", "void*", "const char* version, const char* iface, void** out", "(&g_dummy)"),
    ("SteamInternal_ContextInit", "void*", "const char* name, void* callback", "g_ctx"),
    ("SteamInternal_GameServer_Init", "int", "unsigned int ip, unsigned short port, unsigned short mode, const char* ver", "0"),
    ("SteamGameServer_Init", "int", "unsigned int ip, unsigned short sport, unsigned short gport, unsigned short qport, int mode, const char* ver", "0"),
    ("SteamGameServer_Shutdown", "void", "", ""),
    ("SteamGameServer_RunCallbacks", "void", "", ""),
    ("SteamGameServer_ReleaseCurrentThreadMemory", "void", "", ""),
    ("SteamGameServer_BSecure", "int", "", "0"),
    ("SteamGameServer_GetSteamID", "unsigned long long", "", "0"),
    ("SteamGameServer_GetHSteamPipe", "unsigned int", "", "0"),
    ("SteamGameServer_GetHSteamUser", "unsigned int", "", "0"),
]

for name, rtype, params, retval in EXPORTS:
    arg_names = []
    if params:
        for raw in params.split(", "):
            arg_names.append(raw.split(" ")[-1])
    lines.append("%s __cdecl %s(%s)" % (rtype, name, params if params else "void"))
    lines.append("{")
    for argname in arg_names:
        lines.append("    (void)%s;" % argname)
    if retval:
        lines.append("    return %s;" % retval)
    lines.append("}")
    lines.append("")

with open(OUT_C, "w", encoding="utf-8") as handle:
    handle.write("\n".join(lines))

with open(OUT_DEF, "w", encoding="utf-8") as handle:
    handle.write("EXPORTS\n")
    for name, _rtype, _params, _retval in EXPORTS:
        handle.write("    %s\n" % name)

print("wrote", OUT_C, "and", OUT_DEF)
