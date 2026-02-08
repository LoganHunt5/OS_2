#include <stdint.h>

struct gdt_entry{
  uint8_t base_high;

  uint8_t access;
  uint8_t flags;

  uint16_t base_low;
  uint8_t base_mid;

  uint16_t limit;

} __attribute__((packed));

struct gdtr{
  uint16_t  limit;
  uint32_t  base;
}__attribute__((packed));


void initialize_gdt();

