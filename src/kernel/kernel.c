#include "inc/vga/vga.h"
#include "inc/kernel/kernel.h"

void kernel_start_main(){
  vga_init(VGA_16_BLACK, VGA_16_WHITE);
  kernel_main();
}
void kernel_main(){
  /*
  for(uint16_t i = 0; i < VGA_TEXT_HEIGHT*50; i ++){
    if(i %2 == 0) {
      vga_set_colors(VGA_16_CYAN, VGA_16_BLACK);
      vga_16_puts("Peed myself\n\0");
    }
    else {
      vga_set_colors(VGA_16_BLACK, VGA_16_WHITE);
      vga_16_puts("Pooped myself\n\0");
    }
  }
  */
  vga_16_puthex(0);
  vga_16_puti(12341);
}

