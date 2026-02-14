/* TODO: Add memset, prob into modules*/

#include "drivers/vga/vga.h"
#include "kernel.h"
#include "drivers/UART/UART.h"
#include "modules/GDTIDT/GDT.h"
#include "modules/GDTIDT/IDT.h"
#include "modules/memset/memset.h"

void kernel_start_main(){
  vga_init(VGA_16_BLACK, VGA_16_WHITE);
  initialize_gdt();
  initialize_idt(0x08);
  if(init_UART() != 0){
    vga_16_puts("UART ERROR\n");
    return;
  }
  uint16_t cs_val;
  kernel_main();
}
u32 test[10];
void kernel_main(){
  // asm volatile("int %0" : : "i" (0));

  UART_puts("inited everything\n");
  memset(test, 0xFF,sizeof(test[0])*10);
  UART_puth(test[1]);
  // UART_puti(100012);
  // UART_puth(0xFA2);
}

