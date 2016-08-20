#ifndef __UART_H__
#define __UART_H__
#include <libc.h>

void uart_wait_fifo_empty();
u32 uart_fifo_status();
s32 uart_printf(const char *format, ...);
void uart_putc(u8 byte);
void uart_puts(const char *str);
s8 uart_recv();
s32 uart_handler();
void uart_init();


#endif /* __UART_H__ */
