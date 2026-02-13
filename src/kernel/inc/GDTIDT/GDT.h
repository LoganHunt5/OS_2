#include <stdint.h>


struct gdt_entry{

  uint16_t limit;

  uint16_t base_low;
  uint8_t base_mid;

  uint8_t access;
  uint8_t flags;
  uint8_t base_high;

} __attribute__((packed));

struct gdtr{
  uint16_t  limit;
  uint32_t  base;
}__attribute__((packed));


void initialize_gdt();

