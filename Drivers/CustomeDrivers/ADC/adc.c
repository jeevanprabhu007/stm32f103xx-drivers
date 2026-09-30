#include"adc.h"
#include "stm32f103xb.h"
#include <stdint.h>







void ADC_Set_sampling(ADC_TypeDef *ADCx,uint8_t channel,ADC_samplingtime_t sampling_time){

   uint32_t shift;

   if(channel < 10 ){
      shift = channel*3;
      ADCx->SMPR2 &= ~(0x7u << shift);
      ADCx->SMPR2 |= ((uint32_t)sampling_time << shift);
   }
   else if(channel >= 10){
     shift = (channel - 10)*3;
     ADCx->SMPR1 &= ~(0x7u << shift);
    ADCx->SMPR1 |= ((uint32_t)sampling_time << shift);
   }
}

ADC_Status_t ADC_channel_config(ADC_TypeDef *ADCx,uint8_t channel,uint8_t rank,ADC_samplingtime_t sampling_time){
   
   uint32_t shift;
   if(channel > 17){
    return  ADC_INVALID_CHANNEL;

   }

   if(rank < 1 || rank > 16){
    return ADC_INVALID_RANK;
   }

ADC_Set_sampling(ADCx,channel,sampling_time);

   if(rank <= 6){
     shift = (rank-1)*5;
     ADCx->SQR3 &= ~(0x1Fu << shift);
     ADCx->SQR3 |= ((uint32_t)channel << shift);
   }
   else if(rank <= 12){
   shift = (rank-7)*5;
     ADCx->SQR2 &= ~(0x1Fu << shift);
     ADCx->SQR2 |= ((uint32_t)channel << shift);
   }
   else{
   shift = (rank-13)*5;
     ADCx->SQR1 &= ~(0x1Fu << shift);
     ADCx->SQR1 |= ((uint32_t)channel << shift);
   }

  return ADC_OK;

}



void ADC_Calibrate(ADC_TypeDef *ADCx){

 ADCx->CR2 |= (0x1u << 3);
 while (ADCx->CR2 & (0x1u << 3)); 
 
 
 ADCx->CR2 |= (0x1u << 2);
 while(ADCx->CR2 & (0x1 << 2));

}

ADC_Status_t ADC_Init(ADC_Config_t *config)
{
    ADC_TypeDef *ADCx;

    if (config == 0)
        return ADC_ERROR;

    ADCx = config->instance;


    

    if (ADCx == ADC1)
    {
        RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    }

    else if (ADCx == ADC2)
    {
        RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
    }

    else
    {
        return ADC_ERROR;
    }


   

    ADCx->CR2 &= ~ADC_CR2_ADON;


    

    ADCx->CR1 = 0;
    ADCx->CR2 = 0;

    ADCx->SQR1 = 0;
    ADCx->SQR2 = 0;
    ADCx->SQR3 = 0;


    

    if (config->mode == ADC_MODE_SCAN)
    {
        ADCx->CR1 |= ADC_CR1_SCAN;
    }


    

    if (config->continuous)
    {
        ADCx->CR2 |= ADC_CR2_CONT;
    }


    

    if (config->channel_count > 0 &&
        config->channel_count <= 16)
    {
        ADCx->SQR1 |=
            ((config->channel_count - 1) << 20);
    }


    

    for (uint8_t i = 0;
         i < config->channel_count;
         i++)
    {
        ADC_channel_config(
            ADCx,
            config->channels[i].channel,
            config->channels[i].rank,
            config->channels[i].sampling_time
        );
    }


    
    ADCx->CR2 |= ADC_CR2_ADON;
    
    
    for (volatile uint32_t i = 0;
         i < 1000;
         i++);




    ADC_Calibrate(ADCx);


    

    return ADC_OK;
}


void ADC_Start(ADC_TypeDef *ADCx){
ADCx->CR2 |= ADC_CR2_ADON;
ADCx->CR2 |= ADC_CR2_EXTTRIG;
ADCx->CR2 |= ADC_CR2_SWSTART;
}


uint16_t ADC_READ(ADC_TypeDef *ADCx){

while(!(ADCx->SR & (0x1u << 1)));
return ADCx->DR;

}