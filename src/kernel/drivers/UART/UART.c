#include "UART.h"
#include "../../inc/outxInx.h"
#include "../../inc/stdint.h" 

#define PORT 0x3F8  //COM1

u8 init_UART() {
  outb(PORT+1, 0x0);  // disable all interrupts
  outb(PORT+3, 0x80); // enable Divisor latch
  outb(PORT, 0x0);    // baud high
  outb(PORT, 0x01);   // baud low
  outb(PORT+3, 0x03); // disable divisor latch and set
                                 // word length 8 bit one stop, no parity no break enable
  outb(PORT+2, 0xC7); // Enable FIFO and clear FIFO 14 byte interrupt trigger
  
  outb(PORT+4, 0x1E); // interrupt enable and set loopback for testing
  
  outb(PORT, 0xF1);
  u8 res = inb(PORT);

  if(res != 0xF1) {
    return 1;
  }
  else {
    outb(PORT+4, 0x0F); // disable loopback and set data terminal ready
    return 0;
  }
}

static void put_char(u8 c){
  while((inb(PORT+5) & 0b00100000) == 0); // poll to see if output buffer is full
  outb(PORT,c);
}

void UART_puts(char *c){
  uint16_t i = 0;
  while(c[i] != '\0'){
    put_char(c[i]);
    i++;
  }
}

void UART_puti(u32 i){
  u32 rev = 0;
  u32 mod = 0;
  if(i == 0){
    UART_puts("0\n\0");
  }
  while(i){
    mod = i % 10; 
    rev = rev * 10 + mod;
    i /= 10;
  }
  char c;
  while(rev){
    c = (rev%10)+'0';
    put_char(c);
    rev /=10;
  }
  UART_puts("\n\0");
}

void UART_puth(u32 i){
  char rev[10];
  rev[9] = '\0';
  rev[8] = '\n';
  s32 len = 7;
  u32 mod = 0;
  UART_puts("0x\0");
  if(i == 0){
    UART_puts("00000000\n\0");
    return;
  }
  while(i && len >= 0){
    mod = i % 16;
    if(mod < 10){
      rev[len] = mod + '0';
    } else {
      rev[len] = (mod-10) + 'A';
    }
    i /= 16;
    len--;
  }
  while(len >= 0){
    rev[len] = '0';
    len--;
  }
  UART_puts(rev);

}
