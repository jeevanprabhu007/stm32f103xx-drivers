#ifndef ADC_H
#define ADC_H

#include "stm32f103xb.h"
#include "stm32f1xx.h"
#include <stdint.h>

#define ADC_Channel_0 0x0u
#define ADC_Channel_1 0x1u
#define ADC_Channel_2 0x2u
#define ADC_Channel_3 0x3u
#define ADC_Channel_4 0x4u
#define ADC_Channel_5 0x5u
#define ADC_Channel_6 0x6u
#define ADC_Channel_7 0x7u
#define ADC_Channel_8 0x8u
#define ADC_Channel_9 0x9u
#define ADC_Channel_10 0xAu
#define ADC_Channel_11 0xBu
#define ADC_Channel_12 0xCu
#define ADC_Channel_13 0xDu
#define ADC_Channel_14 0xEu
#define ADC_Channel_15 0xFu
#define ADC_Channel_16 0x10u
#define ADC_Channel_17 0x11u

#define enable 0x1u


typedef enum{
   ADC_MODE_SINGLE = 0,
   ADC_MODE_SCAN
}ADC_mode_t;

typedef enum{
   ADC_OK = 0,
   ADC_ERROR,
   ADC_BUSY,
   ADC_INVALID_CHANNEL,
   ADC_INVALID_RANK,
   ADC_TIMEOUT
}ADC_Status_t;

typedef enum{
  sampling_1_5 = 0x0u,
  sampling_7_5 = 0x1u,  
  sampling_13_5 = 0x2u,
  sampling_28_5 = 0x3u,
  sampling_41_5 = 0x4u,
  sampling_55_5 = 0x5u,
  sampling_71_5 = 0x6u,
  sampling_239_5 = 0x7u,
}ADC_samplingtime_t;

typedef struct{
   uint8_t channel;
   uint8_t rank;
   ADC_samplingtime_t sampling_time;
}ADC_channel_config_t;

typedef struct{
   ADC_TypeDef *instance;
   ADC_mode_t mode;
   uint8_t continuous;
   uint8_t channel_count;
   ADC_channel_config_t *channels;
}ADC_Config_t;





void ADC_Set_sampling (ADC_TypeDef *ADCx,uint8_t channel,ADC_samplingtime_t sampling_time);

ADC_Status_t ADC_channel_config(ADC_TypeDef *ADCx,uint8_t channel,uint8_t rank,ADC_samplingtime_t sampling_time);

ADC_Status_t ADC_Init(ADC_Config_t *config);

void ADC_Calibrate(ADC_TypeDef *ADCx);

void ADC_Start(ADC_TypeDef *ADCx);

uint16_t ADC_READ(ADC_TypeDef *ADCx);







#endif