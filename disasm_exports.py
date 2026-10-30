import sys

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

path = sys.argv[1]
names = sys.argv[2:]
with open(path, "rb") as handle:
    data = handle.read()
pe = pefile.PE(data=data)
image_base = pe.OPTIONAL_HEADER.ImageBase
exports = {}
for exp in pe.DIRECTORY_ENTRY_EXPORT.symbols:
    if exp.name:
        exports[exp.name.decode()] = exp.address

md = Cs(CS_ARCH_X86, CS_MODE_32)
for name in names:
    rva = exports.get(name)
    print("=" * 80)
    if rva is None:
        print(name, ": NOT EXPORTED")
        continue
    offset = pe.get_offset_from_rva(rva)
    print("%s  rva=0x%x offset=0x%x" % (name, rva, offset))
    code = data[offset:offset + 0x60]
    count = 0
    for insn in md.disasm(code, image_base + rva):
        print("   0x%08x  %-24s %s %s" % (insn.address, insn.bytes.hex(), insn.mnemonic, insn.op_str))
        count += 1
        if insn.mnemonic in ("ret", "retn", "jmp") and count > 2:
            break
        if count > 22:
            break
