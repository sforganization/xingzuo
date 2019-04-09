#include "OCTask.h"


/*******************************************************************************
 * 名称: RestartInit
 * 功能: 
 * 形参:       
 * 返回: 无
 * 说明: 
 ******************************************************************************/
void RePowerOnInit(void)
{
  if(SysInfor.Other&SYS_PONSETBIT)//分段开关打开
  {
    if(SysInfor.wColor == LIHGT_MAXCOLOR && SysInfor.yColor == LIHGT_MAXCOLOR && SysInfor.Brightness != LIGHT_CONSTRASTNIGHT)
    {
      SysInfor.Brightness = LIGHT_CONSTRASTNIGHT;
    }
    else 
    {
      SysInfor.Brightness = LIGHT_CONSTRAST;
      if(SysInfor.wColor != LIHGT_MINCOLOR && SysInfor.yColor != LIHGT_MINCOLOR)
      {
        SysInfor.wColor = LIHGT_MAXCOLOR;
        SysInfor.yColor = LIHGT_MINCOLOR;
      }
      else if(SysInfor.wColor != LIHGT_MINCOLOR)
      {
        SysInfor.wColor = LIHGT_MINCOLOR;
        SysInfor.yColor = LIHGT_MAXCOLOR;
      }else{
        SysInfor.wColor = LIHGT_MAXCOLOR;
        SysInfor.yColor = LIHGT_MAXCOLOR;
        SysInfor.Sync   = TRUE;
      }
    }
  }
  SysInfor.MainMode   = M_DRI_PON;
  SysInfor.SwTick     = LIGHT_SWITCH_TIME;      //分段开关
  SysInfor.TaskTimer  = LIGHT_CODE_TIME;        //对码时间
  SysInfor.CmdCnt     = 0;//对码，清码计数清零
  SysInfor.ShowCnt    = 0;
  SysInfor.ShowTimer  = 0;
  SysInfor.lSW		= RGB_ON;
  E2_SaveSYSinfor();
  Lamp_Update_Light(SysInfor.wColor,SysInfor.yColor,SysInfor.rColor,SysInfor.gColor,SysInfor.bColor,SysInfor.Brightness);
}
/*******************************************************************************
 * 名称: OC_TaskTick
 * 功能: 
 * 形参:       
 * 返回: 无
 * 说明: 
 ******************************************************************************/
void OC_TaskTick(void)
{
	static u8 mOPIN;

	if((OC_PORT & OC_PIN) == mOPIN)
	{
		if(SysInfor.OptCnt < OC_TIMES_BROKEN)SysInfor.OptCnt++;
	}else{
		if(SysInfor.OptCnt >= OC_TIMES_POWEROFF)
		{
			OC_TaskPowerOff();
		}
		mOPIN = OC_PORT & OC_PIN;
		SysInfor.OptCnt = 0;
	}
}
/*******************************************************************************
 * 名称: OC_TaskPowerOff
 * 功能: 
 * 形参:       
 * 返回: 无
 * 说明: 
 ******************************************************************************/
void OC_TaskPowerOff(void)
{
	if(SysInfor.MainMode == M_LIGHT_OFF)
	{
		SysInfor.Other &= ~SYS_PONSETBIT;					 //分段开关关闭
		RePowerOnInit();
	}
	else
	{
		SysInfor.Other   |= SYS_PONSETBIT;					 //分段开关打开
		RePowerOnInit();
	}
}


