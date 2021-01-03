#include "stm32f10x.h"
#include <stdint.h>

#define HSEON 16
#define HSERDY 17

int main()
{
	
	// 1. Load the address of the RCC
	RCC_TypeDef *pRCC;
	pRCC = RCC;
	
	// 2. Turn on the HSE Oscillator
	pRCC->CR |= (1 << HSEON);


	// 3. Wait until the clock becomes stable.  
	while (!(pRCC->CR &(1 << HSERDY)));

	// 4. Now set the system clock as HSE
	pRCC->CFGR &= ~(0x3 << 0); // To clear the register
	pRCC->CFGR |= (0x1 << 0); 
}
