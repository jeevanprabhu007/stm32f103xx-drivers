#include "gpio.h"
#include "stm32f103xb.h"
#include <stdint.h>

void GPIO_clockEnable(GPIO_TypeDef *port){

  if(port == GPIOA){
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  }
  else if(port == GPIOB){
     RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
  }
  else if(port == GPIOC){
     RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
  }
else if(port == GPIOD){
     RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
  }
else if(port == GPIOE){
     RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
  }
}




void GPIO_init(GPIO_TypeDef *port,uint8_t pin, uint8_t Mode,uint8_t Config){
  uint32_t shift;
 if(pin < 8){
  shift = pin*4;
  port->CRL &= ~(0xFu << shift);
  port->CRL |= ((Mode|(Config << 2)) << shift);
 }
 else{

  shift = (pin-8)*4;
  port->CRH &= ~(0xFu << shift);
  port->CRH |= ((Mode|(Config << 2)) << shift);
 }
}

void GPIO_TogglePin(GPIO_TypeDef *port,uint8_t pin,uint16_t Delay){

port->BSRR = (0x1u << pin);
    HAL_Delay(Delay);
    port->BSRR = (0x1u << (pin+16));
    HAL_Delay(Delay);
}


void GPIO_Set_ResetPin(GPIO_TypeDef *port,uint8_t pin,uint8_t state){
   
 if(state){
  port->BSRR = (1u << pin);
 }
 else {
 port->BSRR = (1u << (pin-8));
 }

}

