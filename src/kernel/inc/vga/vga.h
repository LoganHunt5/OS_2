#ifndef VGA_H
#define VGA_H

#include "stdint.h"

#define VGA_TEXT_BUFFER 0xB8000
#define VGA_TEXT_WIDTH 80
#define VGA_TEXT_HEIGHT 25

enum vga_16_COLORS {
   VGA_16_BLACK         = 0,
   VGA_16_BLUE          = 1,
   VGA_16_GREEN         = 2,
   VGA_16_CYAN          = 3,
   VGA_16_RED           = 4,
   VGA_16_MAGENTA       = 5,
   VGA_16_BROWN         = 6,
   VGA_16_LIGHT_GRAY    = 7,
   VGA_16_DARK_GRAY     = 8,
   VGA_16_LIGHT_BLUE    = 9,
   VGA_16_LIGHT_GREEN   = 10,
   VGA_16_LIGHT_CYAN    = 11,
   VGA_16_LIGHT_RED     = 12,
   VGA_16_LIGHT_MAGENTA = 13,
   VGA_16_YELLOW        = 14,
   VGA_16_WHITE         = 15
};

void vga_init(enum vga_16_COLORS back,enum vga_16_COLORS fore);

void vga_disable_cursor();

void vga_16_clear_screen();

void vga_16_pch(char c);

void vga_16_puts(char* s);

#endif
