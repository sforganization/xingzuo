#include "KeyControl.h"


/*******************************************************************************
* ����: 
* ����: 
* �β�:       
* ����: ��
* ˵��: 
******************************************************************************/
void    Board_KeyInit(void)
{
  KeyInfor.Message = NOKEY;
  
  GPIO_Init(KEY1_PORT, KEY1_GPIO_PIN, GPIO_MODE_IN_FL_NO_IT);
  GPIO_Init(KEY2_PORT, KEY2_GPIO_PIN, GPIO_MODE_IN_FL_NO_IT);
}
/*******************************************************************************
* ����: 
* ����: 
* �β�:       
* ����: ��
* ˵��: 
******************************************************************************/
void    Board_KeyScanf(void)
{
  u8 tempi = NOKEY;
  
  if(GPIO_ReadInputPin(KEY1_PORT,KEY1_GPIO_PIN) == KEYDOWN)
  {
    tempi |= KEY1;
  }
  if(GPIO_ReadInputPin(KEY2_PORT,KEY2_GPIO_PIN) == KEYDOWN)
  {
    tempi |= KEY2;
  }
  if (tempi == NOKEY)
  { //no key
    if(KeyInfor.IdleCount < KEYSR_120S)
    {
      KeyInfor.IdleCount ++;
      KeyInfor.HoldCount=0;  // had release key	
    }
    return;
  }
  KeyInfor.IdleCount=0;        // KeyMessage
  KeyInfor.TimeOutCount=0;
  if (KeyInfor.HoldCount==0)
  {
    KeyInfor.Message=tempi;
    KeyInfor.HoldCount ++;//;
  } 
  else if (KeyInfor.HoldCount>=KEYSR_2S)
  {
    KeyInfor.Message= tempi | 0x80;
    KeyInfor.HoldCount = KEYSR_2S;// restart 1 sencond
  }
  else 
  {
    KeyInfor.HoldCount ++;
  }
}
/*******************************************************************************
* ����: 
* ����: 
* �β�:       
* ����: ��
* ˵��: 
******************************************************************************/
void    KeyMainNormalMode(void)
{
  if(KeyInfor.Message == KEY2 || KeyInfor.Message == HOLD2S_KEY2)
  {    
    if(SysInfor.MainMode == M_LIGHT_OFF)
    {
      SysInfor.MainMode = M_LIGHT_ON;
      LED_Update_LightBuf(SysInfor.wColor,SysInfor.yColor,SysInfor.Contrast);
    }
    else                                
    {
      SysInfor.MainMode = M_LIGHT_OFF;
      LED_Update_LightBuf(SysInfor.wColor,SysInfor.yColor,0);
    }
    SysInfor.SysSave = TRUE;
  }
  //else
  KeyInfor.Message = NOKEY; 
  
}

/*******************************************************************************
* ����: 
* ����: 
* �β�:       
* ����: ��
* ˵��: 
******************************************************************************/
void    Board_KeyTask(void)
{
  switch(OEMInfor.DriverType)
  {
    case DRIVER_CENTER://�ܿ����豸
    break;
    case DRIVER_CONTROL://ң����
    break;
    case DRIVER_LIGHT://��
      KeyMainNormalMode();
    break;
    default:
    break;
  }
}
