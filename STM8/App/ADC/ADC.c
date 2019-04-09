#include "stm8s.h"
#include "adc.h"

#define AD_CHANNEL      ADC1_CHANNEL_0
#define AD_CHANNEL_IO   (GPIO_PIN_0)
#define SAMPLE_COUNT    4    

/*******************************************************************************
* @��������    ADCInit
* @����˵��   ADC��ʼ��
* @�������   ��
* @�������   ��
* @���ز���   ��
*******************************************************************************/
void ADC_Init(void)
{
  GPIO_Init(GPIOB,AD_CHANNEL_IO, GPIO_MODE_IN_PU_NO_IT );
  
  ADC1_DeInit();
  ADC1_Init(ADC1_CONVERSIONMODE_SINGLE, ADC1_CHANNEL_0, ADC1_PRESSEL_FCPU_D2,
            ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL3, DISABLE);
  ADC1_Cmd(ENABLE);
}
/*******************************************************************************
* @��������   ADCGet
* @����˵��   ADC��ȡת��ֵ  ֻҪ8λ
* @�������   ��
* @�������   ADת��ֵ
* @���ز���   ��
*******************************************************************************/
u16 GetADValue(void)
{
  u16 ADcount = 0, i;
  FlagStatus ADCRdy = RESET;

  for(i = 0; i < 8; i++)
  {
    ADC1_StartConversion();
    ADC1->CR1 |= 0x01;  //�ٴ�ʹ��ADC
    do
    {
      ADCRdy = ADC1_GetFlagStatus(ADC1_FLAG_EOC);
    }
    while(ADCRdy == RESET);           // SET or RESET  
    
    ADcount += ADC1_GetConversionValue(); 
  }  
  
  ADcount = ADcount >>3;   //��ƽ�� 
   
 return ADcount;//16λ
}

