#ifndef UART_H
#define UART_H

#include <stdint.h>

uint8_t init_UART();

void UART_puts(char *c);

void UART_puti(uint32_t i);

void UART_puth(uint32_t i);

#endif
