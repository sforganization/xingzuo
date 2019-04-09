
#include "MainTaskApp.h"
#include "LED_driver.h"


void Drv_ReadPoint()
{

}


#define STATE_TIME				0	 //防抖检测时间 20ms


void Drv_Motor1Process(void)
{
	switch (SysInfor.bMotor1Status)
	{
		case M_IDLE: //空转
			if (GPIO_ReadInputPin(GPIOB, GPIO_PIN_0) == RESET) //SET or RESET
			{
				SysInfor.u8DetectM1Timer = STATE_TIME;
				SysInfor.bMotor1Status = M_ZERO;
			}

			break;

		case M_ZERO: //检测零点
			if (SysInfor.u8DetectM1Timer == 0) {

				if (GPIO_ReadInputPin(GPIOB, GPIO_PIN_0) == RESET) //SET or RESET
				{
					SysInfor.bMotor1Status = M_RUN;
				}
				else {
					SysInfor.bMotor1Status = M_IDLE;
				}
			}

			break;

		case M_RUN: //运行
			if (SysInfor.u32Motor1Count == 0) {
				SysInfor.bMotor1Status = M_READY;
			}

			break;

		case M_READY: //准备就绪
			break;

		default:
			SysInfor.bMotor1Status = M_IDLE;
			break;
	}
}


void Drv_Motor2Process_Up(void)
{
	switch (SysInfor.bMotor2Status)
	{
		case M_IDLE: //空转
			if (GPIO_ReadInputPin(GPIOB, GPIO_PIN_1) == RESET) //SET or RESET
			{
				SysInfor.u8DetectM2Timer = STATE_TIME;
				SysInfor.bMotor2Status = M_ZERO;
			}

			break;

		case M_ZERO: //检测零点
			if (SysInfor.u8DetectM2Timer == 0) {

				if (GPIO_ReadInputPin(GPIOB, GPIO_PIN_1) == RESET) //SET or RESET
				{
					SysInfor.bMotor2Status = M_RUN;	  
                    //GPIO_WriteLow(GPIOC, GPIO_PIN_4);
                    //LED输出高
                    GPIO_WriteHigh(GPIOC, GPIO_PIN_4);
				}
				else {
					SysInfor.bMotor2Status = M_IDLE;
				}
			}

			break;

		case M_RUN: //运行
				SysInfor.bMotor2Status = M_READY;
			break;

		case M_READY: //准备就绪
			break;

		default:
			SysInfor.bMotor2Status = M_IDLE;
			break;
	}
}


void Drv_Motor2Process_Down(void)
{
	switch (SysInfor.bMotor2Status)
	{
		case M_IDLE: //空转
			if (GPIO_ReadInputPin(GPIOB, GPIO_PIN_2) == RESET) //SET or RESET
			{
				SysInfor.u8DetectM2Timer = STATE_TIME;
				SysInfor.bMotor2Status = M_ZERO;
			}

			break;

		case M_ZERO: //检测零点
			if (SysInfor.u8DetectM2Timer == 0) {

				if (GPIO_ReadInputPin(GPIOB, GPIO_PIN_2) == RESET) //SET or RESET
				{
					SysInfor.bMotor2Status = M_RUN;
                    //LED输出低
                    GPIO_WriteLow(GPIOC, GPIO_PIN_4);
				}
				else {
					SysInfor.bMotor2Status = M_IDLE;
				}
			}

			break;

		case M_RUN: //运行
				SysInfor.bMotor2Status = M_READY;
			break;

		case M_READY: //准备就绪
			break;

		default:
			SysInfor.bMotor2Status = M_IDLE;
			break;
	}
}


/*******************************************************************************
* 名称: MainTaskScanf
* 功能: 主任务处理
* 形参: 
* 返回: 无
* 说明: 
*******************************************************************************/
void MainTask_Process(void)
{
	if (SysInfor.bUpdate == 0) {
		return;
	}

   if (SysInfor.bStateMode == M_MODE_UP)
    {
    	if ((SysInfor.bMotor1Status == M_READY) && (SysInfor.bMotor2Status == M_READY)) {
    		SysInfor.bUpdate	= 0;
    	}
    	else if (SysInfor.bMotor1Status != M_READY) {
    		Drv_Motor1Process();						//电机1任务，星座图案
    	}
    	else {
    		Drv_Motor2Process_Up();						//电机2任务，升
    	}
    }
   else
    {    	
        if (SysInfor.bMotor2Status == M_READY) {
    		SysInfor.bUpdate	= 0;
    	}
        SysInfor.bMotor1Status = M_READY;
        Drv_Motor2Process_Down();						//电机2任务，降
   }
}


/*******************************************************************************
* 名称: LightABS
* 功能: 绝对值
* 形参: 
* 返回: 无
* 说明: 
*******************************************************************************/
u16 LightABS(u16 a, u16 b)
{
	if (a > b)
		return (a - b);

	return (b - a);
}



