
#include "LED_driver.h"
#include <stdlib.h>





/*******************************************************************************
* ����: 
* ����: 
* �β�: 
* ����: ��
* ˵��: 
*******************************************************************************/
void Motor_DriverInit(void)
{
	  //�����������
	  GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST); //����������  
	  GPIO_Init(GPIOC, GPIO_PIN_1, GPIO_MODE_OUT_PP_LOW_FAST);
	  GPIO_Init(GPIOC, GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST);
      
      //���2�������
	  GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);
      //LED��
	  GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);
      
	  GPIO_WriteLow(GPIOD, GPIO_PIN_3);
	  GPIO_WriteLow(GPIOC, GPIO_PIN_1);
	  GPIO_WriteLow(GPIOC, GPIO_PIN_2);
	  GPIO_WriteLow(GPIOC, GPIO_PIN_3);
	  GPIO_WriteLow(GPIOC, GPIO_PIN_4);
      //GPIO_WriteHigh(GPIOC, GPIO_PIN_3);
	  //���������
	  GPIO_Init(GPIOB, GPIO_PIN_0, GPIO_MODE_IN_PU_NO_IT); //���1�����
	  GPIO_Init(GPIOB, GPIO_PIN_1, GPIO_MODE_IN_PU_NO_IT); //���2 �϶������
	  GPIO_Init(GPIOB, GPIO_PIN_2, GPIO_MODE_IN_PU_NO_IT); //���2 �¶������
	
	//TIMER2
//	GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_SLOW);
//	GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_SLOW);

//	//TIMER1
//	GPIO_Init(GPIOC, GPIO_PIN_1, GPIO_MODE_OUT_PP_LOW_SLOW);
//	GPIO_Init(GPIOC, GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_SLOW);
//	GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_SLOW);

//	TIM2_DeInit();
//	TIM2_TimeBaseInit(TIM2_PRESCALER_1, 1600);		//Ƶ�ʸı� ��ֵ

//	//��ʱ��2	��Ƶ
//	TIM2->PSCR			= (uint8_t) (TIM2_PRESCALER_1); //TIM2_PRESCALER_1

//	//�趨����ֵ
//	TIM2->ARRH			= (uint8_t) (160 >> 8); 	//LED_PERIOD
//	TIM2->ARRL			= (uint8_t) (160);


//	TIM2_OC1Init(TIM2_OCMODE_TOGGLE, TIM2_OUTPUTSTATE_ENABLE, 160, TIM2_OCPOLARITY_HIGH);
//	TIM2_OC2Init(TIM2_OCMODE_TOGGLE, TIM2_OUTPUTSTATE_ENABLE, 160, TIM2_OCPOLARITY_HIGH);
//	TIM2_CCxCmd(TIM2_CHANNEL_1, ENABLE);
//	TIM2_CCxCmd(TIM2_CHANNEL_2, ENABLE);

//	//����ʹ��
//	TIM2->CR1			|= (uint8_t)
//	TIM2_CR1_ARPE;									//TIM_ARRPreloadConfig(ENABLE);

//	//��ʱ��2ʹ��
//	TIM2->CR1			|= (uint8_t)
//	TIM2_CR1_CEN;									//TIM2_Cmd(ENABLE);

//	TIM2->CCER2 		|= (uint8_t) ((uint8_t) (TIM2_OUTPUTSTATE_ENABLE & (uint8_t) TIM2_CCER1_CC2E));



//	//***************************TIMER1**********************************************
//	//TIMER1
//	TIM1_DeInit();
//	IM1_TimeBaseInit(0, TIM1_COUNTERMODE_UP, 1600, 0); //Ƶ�ʸı� ��ֵ



//	TIM1_OC1Init(TIM1_OCMODE_TOGGLE, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE, 
//		160, TIM1_OCPOLARITY_HIGH, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET, TIM1_OCNIDLESTATE_SET);

//	TIM1_OC2Init(TIM1_OCMODE_TOGGLE, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE, 
//		160, TIM1_OCPOLARITY_HIGH, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET, TIM1_OCNIDLESTATE_SET);

//	TIM1_OC3Init(TIM1_OCMODE_TOGGLE, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE, 
//		160, TIM1_OCPOLARITY_HIGH, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET, TIM1_OCNIDLESTATE_SET);

//  TIM1_CCxNCmd(TIM1_CHANNEL_1, ENABLE);
//  TIM1_CCxNCmd(TIM1_CHANNEL_2, ENABLE);
//  TIM1_CCxNCmd(TIM1_CHANNEL_3, ENABLE);
//	TIM1_OC1PreloadConfig(ENABLE);
//	TIM1_OC2PreloadConfig(ENABLE);
//	TIM1_OC3PreloadConfig(ENABLE);

//	TIM1_ARRPreloadConfig(ENABLE);
//	TIM1_CtrlPWMOutputs(ENABLE);					/* ʹ��TIM1��� */
//	TIM1_Cmd(ENABLE);								/* TIM1 counter ʹ�� DISABLE*/
//	TIM2_Cmd(ENABLE);
}



