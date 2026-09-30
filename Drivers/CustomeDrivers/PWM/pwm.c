#include "stm32f103xb.h"
#include "stm32f1xx.h"
#include <stdint.h>
#include "pwm.h"

// note this api can be used for TIM2 to TIM4 and at 8MHZ APB2 clock frequency



#define TIMER_CLOCK 8000000U


static void PWM_GPIO_init(TIM_TypeDef *TIMx,
                          PWM_channel_t channel)
{
    /* Enable GPIO clocks */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;


    /*
     * TIM2
     * CH1 -> PA0
     * CH2 -> PA1
     * CH3 -> PA2
     * CH4 -> PA3
     */
    if (TIMx == TIM2)
    {
        if (channel == PWM_CH1)
        {
            GPIOA->CRL &= ~(0xFu << 0);
            GPIOA->CRL |=  (0xBu << 0);
        }

        else if (channel == PWM_CH2)
        {
            GPIOA->CRL &= ~(0xFu << 4);
            GPIOA->CRL |=  (0xBu << 4);
        }

        else if (channel == PWM_CH3)
        {
            GPIOA->CRL &= ~(0xFu << 8);
            GPIOA->CRL |=  (0xBu << 8);
        }

        else if (channel == PWM_CH4)
        {
            GPIOA->CRL &= ~(0xFu << 12);
            GPIOA->CRL |=  (0xBu << 12);
        }
    }


    /*
     * TIM3
     * CH1 -> PA6
     * CH2 -> PA7
     * CH3 -> PB0
     * CH4 -> PB1
     */
    else if (TIMx == TIM3)
    {
        if (channel == PWM_CH1)
        {
            GPIOA->CRL &= ~(0xFu << 24);
            GPIOA->CRL |=  (0xBu << 24);
        }

        else if (channel == PWM_CH2)
        {
            GPIOA->CRL &= ~(0xFu << 28);
            GPIOA->CRL |=  (0xBu << 28);
        }

        else if (channel == PWM_CH3)
        {
            GPIOB->CRL &= ~(0xFu << 0);
            GPIOB->CRL |=  (0xBu << 0);
        }

        else if (channel == PWM_CH4)
        {
            GPIOB->CRL &= ~(0xFu << 4);
            GPIOB->CRL |=  (0xBu << 4);
        }
    }


    /*
     * TIM4
     * CH1 -> PB6
     * CH2 -> PB7
     * CH3 -> PB8
     * CH4 -> PB9
     */
    else if (TIMx == TIM4)
    {
        if (channel == PWM_CH1)
        {
            GPIOB->CRL &= ~(0xFu << 24);
            GPIOB->CRL |=  (0xBu << 24);
        }

        else if (channel == PWM_CH2)
        {
            GPIOB->CRL &= ~(0xFu << 28);
            GPIOB->CRL |=  (0xBu << 28);
        }

        else if (channel == PWM_CH3)
        {
            GPIOB->CRH &= ~(0xFu << 0);
            GPIOB->CRH |=  (0xBu << 0);
        }

        else if (channel == PWM_CH4)
        {
            GPIOB->CRH &= ~(0xFu << 4);
            GPIOB->CRH |=  (0xBu << 4);
        }
    }
}


static void PWM_TimerClock_Enable(TIM_TypeDef *TIMx)
{
    if (TIMx == TIM2)
    {
        RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    }

    else if (TIMx == TIM3)
    {
        RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    }

    else if (TIMx == TIM4)
    {
        RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    }
}


static void PWM_SetMode(TIM_TypeDef *TIMx,
                        PWM_channel_t channel)
{
    switch(channel)
    {
        case PWM_CH1:

            TIMx->CCMR1 &= ~(0xFF);
            TIMx->CCMR1 |= (0x6u << 4);       
            TIMx->CCMR1 |= TIM_CCMR1_OC1PE;

            break;


        case PWM_CH2:

            TIMx->CCMR1 &= ~(0xFF00);
            TIMx->CCMR1 |= (0x6u << 12);      
            TIMx->CCMR1 |= TIM_CCMR1_OC2PE;

            break;


        case PWM_CH3:

            TIMx->CCMR2 &= ~(0xFF);
            TIMx->CCMR2 |= (0x6u << 4);       
            TIMx->CCMR2 |= TIM_CCMR2_OC3PE;

            break;


        case PWM_CH4:

            TIMx->CCMR2 &= ~(0xFF00);
            TIMx->CCMR2 |= (0x6u << 12);      
            TIMx->CCMR2 |= TIM_CCMR2_OC4PE;

            break;


        default:
            break;
    }
}


void PWM_Init(TIM_TypeDef *TIMx,
              PWM_channel_t channel,
              uint32_t frequency)
{
    uint32_t prescaler = 7;
    uint32_t arr;


   
    PWM_TimerClock_Enable(TIMx);


    
    PWM_GPIO_init(TIMx, channel);


    
    arr = (TIMER_CLOCK /
          ((prescaler + 1) * frequency)) - 1;


    TIMx->PSC = prescaler;

    TIMx->ARR = arr;


    
    PWM_SetMode(TIMx, channel);


    
    TIMx->CR1 |= TIM_CR1_ARPE;


    
    PWM_SetDuty(TIMx, channel, 0);


    /* Do NOT enable channel here */
}


void PWM_EnableChannel(TIM_TypeDef *TIMx,
                       PWM_channel_t channel)
{
    switch(channel)
    {
        case PWM_CH1:
            TIMx->CCER |= TIM_CCER_CC1E;
            break;

        case PWM_CH2:
            TIMx->CCER |= TIM_CCER_CC2E;
            break;

        case PWM_CH3:
            TIMx->CCER |= TIM_CCER_CC3E;
            break;

        case PWM_CH4:
            TIMx->CCER |= TIM_CCER_CC4E;
            break;

        default:
            break;
    }
}


void PWM_DisableChannel(TIM_TypeDef *TIMx,
                        PWM_channel_t channel)
{
    switch(channel)
    {
        case PWM_CH1:
            TIMx->CCER &= ~TIM_CCER_CC1E;
            break;

        case PWM_CH2:
            TIMx->CCER &= ~TIM_CCER_CC2E;
            break;

        case PWM_CH3:
            TIMx->CCER &= ~TIM_CCER_CC3E;
            break;

        case PWM_CH4:
            TIMx->CCER &= ~TIM_CCER_CC4E;
            break;

        default:
            break;
    }
}


void PWM_SetDuty(TIM_TypeDef *TIMx,
                 PWM_channel_t channel,
                 uint8_t duty)
{
    uint32_t value;


    if (duty > 100)
        duty = 100;


    value = ((TIMx->ARR + 1) * duty) / 100;


    switch(channel)
    {
        case PWM_CH1:
            TIMx->CCR1 = value;
            break;

        case PWM_CH2:
            TIMx->CCR2 = value;
            break;

        case PWM_CH3:
            TIMx->CCR3 = value;
            break;

        case PWM_CH4:
            TIMx->CCR4 = value;
            break;

        default:
            break;
    }
}


void PWM_Start(TIM_TypeDef *TIMx)
{
    TIMx->CR1 |= TIM_CR1_CEN;
}


void PWM_Stop(TIM_TypeDef *TIMx)
{
    TIMx->CR1 &= ~TIM_CR1_CEN;
}

