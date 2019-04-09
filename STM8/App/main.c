

/* 头文件 --------------------------------------------------------------------*/
#define _MAININC_
#include "stm8s.h"
#undef _MAININC_

/****接线方式***********
*	UART PD5:TX  PD6: RX
*	
*	
*
*************************/

/* 局部函数-------------------------------------------------------------------*/
void McuClk_Init(void);
void SysTickTask(void);


/*******************************************************************************
* 名称:
* 功能:
* 形参:	
* 返回: 无
* 说明:注意进入中断太频繁，要在中断里面喂狗，否则一直重启
*******************************************************************************/
void main(void)
{
	McuClk_Init();
	SysParameterInit(); 							//参数初始化
	Uart2_Init();									//		INTERRUPT_HANDLER(UART2_RX_IRQHandler, 21)中断处理函数 
	ITC_SetSoftwarePriority(ITC_IRQ_UART2_RX, ITC_PRIORITYLEVEL_1); //设置串口接收中断优先级
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
* 名称: 
* 功能: 
* 形参: 
* 返回: 无
* 说明: 
******************************************************************************/
void McuClk_Init(void)
{
	//使用宏定义的写法
#ifdef HSE_Enable

	while (!CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, \ CLK_CURRENTCLOCKSTATE_DISABLE))
		;

	//切换到外部时钟,并等待时钟却换成功
#else

	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
#endif


	IWDG->KR			= 0xCC; 					//启动IWDG	
	IWDG->KR			= 0x55; 					//解除 PR 及 RLR 的写保护	
	IWDG->RLR			= 0xff; 					//看门狗计数器重装载数值 		 
	IWDG->PR			= 0x04; 					//分频系数为6-256 1.02s	 4-64 0.25S 
	IWDG->KR			= 0xAA; 					//刷新IDDG，避免产生看门狗复位，同时恢复 PR 及 RLR 的写保	
}



/*******************************************************************************
* 名称: ReceiveTask
* 功能: 
* 形参:		
* 返回: 无
* 说明: 
***************************************************************************8***/

#define MOTOR_STEP  10000//电机驱动设置的步数 * 2
void ReceiveTask(void)
{
	//串口接收到数据，数据解析星座与数据校验
	char			CheckSum = 0;
	int 			xingZuo = 0, i;

	for (i = 0; i < 7; i++)
		CheckSum += SysInfor.u8Recive[i];

	if ((SysInfor.u8Recive[0] == 0xAA) //包 头
	&& ((SysInfor.u8Recive[1] == 0x01) || (SysInfor.u8Recive[1] == 0x02)) //cmd 命令 0x01升起，0x02降落
	&& (SysInfor.u8Recive[2] == 0x03) //包体大小
	&& (SysInfor.u8Recive[4] == 0) //arg1
	&& (SysInfor.u8Recive[5] == 0) //arg2 默认0

	//&&(SysInfor.u8Recive[6] == CheckSum) //校验和，暂时未使用
	&& (SysInfor.u8Recive[7] == 0x55)) //包 尾
	{
		xingZuo 			= SysInfor.u8Recive[3];
	}

	if (SysInfor.u8Recive[1] == 0x01) {
		//计算各电机旋转角度 u16Motor1Count 为实际步进2倍 形成脉冲
		//过零点后旋转圈 + 星座对应角度   步进电机驱动设置MOTOR_STEP步一圈
		//过零点后旋转两圈 + 星座对应角度
		SysInfor.u32Motor1Count = MOTOR_STEP *2 + (u32)xingZuo * MOTOR_STEP / 12;
		SysInfor.bStateMode = M_MODE_UP;			//电机2上升
		GPIO_WriteLow(GPIOC, GPIO_PIN_3);			//电机2方向
	}
	else {
		SysInfor.bStateMode = M_MODE_DOWN;			//电机2下降
		GPIO_WriteHigh(GPIOC, GPIO_PIN_3);			//电机2方向
	}

	SysInfor.bRecComplite = FALSE;
	SysInfor.bUpdate	= 1;
	SysInfor.bMotor1Status = M_IDLE;
	SysInfor.bMotor2Status = M_IDLE;
}


/*******************************************************************************
* 名称: 
* 功能: 
* 形参:		
* 返回: 无
* 说明: 
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

    if((SysInfor.bMotor1Status == M_READY)) //电机1转完 电机2才开始运动
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
* 名称: 
* 功能: 
* 形参:		
* 返回: 无
* 说明: 
***************************************************************************8***/
void SysTickTask(void)
{
	static u16		SecTick = 1000;
	static u16		u16MotTick = MOTOR_COVER_TIME;	//0.5ms x 2 =1ms相应修改时钟中断重载值 SysTickInit();如果调整了步数，也要改相应的东东

	IWDG->KR			= 0xAA; 					//喂狗

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

		if (SysInfor.bRecComplite == TRUE) //接收完成
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


