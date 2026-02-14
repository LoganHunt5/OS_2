#include "../../inc/stdint.h"


struct gdt_entry{

  u16 limit;

  u16 base_low;
  u8 base_mid;

  u8 access;
  u8 flags;
  u8 base_high;

} __attribute__((packed));

struct gdtr{
  u16  limit;
  u32  base;
}__attribute__((packed));


void initialize_gdt();

