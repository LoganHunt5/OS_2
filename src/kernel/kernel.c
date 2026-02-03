#include "inc/vga/vga.h"
#include "inc/kernel/kernel.h"
void kernel_main(){
  vga_init(VGA_16_BLACK, VGA_16_WHITE);
  vga_16_puts("Peed myself\0");
}

