#include "OCTask.h"


/*******************************************************************************
 * ����: RestartInit
 * ����: 
 * �β�:       
 * ����: ��
 * ˵��: 
 ******************************************************************************/
void RePowerOnInit(void)
{
  if(SysInfor.Other&SYS_PONSETBIT)//�ֶο��ش�
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
  SysInfor.SwTick     = LIGHT_SWITCH_TIME;      //�ֶο���
  SysInfor.TaskTimer  = LIGHT_CODE_TIME;        //����ʱ��
  SysInfor.CmdCnt     = 0;//���룬�����������
  SysInfor.ShowCnt    = 0;
  SysInfor.ShowTimer  = 0;
  SysInfor.lSW		= RGB_ON;
  E2_SaveSYSinfor();
  Lamp_Update_Light(SysInfor.wColor,SysInfor.yColor,SysInfor.rColor,SysInfor.gColor,SysInfor.bColor,SysInfor.Brightness);
}
/*******************************************************************************
 * ����: OC_TaskTick
 * ����: 
 * �β�:       
 * ����: ��
 * ˵��: 
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
 * ����: OC_TaskPowerOff
 * ����: 
 * �β�:       
 * ����: ��
 * ˵��: 
 ******************************************************************************/
void OC_TaskPowerOff(void)
{
	if(SysInfor.MainMode == M_LIGHT_OFF)
	{
		SysInfor.Other &= ~SYS_PONSETBIT;					 //�ֶο��عر�
		RePowerOnInit();
	}
	else
	{
		SysInfor.Other   |= SYS_PONSETBIT;					 //�ֶο��ش�
		RePowerOnInit();
	}
}


