#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "../../inc/stdint.h" 

u8 init_UART();

void UART_puts(char *c);

void UART_puti(u32 i);

void UART_puth(u32 i);

#endif
