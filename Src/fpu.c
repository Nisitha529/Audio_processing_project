#include "stm32f4xx.h"
#include "fpu.h"

void fpu_enable (void)
{
	//enable the FPU : Enable CP10 and CP11 full access
	SCB->CPACR |= (1 << 20);
	SCB->CPACR |= (1 << 21);
	SCB->CPACR |= (1 << 22);
	SCB->CPACR |= (1 << 23);
}
