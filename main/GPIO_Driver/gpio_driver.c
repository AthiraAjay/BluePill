/*************BLUE PILL SPECIFIC HEADER FILE**************           
 *************				DEFINITION						**************           
 * This driver file is specifically created for          *
 * STM32F103CT Blue Pill MCU .         									 *
 * Author : Athira Ajayakumar														 *
 *********************************************************/

#include "gpio_driver.h"
#include "stm32f10x.h"

/*********************************************************
 * FUNCTION NAME : gpio_clock_config()                   *
 *																											 *
 * DESCRIPTION   : ENABLE or DISABLE the GPIO            *
 *                 PORT A,B,C clock                      *
 *                                         							 *
 * PARAMETERS    : GPIOx  -> Pointer To access GPIO      *
 *                           registers                   *
 *                 enable -> To enable or disaable the   *
 *                           port clock   							 *
 *																											 *
 * RETURN TYPE   : None                                  *
 *********************************************************/ 
void gpio_clock_config( GPIO_TypeDef *GPIOx, bool enable)
{
	// 'enable' is set to high to enable the clock
	if (enable)
	{
		if      (GPIOx == GPIOA)  GPIO_A_CLOCK_ENABLE();
		else if (GPIOx == GPIOB)	GPIO_B_CLOCK_ENABLE();
		else if (GPIOx == GPIOC)	GPIO_C_CLOCK_ENABLE();
	}
	else
	{
		// 'enable' is low to disable the clock
		if      (GPIOx == GPIOA)  GPIO_A_CLOCK_DISABLE();
		else if (GPIOx == GPIOB)	GPIO_B_CLOCK_DISABLE();
		else if (GPIOx == GPIOC)	GPIO_C_CLOCK_DISABLE();
	}
}


/*********************************************************
 * FUNCTION NAME : afio_clock_config()                   *
 *																											 *
 * DESCRIPTION   : ENABLE or DISABLE the Alternate       *
 *                 function clock                        *
 *                                         							 *
 * PARAMETERS    : enable -> To enable or disable the    *
 *                 alternate function clock              *
 *																											 *
 * RETURN TYPE   : None                                  *
 *********************************************************/ 
void afio_clock_config(bool enable)
{
	// 'enable' is set to high to enable the clock
	if (enable)   		AFIO_CLOCK_ENABLE();
	
	// 'enable' is low to disable the clock
	else  		        AFIO_CLOCK_DISABLE();
}


/*********************************************************
 * FUNCTION NAME : gpio_pin_config()                     *
 *																											 *
 * DESCRIPTION   : To configure pin of a GPIO part       *
 *                                         							 *
 * PARAMETERS    : GPIOx  -> Pointer To access GPIO      *
 *                           registers                   *
 *                 GPIOx_Pin -> Pointer to access pin    *
 *                             configuration of GPIO port*
 *																											 *
 * RETURN TYPE   : None                                  *
 *********************************************************/
void gpio_pin_config (GPIO_TypeDef *GPIOx, GPIO_PIN_CONFIG_t *GPIOx_Pin)
{
	
	bool enable = true;                    //To enable (true) or disable (false) the clock.
	int pin = GPIOx_Pin->pin;
	uint32_t mode = GPIOx_Pin->mode;
	uint32_t config_type = GPIOx_Pin->config_type;
	uint32_t pull = GPIOx_Pin->pull;
		
	// To enable the clock for the GPIO Port
	gpio_clock_config( GPIOx, enable);
	// To configure the pin configuration of the GPIO port
	gpio_set_pin_config( GPIOx,  pin,  mode, config_type, pull);
	
}

/*********************************************************
 * FUNCTION NAME : gpio_pin_config()                     *
 *																											 *
 * DESCRIPTION   : To configure pin of a GPIO part       *
 *                                         							 *
 * PARAMETERS    : GPIOx -> Pointer To access GPIO       *
 *                           registers                   *
 *                 mode -> To set the pin as input or    *
 *                         output (with the speed)       *
 *                 config_type ->To configure the I/O pin*
 *                 pull -> To configure the input pin as *
 *                         pull up or pull down          *
 *																											 *
 * RETURN TYPE   : None                                  *
 *********************************************************/
void gpio_set_pin_config (GPIO_TypeDef *GPIOx, int pin, uint32_t mode, uint32_t config_type, uint32_t pull)
{
	
	// Clearing the configuration bits
	uint32_t mask_bits; 
	uint32_t tempreg = 0x00000000;
	
	
	if (pin < GPIO_PIN_INT_8)  
	{
		// Clearing the configuration bits for the specific pin
		mask_bits = (uint32_t) (0x0000000C << (4 * pin));
		GPIOx->CRL &= ~ (mask_bits);
		
		// Setting the configuration and mode for the specific pin
		tempreg |= (mode | config_type) << (4 * pin);
		GPIOx->CRL |= tempreg;
	}
	else 
	{
		// Clearing the configuration bits for the specific pin
		mask_bits = (uint32_t) (0x0000000C << (4 * (pin - 8)));
    GPIOx->CRH &= ~ (mask_bits);
		
		// Setting the configuration and mode for the specific pin
		tempreg |= (mode | config_type) << (4 * (pin-8));
		GPIOx->CRH |= tempreg;
	}
	
	// To configure the input pin as pull up or pull down
	if       (pull == GPIO_IN_PULLDOWN_ODR_BIT)  ( GPIOx->BSRR |= (1 << ( 16 + pin)));
	else if  (pull == GPIO_IN_PULLUP_ODR_BIT)    ( GPIOx->BSRR |= (1 << pin));
	
}
