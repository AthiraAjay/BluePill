
#include "stm32f10x.h"

int main()
{
	  // 1. Load the base address of the peripheral register
	ADC_TypeDef *pADC;
	pADC = ADC1;
	
	// 2. Load the address of the Clock Bus Register which is connected to the Peripheral
	RCC_TypeDef *pRCC;
	pRCC = RCC;
	
	// 3. Enable the specific clock according to the peripherals
	pRCC->APB2ENR |= (1 << 9);
		
	// 4. Now you can use the peripheral
	pADC->CR1 =0x55;    
}
