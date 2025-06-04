#include "bsp.h"
#include "stm32f4xx.h"

#define GPIOAEN  (1U << 0)
#define GPIOEEN  (1U << 4)

#define PIN5     (1U << 5)
#define LED_PIN  PIN5
#define PIN3     (1U << 4)
#define BTN_PIN  PIN3

void led_init (void)
{
	// Enable clock access to GPIOA
	RCC->AHB1ENR |=  GPIOAEN;
	// Set PA6 mode to output mode
	GPIOA->MODER |=  (1U << 12);
	GPIOA->MODER &= ~(1U << 13);
}

void led_on (void)
{
	// Set PA6 high
	GPIOA->ODR   |= LED_PIN;
}

void led_off (void)
{
	// Set PA6 low
	GPIOA->ODR   &= ~LED_PIN;
}

void button_init (void)
{
	// Enable the clock access to PORTE
	RCC->AHB1ENR |= GPIOEEN;
	// Set PE3 as an input pin
	GPIOE->MODER &= ~(1U << 8);
	GPIOE->MODER &= ~(1U << 9);
}

bool get_btn_state (void)
{
	// Check if button is pressed
	// Btn is active low
	if (GPIOE->IDR & BTN_PIN)
	{
		return false;
	}
	else
	{
		return true;
	}
}







