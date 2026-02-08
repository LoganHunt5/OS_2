#include "inc/vga/vga.h"
#include "inc/kernel/kernel.h"
#include "inc/UART/UART.h"
#include "inc/GDTIDT/GDT.h"

void kernel_start_main(){
  vga_init(VGA_16_BLACK, VGA_16_WHITE);
  initialize_gdt();
  kernel_main();
}
void kernel_main(){

  if(init_UART() != 0){
    vga_16_puts("UART ERROR\n");
    return;
  }
  UART_puts("oOo\n\0");
  UART_puti(100012);
  UART_puth(0xFA2);
}

