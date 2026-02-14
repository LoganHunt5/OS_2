#include "GDT.h"

static struct gdt_entry  _gdt[5]; // 5 is current max number of descriptors
static struct gdtr _gdtr;

extern void load_gdt(u32 gdt_ptr);

static void make_gdt_entry(u32 i, u32 base, u32 limit, u8 access, u8 flags){
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
  load_gdt((u32)&_gdtr);
  // asm volatile("lgdt %0" : : "m"(_gdtr));
}

static void fill_gdtr(){
  _gdtr.limit = sizeof(struct gdt_entry) * 5 - 1; // 5 is number of gdt_entries
  _gdtr.base = (u32)&_gdt[0];
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
