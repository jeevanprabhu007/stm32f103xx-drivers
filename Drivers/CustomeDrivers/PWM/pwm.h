#ifndef PWM_H
#define PWM_H

#include "stm32f103xb.h"
#include <stdint.h>


#define FREQUENCY 10000u


typedef enum
{
    PWM_CH1 = 1,
    PWM_CH2,
    PWM_CH3,
    PWM_CH4
} PWM_channel_t;

void PWM_init(TIM_TypeDef *TIMx,PWM_channel_t channel,uint32_t frequency);

void PWM_EnableChannel(TIM_TypeDef *TIMx,PWM_channel_t channel);

void PWM_DisableChannel(TIM_TypeDef *TIMx,PWM_channel_t channel);

void PWM_SetDuty(TIM_TypeDef *TIMx,PWM_channel_t channel,uint8_t duty);

void PWM_Start(TIM_TypeDef *TIMx);

void PWM_Stop(TIM_TypeDef *TIMx);

#endif