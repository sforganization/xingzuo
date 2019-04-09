

/* ͷ�ļ� --------------------------------------------------------------------*/
#define _MAININC_
#include "stm8s.h"
#undef _MAININC_

/****���߷�ʽ***********
*	UART PD5:TX  PD6: RX
*	
*	
*
*************************/

/* �ֲ�����-------------------------------------------------------------------*/
void McuClk_Init(void);
void SysTickTask(void);


/*******************************************************************************
* ����:
* ����:
* �β�:	
* ����: ��
* ˵��:ע������ж�̫Ƶ����Ҫ���ж�����ι��������һֱ����
*******************************************************************************/
void main(void)
{
	McuClk_Init();
	SysParameterInit(); 							//������ʼ��
	Uart2_Init();									//		INTERRUPT_HANDLER(UART2_RX_IRQHandler, 21)�жϴ����� 
	ITC_SetSoftwarePriority(ITC_IRQ_UART2_RX, ITC_PRIORITYLEVEL_1); //���ô��ڽ����ж����ȼ�
	Motor_DriverInit();
	SysTickInit();

	while (1) {

		if (SysInfor.SysTick != 0) {
			SysInfor.SysTick--;
			SysTickTask();
		}

		MainTask_Process();
	}
}


/*******************************************************************************
* ����: 
* ����: 
* �β�: 
* ����: ��
* ˵��: 
******************************************************************************/
void McuClk_Init(void)
{
	//ʹ�ú궨���д��
#ifdef HSE_Enable

	while (!CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, \ CLK_CURRENTCLOCKSTATE_DISABLE))
		;

	//�л����ⲿʱ��,���ȴ�ʱ��ȴ���ɹ�
#else

	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
#endif


	IWDG->KR			= 0xCC; 					//����IWDG	
	IWDG->KR			= 0x55; 					//��� PR �� RLR ��д����	
	IWDG->RLR			= 0xff; 					//���Ź���������װ����ֵ 		 
	IWDG->PR			= 0x04; 					//��Ƶϵ��Ϊ6-256 1.02s	 4-64 0.25S 
	IWDG->KR			= 0xAA; 					//ˢ��IDDG������������Ź���λ��ͬʱ�ָ� PR �� RLR ��д��	
}



/*******************************************************************************
* ����: ReceiveTask
* ����: 
* �β�:		
* ����: ��
* ˵��: 
***************************************************************************8***/

#define MOTOR_STEP  10000//����������õĲ��� * 2
void ReceiveTask(void)
{
	//���ڽ��յ����ݣ����ݽ�������������У��
	char			CheckSum = 0;
	int 			xingZuo = 0, i;

	for (i = 0; i < 7; i++)
		CheckSum += SysInfor.u8Recive[i];

	if ((SysInfor.u8Recive[0] == 0xAA) //�� ͷ
	&& ((SysInfor.u8Recive[1] == 0x01) || (SysInfor.u8Recive[1] == 0x02)) //cmd ���� 0x01����0x02����
	&& (SysInfor.u8Recive[2] == 0x03) //�����С
	&& (SysInfor.u8Recive[4] == 0) //arg1
	&& (SysInfor.u8Recive[5] == 0) //arg2 Ĭ��0

	//&&(SysInfor.u8Recive[6] == CheckSum) //У��ͣ���ʱδʹ��
	&& (SysInfor.u8Recive[7] == 0x55)) //�� β
	{
		xingZuo 			= SysInfor.u8Recive[3];
	}

	if (SysInfor.u8Recive[1] == 0x01) {
		//����������ת�Ƕ� u16Motor1Count Ϊʵ�ʲ���2�� �γ�����
		//��������תȦ + ������Ӧ�Ƕ�   ���������������MOTOR_STEP��һȦ
		//��������ת��Ȧ + ������Ӧ�Ƕ�
		SysInfor.u32Motor1Count = MOTOR_STEP *2 + (u32)xingZuo * MOTOR_STEP / 12;
		SysInfor.bStateMode = M_MODE_UP;			//���2����
		GPIO_WriteLow(GPIOC, GPIO_PIN_3);			//���2����
	}
	else {
		SysInfor.bStateMode = M_MODE_DOWN;			//���2�½�
		GPIO_WriteHigh(GPIOC, GPIO_PIN_3);			//���2����
	}

	SysInfor.bRecComplite = FALSE;
	SysInfor.bUpdate	= 1;
	SysInfor.bMotor1Status = M_IDLE;
	SysInfor.bMotor2Status = M_IDLE;
}


