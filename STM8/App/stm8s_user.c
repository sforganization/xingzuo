
#include <stdlib.h>
#include "stm8s_user.h"



/* 公共函数  -----------------------------------------------------------------*/
/*******************************************************************************
* 名称: 
* 功能: 系统任务时钟
* 形参:		
* 返回: 无
* 说明: 
******************************************************************************/
void SysTickInit(void)
{
	/* TIM4 configuration:
	- TIM4CLK is set to 16 MHz, the TIM4 Prescaler is equal to 128 so the TIM1 counter
	clock used is 16 MHz / 64 = 250 000 Hz
	- With 250 000 Hz we can generate time base:
	max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 250000 = 1.024 ms
	min time base is 0.008 ms if TIM4_PERIOD = 1   --> (  1 + 1) / 250000 = 0.008 ms
	- In this example we need to generate a time base equal to 1 ms
	so TIM4_PERIOD = (0.001 * 250000 - 1) = 249 */
	TIM4->PSCR			= TIM4_PRESCALER_64;

	//修改系统节拍
	TIM4->ARR			= TIME_DEVI;				//247-快了4分钟 249-慢了2分钟  248 1ms
	TIM4->SR1			= (~TIM4_FLAG_UPDATE);
	TIM4->IER			|= TIM4_IT_UPDATE;
	TIM4->CR1			|= TIM4_CR1_CEN;

	enableInterrupts();
}


/*******************************************************************************
* 名称: 
* 功能: 
* 形参:		
* 返回: 无
* 说明: 0.6us
*******************************************************************************/
#pragma optimize				=none 


void DelayUs(uint16_t nCount)
{
	//0.5us
	while (nCount--)
		;
}


/*******************************************************************************
* 名称: 
* 功能: 
* 形参:		
* 返回: 无
* 说明: 
******************************************************************************/
void SysParameterInit(void)
{
	SysInfor.bMotor1Zero = 0;
	SysInfor.bMotor2Zero = 0;
	SysInfor.bMotor3Zero = 0;
	SysInfor.bMotor4Zero = 0;

	SysInfor.bMotor1Status = M_IDLE;
	SysInfor.bMotor2Status = M_IDLE;
	SysInfor.bMotor3Status = M_IDLE;
	SysInfor.bMotor4Status = M_IDLE;

	SysInfor.bMessage	= 0;
	SysInfor.bUpdate	= 0;
	SysInfor.u16Years	= 0;
	SysInfor.u8Month	= 0;
	SysInfor.u8Day		= 0;
	SysInfor.u8Constellatory = 0;

	SysInfor.u16Years_s = 0;
	SysInfor.u8Month_s	= 0;
	SysInfor.u8Day_s	= 0;
	SysInfor.u8Constellatory_s = 0;


	SysInfor.u32SysTick = 0;
	SysInfor.bRecComplite = FALSE;
	SysInfor.u8RecPtr	= 0;



	SysInfor.u32Motor1Count = 0;
	SysInfor.u32Motor2Count = 0;
	SysInfor.u32Motor3Count = 0;
	SysInfor.u32Motor4Count = 0;
}



