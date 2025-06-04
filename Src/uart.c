#include "uart.h"
#include <stdint.h>

#define  GPIOAEN                 (1U << 0)
#define  GPIOCEN                 (1U << 2)
#define  UART1EN                 (1U << 4)
#define  UART6EN                 (1U << 5)
#define  DBG_UART_BAUDRATE       115200
#define  SLAVE_DEV_UART_BAUDRATE 9600
#define  SYS_FREQ                16000000
#define  APB2_CLK                SYS_FREQ
#define  CR1_TE                  (1U << 3)
#define  CR1_RE                  (1U << 2)
#define  CR1_UE                  (1U << 13)
#define  SR_TXE                  (1U << 7)

static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);
static uint16_t compute_uart_bd (uint32_t periph_clk, uint32_t baudrate);
static void debug_uart_write(int ch);
static void slavedev_uart_write(int ch);

int __io_putchar (int ch)
{
	debug_uart_write(ch);
	return ch;
}

void debug_uart_init (void)
{
	// Enable clock access to GPIOA
	RCC->AHB1ENR  |= GPIOAEN;

	// Set the mode of PA9 to alternate function mode
	GPIOA->MODER  &= ~(1U << 18);
	GPIOA->MODER  |=  (1U << 19);

	// Set the mode of PA10 to alternate function mode
	GPIOA->MODER  &= ~(1U << 20);
	GPIOA->MODER  |=  (1U << 21);

	// Set alternate function type to AF7 (UART1_TX)
	GPIOA->AFR[1] |=  (1U << 4);
	GPIOA->AFR[1] |=  (1U << 5);
	GPIOA->AFR[1] |=  (1U << 6);
	GPIOA->AFR[1] &= ~(1U << 7);

	// Set alternate function type to AF7 (UART1_RX)
	GPIOA->AFR[1] |=  (1U << 8);
	GPIOA->AFR[1] |=  (1U << 9);
	GPIOA->AFR[1] |=  (1U << 10);
	GPIOA->AFR[1] &= ~(1U << 11);

	// Enabling clock access to UART1
	RCC->APB2ENR  |=  UART1EN;

	// Disable UART module
    USART1->CR1   &=  ~CR1_UE;

	// Configure uart baudrate
	uart_set_baudrate(APB2_CLK, DBG_UART_BAUDRATE);

	// Configure transfer direction
    USART1->CR1    =  CR1_TE | CR1_RE;

    // Enable interrupt in NVIC
    NVIC_EnableIRQ(USART1_IRQn);

	// Enable UART module
    USART1->CR1   |=  CR1_UE;
}

void slave_dev_uart_init (void)
{
	// Enable clock access to GPIOC
	RCC->AHB1ENR  |= GPIOCEN;

	// Set the mode of PC6 to alternate function mode
	GPIOC->MODER  &= ~(1U << 12);
	GPIOC->MODER  |=  (1U << 13);

	// Set the mode of PC7 to alternate function mode
	GPIOC->MODER  &= ~(1U << 14);
	GPIOC->MODER  |=  (1U << 15);

	// Set alternate function type to AF7 (UART6_TX)
	GPIOC->AFR[0] |=  (1U << 24);
	GPIOC->AFR[0] |=  (1U << 25);
	GPIOC->AFR[0] |=  (1U << 26);
	GPIOC->AFR[0] &= ~(1U << 27);

	// Set alternate function type to AF7 (UART6_RX)
	GPIOC->AFR[0] |=  (1U << 28);
	GPIOC->AFR[0] |=  (1U << 29);
	GPIOC->AFR[0] |=  (1U << 30);
	GPIOC->AFR[0] &= ~(1U << 31);

	// Enabling clock access to UART6
	RCC->APB2ENR  |=  UART6EN;

	// Disable UART module
    USART6->CR1   &=  ~CR1_UE;

	// Configure uart baudrate
	USART6->BRR    = compute_uart_bd(APB2_CLK, SLAVE_DEV_UART_BAUDRATE);

	// Configure transfer direction
    USART6->CR1    =  CR1_TE | CR1_RE;

    // Enable interrupt in NVIC
    NVIC_EnableIRQ(USART6_IRQn);

	// Enable UART module
    USART6->CR1   |=  CR1_UE;
}

static void debug_uart_write(int ch)
{
	// Make sure transmit data reg is empty
	while (!(USART1->SR & SR_TXE)){}
	// Write to the transmit data reg
	USART1->DR = (ch & 0xFF);
}

static void slavedev_uart_write(int ch)
{
	// Make sure transmit data reg is empty
	while (!(USART6->SR & SR_TXE)){}
	// Write to the transmit data reg
	USART6->DR = (ch & 0xFF);
}

static uint16_t compute_uart_bd (uint32_t periph_clk, uint32_t baudrate)
{
	return ((periph_clk + (baudrate / 2U)) / baudrate);
}

static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate)
{
	USART1->BRR = compute_uart_bd(periph_clk, baudrate);
}
