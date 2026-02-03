#include "inc/vga/vga.h"
#include "inc/kernel/kernel.h"
void kernel_main(){
  vga_init(VGA_16_BLACK, VGA_16_WHITE);
  for(uint16_t i = 0; i < VGA_TEXT_HEIGHT*50; i ++){
    if(i %2 == 0) vga_16_puts("Peed myself\n\0");
    if(i %2 == 1) vga_16_puts("Pooped myself\n\0");
  }
}

