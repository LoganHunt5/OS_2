#include "IDT.h"
#include <stdbool.h>
#include "../../drivers/UART/UART.h"
#include "../../drivers/vga/vga.h"

#define MAX_INTERRUPTS 256 

typedef void (*irq_handler)();

static struct idt_entry  _idt[MAX_INTERRUPTS]; // 5 is current max number of descriptors
static struct idtr _idtr;
static void fill_idtr();
static void install_idt();

static void install_idt() {
  asm volatile("lidt %0" : : "m"(_idtr));
}

void default_handler(){
  vga_16_clear_screen(); 
  vga_16_puts("Unhandled Exception: Stopping Execution\0");
  UART_puts("Unhandled Exception: Stopping Execution\n\0");
  while(true);
}

static void fill_idtr(){
  _idtr.limit = sizeof(struct idt_entry) * MAX_INTERRUPTS - 1; // 5 is number of gdt_entries
  _idtr.base = (u32)&_idt[0];
}

// fills an interrupt index in ir table
// irq is a function pointer
u32 install_ir(u32 i, u16 sel, u8 flags, irq_handler irq){
  if(i > MAX_INTERRUPTS){
    return 0;
  }
  if(!irq){
    return 0;
  }
  // make sure we have address
  u32 irq_address = (u32)&(*irq);
  
  _idt[i].selector = sel;
  _idt[i].zero = 0;
  _idt[i].type_attributes = (u8)flags;
  _idt[i].offset_1 = (u16)irq_address & 0xFFFF;
  _idt[i].offset_2 = (u16)((irq_address >> 16) & 0xFFFF);
  
  return 0;
}

// sets up idt with default handler in all slots. code sel is our kernel code selector
void initialize_idt(u16 code_sel){
  fill_idtr();

  for(int i = 0; i< MAX_INTERRUPTS; i++){
    install_ir(i, code_sel, 0b10001110, (irq_handler)default_handler);
  }

  install_idt();
}
