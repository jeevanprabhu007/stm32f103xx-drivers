#ifndef GPIO_H
#define GPIO_H

#include "stm32f1xx.h"
#include <stdint.h>


#define GPIO_PIN0 0u
#define GPIO_PIN1 1u
#define GPIO_PIN2 2u
#define GPIO_PIN3 3u
#define GPIO_PIN4 4u
#define GPIO_PIN5 5u
#define GPIO_PIN6 6u
#define GPIO_PIN7 7u
#define GPIO_PIN8 8u
#define GPIO_PIN9 9u
#define GPIO_PIN10 10u
#define GPIO_PIN11 11u
#define GPIO_PIN12 12u
#define GPIO_PIN13 13u
#define GPIO_PIN14 14u
#define GPIO_PIN15 15u

#define GPIO_MODE_IN 0x0u
#define GPIO_MODE_OUT_10MHZ 0x1u
#define GPIO_MODE_OUT_2MHZ 0x2u
#define GPIO_MODE_OUT_50MHZ 0x3u

#define GPIO_CONFIG_AM 0x0u
#define GPIO_CONFIG_FIN 0x1u
#define GPIO_CONFIG_PU_PD 0x2u 

#define GPIO_CONFIG_OUT_PP 0x0u
#define GPIO_CONFIG_OUT_OD 0x1u
#define GPIO_CONFIG_ALT_PP 0x2u
#define GPIO_CONFIG_ALT_OD 0x3u

#define Pin_State_High 0x1u
#define Pin_state_Low 0x0u

void GPIO_clockEnable(GPIO_TypeDef *port);
void GPIO_init(GPIO_TypeDef *port,uint8_t pin, uint8_t Mode,uint8_t Config);
void GPIO_TogglePin(GPIO_TypeDef *port,uint8_t pin,uint16_t Delay);
void GPIO_Set_ResetPin(GPIO_TypeDef *port,uint8_t pin,uint8_t state);
 /*00: Analog mode
01: Floating input (reset state)
10: Input with pull-up / pull-down
11: Reserved
In output mode (MODE[1:0] > 00):
00: General purpose output push-pull
01: General purpose output Open-drain
10: Alternate function output Push-pull
11: Alternate function output Open-drain */

#endif