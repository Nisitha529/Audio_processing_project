#ifndef __CIRCULAR_BUFFER_H
#define __CIRCULAR_BUFFER_H

#include "uart.h"

#define UART_BUFFER_SIZE 100
#define INIT_VAL         0

typedef enum
{
	DEBUG_PORT     = 0,
	SLAVE_DEV_PORT = 1
}portType;

typedef struct
{
	unsigned char buffer[UART_BUFFER_SIZE];
	volatile uint32_t head;
	volatile uint32_t tail;
}circular_buffer;

void buffer_clear (portType uart);
void buffer_send_string (const char *s, portType uart);
void circular_buffer_init (void);
void buffer_send_byte (const uint8_t *data, int length, portType uart);

#endif
