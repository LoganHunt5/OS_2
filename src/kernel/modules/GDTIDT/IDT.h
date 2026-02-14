#include "../../inc/stdint.h"

struct idt_entry{
   u16 offset_1;        // offset bits 0..15
   u16 selector;        // a code segment selector in GDT or LDT
   u8  zero;            // unused, set to 0
   u8  type_attributes; // gate type, dpl, and p fields
   u16 offset_2;        // offset bits 16..31
}__attribute__((packed));

struct idtr{
  u16  limit;
  u32  base;
}__attribute__((packed));

void default_handler();

void initialize_idt(uint16_t code_sel);
