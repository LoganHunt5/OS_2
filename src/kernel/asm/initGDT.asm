bits 32
global load_gdt

section .text

; esp + 4 = _gdtr pointer
load_gdt:
  mov eax, [esp + 4]
  lgdt [eax]
  push 0x08
  push .flush_registers
  retf

  .flush_registers:
    mov     ax, 0x10    ; data selector
    mov     ds, ax
    mov     ss, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    ret
