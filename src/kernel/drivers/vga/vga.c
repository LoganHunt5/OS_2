#include "vga.h"
#include "../../inc/outxInx.h"

static u8 fg = 0;
static u8 bg = 0;
static u16 cursor_pos_x = 0;
static u16 cursor_pos_y = 0;
static void enable_cursor(u8 cursor_start, u8 cursor_end);
static void update_cursor(u16 x, u16 y);
static void scroll_line();

void vga_init(enum vga_16_COLORS back,enum vga_16_COLORS fore) {
  vga_set_colors(back, fore);
  vga_16_clear_screen();
  enable_cursor(12,14);
  update_cursor(0, 0);
}

void vga_16_clear_screen(){
  u16* vga_text_pointer = (u16*) VGA_TEXT_BUFFER;
  u16 blank = (bg << 12)+(' '<<4);
  u16* vga_text_end = VGA_TEXT_WIDTH * 2 * VGA_TEXT_HEIGHT + vga_text_pointer;
  for(u16* i = vga_text_pointer; i < vga_text_end; i++){
    *i = blank; 
  }
  update_cursor(0, 0);
}

void vga_16_goto(u16 x, u16 y){
    cursor_pos_x = x;
    cursor_pos_y = y;
    update_cursor(x, y);
}

/*Start and end are scanlines*/
static void enable_cursor(u8 cursor_start, u8 cursor_end){
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

static void update_cursor(u16 x, u16 y){
  u16 pos= y * VGA_TEXT_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (u8) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (u8) ((pos >> 8) & 0xFF));
}

void vga_disable_cursor(){
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void vga_16_putc(char c){
  u8* vga_text_pointer = (u8*) VGA_TEXT_BUFFER;
  u16 offset = cursor_pos_y*2*VGA_TEXT_WIDTH+cursor_pos_x*2;
  if(c != '\n'){
    *(vga_text_pointer+offset) = c; 
    *(vga_text_pointer+offset+1) = (bg << 4) + fg; 
    cursor_pos_x++;
  }
  if(cursor_pos_x == VGA_TEXT_WIDTH || c == '\n'){
    cursor_pos_x = 0;
    cursor_pos_y++;
    if(cursor_pos_y == VGA_TEXT_HEIGHT) scroll_line();
  }
}

static void scroll_line(){
  cursor_pos_y--;
  update_cursor(cursor_pos_x, cursor_pos_y);
  u16* vga_text_pointer = (u16*) VGA_TEXT_BUFFER;
  u16* vga_text_end = VGA_TEXT_WIDTH * 2 * (VGA_TEXT_HEIGHT-1) + vga_text_pointer;
  for(u16* i = vga_text_pointer; i < vga_text_end; i++){
    *i = *(i+VGA_TEXT_WIDTH); 
  }
}

void vga_16_puts(char* s){
  u16 i = 0;
  while(s[i] != '\0'){
    vga_16_putc(*(s + i));
    i++;
    if(i > 128) return;
  }
  update_cursor(cursor_pos_x, cursor_pos_y);
}

void vga_16_puti(uint32_t i){
  u32 rev = 0;
  u32 mod = 0;
  if(i == 0){
    vga_16_puts("0\n\0");
  }
  while(i){
    mod = i % 10; 
    rev = rev * 10 + mod;
    i /= 10;
  }
  char c;
  while(rev){
    c = (rev%10)+'0';
    vga_16_putc(c);
    rev /=10;
  }
  vga_16_puts("\n\0");
}

void vga_16_puthex(u32 i){
  char rev[10];
  rev[9] = '\0';
  rev[8] = '\n';
  s32 len = 7;
  u32 mod = 0;
  vga_16_puts("0x\0");
  if(i == 0){
    vga_16_puts("00000000\n\0");
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
  vga_16_puts(rev);
}

void vga_set_colors(enum vga_16_COLORS back, enum vga_16_COLORS fore){
  fg = fore;
  bg = back;
}
