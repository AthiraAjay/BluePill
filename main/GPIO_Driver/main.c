#include "stm32f10x.h"
#include "gpio_driver.h"

int main(void)
{
	// Pointer to GPIOA Registers	
	GPIO_TypeDef *pGPIOA; 
	pGPIOA = GPIOA; 
	
	GPIO_PIN_CONFIG_t pinc [6];  // Array of structures
	
 /* Test Case 1
	* Pin 1 - OUTPUT
	* Config Type : Push pull  */
 	pinc[0].pin= GPIO_PIN_INT_1;
	pinc[0].mode = GPIO_OUTPUT_2MHZ ;  
	pinc[0].config_type = GPIO_OUT_PUSHPULL;
	gpio_pin_config (pGPIOA, &pinc[0]);

 /* Test Case 2
  * Pin 8 - OUTPUT
	* Config Type : IN ANALOG */
	pinc[1].pin= GPIO_PIN_INT_8;
	pinc[1].mode = GPIO_OUTPUT_2MHZ ;  
	pinc[1].config_type = GPIO_OUT_OPENDRAIN ;
	gpio_pin_config (pGPIOA, &pinc[1]);

 /* Test Case 3
	* Pin 3 - INPUT
	* Config Type : ANALOG */
	pinc[2].pin= GPIO_PIN_INT_3;
	pinc[2].mode = GPIO_INPUT ;  
	pinc[2].config_type = GPIO_IN_ANALOG;
	gpio_pin_config (pGPIOA, &pinc[2]);
	
 /* Test Case 4
	* Pin 9 - INPUT
	* Config Type : IN FLOATING */
	pinc[3].pin= GPIO_PIN_INT_9;
	pinc[3].mode = GPIO_INPUT ;  
	pinc[3].config_type = GPIO_IN_FLOATING;
	pinc[3].pull = GPIO_IN_PULLDOWN_ODR_BIT;
	gpio_pin_config (pGPIOA, &pinc[3]);
			
 /* Test Case 5
	* Pin 4 - INPUT
	* Config Type : GPIO PULL UP */
	pinc[4].pin= GPIO_PIN_INT_4;
	pinc[4].mode = GPIO_INPUT ;  
	pinc[4].config_type = GPIO_IN_PULLUP;
	pinc[4].pull = GPIO_IN_PULLUP_ODR_BIT;
	gpio_pin_config (pGPIOA, &pinc[4]);
	
 /* Test Case 6
	* Pin 6 - INPUT
	* Config Type : GPIO PULL DOWN */
	pinc[5].pin= GPIO_PIN_INT_10;
	pinc[5].mode = GPIO_INPUT ;  
	pinc[5].config_type = GPIO_IN_PULLDOWN;
	pinc[5].pull = GPIO_IN_PULLDOWN_ODR_BIT;
	gpio_pin_config (pGPIOA, &pinc[5]);
	
	return 0;
}