/*******************************************************************************
* ����: 
* ����: 
* �β�:		
* ����: ��
* ˵��: 
***************************************************************************8***/
void MotorPulseTask(void)
{
	//	  (GPIOD, GPIO_PIN_3);
	//	  (GPIOC, GPIO_PIN_1);
	//	  (GPIOC, GPIO_PIN_2);
	//	  (GPIOC, GPIO_PIN_3);
	//	  (GPIOC, GPIO_PIN_4);
	//C1
	if (SysInfor.bMotor1Status == M_IDLE || SysInfor.bMotor1Status == M_ZERO) {
		GPIOD->ODR			^= (uint8_t)
		GPIO_PIN_3;
		GPIOC->ODR			^= (uint8_t)
		GPIO_PIN_1;

		//		GPIO_WriteReverse(GPIOD, GPIO_PIN_3);
		//		GPIO_WriteReverse(GPIOC, GPIO_PIN_1);
	}
	else if (SysInfor.u32Motor1Count) {
		SysInfor.u32Motor1Count--;

		//		GPIO_WriteReverse(GPIOC, GPIO_PIN_1);
		GPIOC->ODR			^= (uint8_t)
		GPIO_PIN_1;
		GPIOD->ODR			^= (uint8_t)
		GPIO_PIN_3;
	}

    if((SysInfor.bMotor1Status == M_READY)) //���1ת�� ���2�ſ�ʼ�˶�
    	{
        	//C2
        	if (SysInfor.bMotor2Status == M_IDLE || SysInfor.bMotor2Status == M_ZERO) {
        		//		GPIO_WriteReverse(GPIOC, GPIO_PIN_2);
        		GPIOC->ODR			^= (uint8_t)
        		GPIO_PIN_2;
        	}
        	else if (SysInfor.u32Motor2Count) {
        		SysInfor.u32Motor2Count--;

        		//		GPIO_WriteReverse(GPIOC, GPIO_PIN_2);
        		GPIOC->ODR			^= (uint8_t)
        		GPIO_PIN_2;
    	}
        }
}


/*******************************************************************************
* ����: 
* ����: 
* �β�:		
* ����: ��
* ˵��: 
***************************************************************************8***/
void SysTickTask(void)
{
	static u16		SecTick = 1000;
	static u16		u16MotTick = MOTOR_COVER_TIME;	//0.5ms x 2 =1ms��Ӧ�޸�ʱ���ж�����ֵ SysTickInit();��������˲�����ҲҪ����Ӧ�Ķ���

	IWDG->KR			= 0xAA; 					//ι��

	if (SysInfor.bUpdate != 0) {
		MotorPulseTask();
	}

	if (u16MotTick)
		u16MotTick--;

	if (u16MotTick == 0) {

        u16MotTick = MOTOR_COVER_TIME;
		if (SecTick)
			SecTick--;

		if (SecTick == 0) {
			SecTick 			= 1000;
		}

		if (SysInfor.bRecComplite == TRUE) //�������
		{
			ReceiveTask();
		}

		if (SysInfor.u8DetectM1Timer)
			SysInfor.u8DetectM1Timer--;

		if (SysInfor.u8DetectM2Timer)
			SysInfor.u8DetectM2Timer--;

		if (SysInfor.u8DetectM3Timer)
			SysInfor.u8DetectM3Timer--;

		if (SysInfor.u8DetectM4Timer)
			SysInfor.u8DetectM4Timer--;
	}

}


