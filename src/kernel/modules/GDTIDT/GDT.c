#include "../../inc/GDTIDT/GDT.h"
#include "../../inc/UART/UART.h"
#include <stdint.h>

static struct gdt_entry  _gdt[5]; // 5 is current max number of descriptors
static struct gdtr _gdtr;

extern void load_gdt(uint32_t gdt_ptr);

static void make_gdt_entry(uint64_t i, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags){
  _gdt[i].base_high = (base >> 24) & 0xFF;
  _gdt[i].base_mid = (base >> 16) & 0xFF;
  _gdt[i].base_low = base & 0xFFFF;
  _gdt[i].limit = limit & 0xFFFF;
  _gdt[i].access = access;
  _gdt[i].flags = 0x00;
  _gdt[i].flags |= ((limit >> 16) & 0xF); //segment top 4
  _gdt[i].flags |= (flags & 0xF0); // flags
}

static void setup_load_gdt(){
  load_gdt((uint32_t)&_gdtr);
  // asm volatile("lgdt %0" : : "m"(_gdtr));
}

static void fill_gdtr(){
  _gdtr.limit = sizeof(struct gdt_entry) * 5 - 1; // 5 is number of gdt_entries
  _gdtr.base = (uint32_t)&_gdt[0];
}

void initialize_gdt(){

  fill_gdtr();

  make_gdt_entry(0, 0, 0, 0, 0);   // null
  make_gdt_entry(1, 0, 0xFFFFF, 0b10011011, 0b11000000);   // kernel code
  make_gdt_entry(2, 0, 0xFFFF, 0b10010011, 0b11000000);   // kernel data
  make_gdt_entry(3, 0, 0xFFFF, 0b11111011, 0b11000000);   // user code
  make_gdt_entry(4, 0, 0xFFFF, 0b11110011, 0b11000000);   // user data
  setup_load_gdt();
}
