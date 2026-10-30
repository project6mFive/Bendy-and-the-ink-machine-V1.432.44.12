import re
import sys
from collections import defaultdict

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

path = sys.argv[1]
with open(path, "rb") as handle:
    data = handle.read()
pe = pefile.PE(data=data)
image_base = pe.OPTIONAL_HEADER.ImageBase

md = Cs(CS_ARCH_X86, CS_MODE_32)
md.detail = False

slots = defaultdict(dict)
for exp in pe.DIRECTORY_ENTRY_EXPORT.symbols:
    if not exp.name:
        continue
    name = exp.name.decode()
    if not name.startswith("ISteam"):
        continue
    rva = exp.address
    offset = pe.get_offset_from_rva(rva)
    code = data[offset:offset + 0x90]
    insns = list(md.disasm(code, image_base + rva))

    ctx_off = None
    ctx_name = None
    vtbl_idx = None
    vtbl_pos = None
    for pos, insn in enumerate(insns):
        text = "%s %s" % (insn.mnemonic, insn.op_str)
        m = re.match(r"push (0x[0-9a-f]+)$", text)
        if m and ctx_name is None:
            ctx_name = m.group(1)
            continue
        m = re.match(r"mov ecx, dword ptr \[eax(?:\ \+ (0x[0-9a-f]+|\d+))?\]", text)
        if m and ctx_off is None:
            ctx_off = int(m.group(1), 0) if m.group(1) else 0
            continue
        m = re.match(r"mov (?:eax|edx), dword ptr \[eax(?:\ \+ (0x[0-9a-f]+|\d+))?\]", text)
        if m and ctx_off is not None and vtbl_idx is None:
            vtbl_idx = (int(m.group(1), 0) if m.group(1) else 0) // 4
            vtbl_pos = pos
            continue
        if insn.mnemonic in ("call", "jmp") and insn.op_str in ("eax", "edx"):
            break
    if ctx_off is None or vtbl_idx is None:
        continue

    argbytes = 0
    seen_ctx_call = False
    for insn in insns:
        if insn.mnemonic == "call" and "dword ptr [0x" in insn.op_str:
            seen_ctx_call = True
            continue
        if not seen_ctx_call:
            continue
        if insn.mnemonic == "push":
            argbytes += 4
        elif insn.mnemonic in ("call", "jmp") and insn.op_str in ("eax", "edx"):
            break
    slots[(ctx_name, ctx_off)][vtbl_idx] = (name, argbytes // 4)

for key in sorted(slots, key=lambda k: (str(k[0]), k[1])):
    entries = slots[key]
    max_idx = max(entries)
    print("/* context '%s' + 0x%02x : interface with %d slots */" % (key[0], key[1], max_idx + 1))
    for idx in sorted(entries):
        name, nargs = entries[idx]
        print("   ctx 0x%02x  vtable[%3d]  args=%d  %s" % (key[1], idx, nargs, name))
    print()
