/*************BLUE PILL SPECIFIC HEADER FILE**************           
 * This driver file is specifically created for          *
 * STM32F103CT Blue Pill MCU .         									 *
 * Author : Athira Ajayakumar														 *
 *********************************************************/

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "stm32f10x.h"
#include <stdbool.h>

/**********************************************************
 *               MACRO INITIALISATION                     *
 **********************************************************/
 
  
 // Macros to enable the clock for GPIO Ports
 #define AFIO_CLOCK_ENABLE()      (RCC->APB2ENR |= RCC_APB2ENR_AFIOEN)
 #define GPIO_A_CLOCK_ENABLE()    (RCC->APB2ENR |= RCC_APB2ENR_IOPAEN)
 #define GPIO_B_CLOCK_ENABLE()    (RCC->APB2ENR |= RCC_APB2ENR_IOPBEN)
 #define GPIO_C_CLOCK_ENABLE()    (RCC->APB2ENR |= RCC_APB2ENR_IOPCEN)
 
  // Macros to disable the clock for GPIO Ports
 #define AFIO_CLOCK_DISABLE()      (RCC->APB2ENR &= ~(RCC_APB2ENR_AFIOEN))
 #define GPIO_A_CLOCK_DISABLE()    (RCC->APB2ENR &= ~(RCC_APB2ENR_IOPAEN))
 #define GPIO_B_CLOCK_DISABLE()    (RCC->APB2ENR &= ~(RCC_APB2ENR_IOPBEN))
 #define GPIO_C_CLOCK_DISABLE()    (RCC->APB2ENR &= ~(RCC_APB2ENR_IOPCEN))
 
 
 #define AF_SPI1_NO_REMAP    ~(AFIO_MAPR_SPI1_REMAP)

 
 /**********************************************************
 *               ENUM INITIALISATION                     *
 **********************************************************/
  
 // GPIO MODE
 typedef enum
 {
		GPIO_INPUT         = 0x00000000,
		GPIO_OUTPUT_10MHZ  = 0x00000001, // Maximum output speed 10 MHz
	  GPIO_OUTPUT_2MHZ   = 0x00000002, // Maximum output speed 2 MHz
	  GPIO_OUTPUT_50MHZ  = 0x00000003  // Maximum output speed 50 MHz
 }GPIO_MODE_e;
 
 
 // GPIO Port Configuration (Bits are set not based on the data sheet. Bit 2 and Bit 3 are set according to datasheet instead of Bit 0 and Bit 1
 typedef enum
 {
	 GPIO_OUT_PUSHPULL  = 0x00000000, // General purpose output Push-pull
	 GPIO_OUT_OPENDRAIN = 0x00000004, // General purpose output Open-drain
	 GPIO_AF_PUSHPULL   = 0x00000002, // Alternate Function output Push-pull
	 GPIO_AF_OPENDRAIN  = 0x00000003, // Alternate Function output Open-drain
	 GPIO_IN_ANALOG     = 0x00000000, // Input Analog
	 GPIO_IN_FLOATING   = 0x00000004, // Input floating
	 GPIO_IN_PULLDOWN   = 0x00000008, // Input pull-down
	 GPIO_IN_PULLUP     = 0x00000008  // Input pull-up
}GPIO_CONFIG_e;
 

// To configure the input pin as pull up or pull down
typedef enum 
{
	GPIO_IN_PULLDOWN_ODR_BIT = 0,
	GPIO_IN_PULLUP_ODR_BIT = 1,
}GPIO_ODR_CONFIG_e;
 
