section .text
    global asm_load_GDT;

asm_load_GDT:
    cli
    pusha
    lgdt [gdt_pointer]
    sti
    popa
    jmp 0x08:.reload_registers ; kernel code descriptor is 0x08

  .reload_registers:
    mov   ax, 0x10 ; 0x10 is kernel data descriptor 
    mov   ds, ax
    mov   es, ax
    mov   fs, ax
    mov   gs, ax
    mov   ss, ax
    ret

gdt_start:
    ; null descriptor
    dd 0
    dd 0

    ; kernel code descriptor offset is 0x08

    dw 0xFFFF             ; limit low
    dw 0                  ; base low
    db 0                  ; base middle
    db 0b10011010         ; access bits
    db 0b11001111         ; granularity
    db 0                  ; base high

    ; kernel data descriptor, same except for a 1 in access
    ; tells cpu its a data descrpitor
    dw 0xFFFF             ; limit low
    dw 0                  ; base low
    db 0                  ; base middle
    db 0b10010010         ; access bits
    db 0b11001111         ; granularity
    db 0                  ; base high

    ;user code (offset 0x18 bytes)
    dw 0xFFFF             ; limit low
    dw 0                  ; base low
    db 0                  ; base middle
    db 0b11111010         ; access bits
    db 0b11001111         ; granularity
    db 0                  ; base high

    ;user data (offset 0x18 bytes)

    dw 0xFFFF             ; limit low
    dw 0                  ; base low
    db 0                  ; base middle
    db 0b11110010         ; access bits
    db 0b11001111         ; granularity
    db 0                  ; base high

gdt_end:
gdt_pointer:
      dw  gdt_end - gdt_start - 1
      dd  gdt_start
    ; needs to follow this exact format for lgdt