typedef enum 
{
	 GPIO_PIN_0               =  ((uint16_t)0x0001),  /* Pin 0 selected    */
   GPIO_PIN_1               =  ((uint16_t)0x0002),  /* Pin 1 selected    */
   GPIO_PIN_2               =  ((uint16_t)0x0004),  /* Pin 2 selected    */
   GPIO_PIN_3               =  ((uint16_t)0x0008),  /* Pin 3 selected    */
   GPIO_PIN_4               =  ((uint16_t)0x0010),  /* Pin 4 selected    */
   GPIO_PIN_5               =  ((uint16_t)0x0020),  /* Pin 5 selected    */
   GPIO_PIN_6               =  ((uint16_t)0x0040),  /* Pin 6 selected    */
   GPIO_PIN_7               =  ((uint16_t)0x0080),  /* Pin 7 selected    */
   GPIO_PIN_8               =  ((uint16_t)0x0100),  /* Pin 8 selected    */
   GPIO_PIN_9               =  ((uint16_t)0x0200),  /* Pin 9 selected    */
   GPIO_PIN_10              =  ((uint16_t)0x0400),  /* Pin 10 selected   */
   GPIO_PIN_11              =  ((uint16_t)0x0800),  /* Pin 11 selected   */
   GPIO_PIN_12              =  ((uint16_t)0x1000),  /* Pin 12 selected   */
   GPIO_PIN_13              =  ((uint16_t)0x2000),  /* Pin 13 selected   */
   GPIO_PIN_14              =  ((uint16_t)0x4000),  /* Pin 14 selected   */
   GPIO_PIN_15              =  ((uint16_t)0x8000),  /* Pin 15 selected   */
   GPIO_PIN_All             =  ((uint16_t)0xFFFF)  /* All pins selected */
}GPIO_PIN_e;

// Enum to select GPIO pin 
typedef enum 
{
	 GPIO_PIN_INT_0               =  0,  /* Pin 0 selected    */
   GPIO_PIN_INT_1               =  1,  /* Pin 1 selected    */
   GPIO_PIN_INT_2               =  2,  /* Pin 2 selected    */
   GPIO_PIN_INT_3               =  3,  /* Pin 3 selected    */
   GPIO_PIN_INT_4               =  4,  /* Pin 4 selected    */
   GPIO_PIN_INT_5               =  5,  /* Pin 5 selected    */
   GPIO_PIN_INT_6               =  6,  /* Pin 6 selected    */
   GPIO_PIN_INT_7               =  7,  /* Pin 7 selected    */
   GPIO_PIN_INT_8               =  8,  /* Pin 8 selected    */
   GPIO_PIN_INT_9               =  9,  /* Pin 9 selected    */
   GPIO_PIN_INT_10              =  10,  /* Pin 10 selected   */
   GPIO_PIN_INT_11              =  11,  /* Pin 11 selected   */
   GPIO_PIN_INT_12              =  12,  /* Pin 12 selected   */
   GPIO_PIN_INT_13              =  13,  /* Pin 13 selected   */
   GPIO_PIN_INT_14              =  14,  /* Pin 14 selected   */
   GPIO_PIN_INT_15              =  15 /* Pin 15 selected   */
}GPIO_PIN_INT_e;
 
 /*********************************************************
 *               STRUCTURE INITIALISATION                 *
 **********************************************************/
  
 // GPIO Initialisation
 typedef struct
 {
	 GPIO_TypeDef *port;
	 uint32_t pin;
 }GPIO_PIN_ID_t;
 
 
 // GPIO pin configuration
 typedef struct
 {
	 int pin;
	 uint32_t mode;
	 uint32_t config_type;
	 uint32_t pull;
	 uint32_t alternate_func;
 }GPIO_PIN_CONFIG_t;
 
 /*********************************************************
 *               FUNCTION DECLARATION                     *
 **********************************************************/

 void gpio_clock_config( GPIO_TypeDef *GPIOx, bool enable);
   
 void afio_clock_config(bool enable);
 
 void gpio_set_pin_mode (GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t mode);
  
 void gpio_pin_config (GPIO_TypeDef *GPIOx, GPIO_PIN_CONFIG_t *GPIOx_Pin);
 
 void gpio_set_pin_config (GPIO_TypeDef *GPIOx, int pin, uint32_t mode, uint32_t config_type ,uint32_t pull);
#endif
