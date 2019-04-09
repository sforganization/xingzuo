/**
******************************************************************************
* @file    eeprom.c
* @author  STMicroelectronics - MCD Application Team
* @version V2.0.0
* @date    07/04/2011
* @brief   EEPROM read/write routines
******************************************************************************
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
******************************************************************************
*/

#include "stm8s.h"
#include "eeprom.h"


extern u8      wColorBuf,yColorBuf;
extern u16     ContrastBuf;


/*******************************************************************************
* 名称: EEPROM_CloseSwitchPower
* 功能: 
* 形参:       
* 返回: 无
* 说明: 
*******************************************************************************/
void    EEPROM_CloseSwitchPower(void)
{ 
  u8 i;
  if(SysInfor.Other & SYS_PONSETBIT)
  {
    SysInfor.Other &= (~SYS_PONSETBIT);//分段开关关闭
    
  	for(i=0;i<16;i++)
	{
      if(i2c_write(EE_SYS_ADDR+SYS_OTHER,&SysInfor.Other,1) == 0)break;
  	}
  }
}
/*******************************************************************************
* 名称: 
* 功能: 读取E2ROM中的第一个遥控信息
* 形参:       
* 返回: 无
* 说明: 
*******************************************************************************/
void E2_ReadFirstRemote(RemoteType* remote)
{
  
  u8 i;
  //u8  *p;
  
  for(i=0;i<16;i++)
  {
    if(i2c_read((EE_CTR_BADDR + 4),&remote->pack[0],2) == 0)break;
  }
  
  for(i=0;i<16;i++)
  {
    if(i2c_read(EE_CTR_BADDR ,&remote->pack[2], EE_CTR_MOTESIZE - 2) == 0)break;
  }
  
  // 	#if Debug == 2
  // 	for(i=0; i<6; i++)
  // 	{
  // 		
  // 		my_printf(SyncPack.pack[i]);
  // 		serial_putchar(' ');
  // 	} 
  // 	#endif
}


/*******************************************************************************
* 名称: 
* 功能: 读取E2ROM中的系统信息
* 形参:       
* 返回: 无
* 说明: 
*******************************************************************************/
void E2_ReadOEMinfor(void)
{
  u8 i;
  for(i=0;i<16;i++)
  {
    if(i2c_read(EE_OEM_ADDR,(u8*)&OEMInfor.Oem,OEM_DRIVER_PACK_LENGTH) == 0)break;
  }
  for(i=0;i<16;i++)
  {
    if(i2c_read(EE_HOST_ADDR,(u8*)&OEMInfor.Host,OEM_DRIVER_PACK_LENGTH) == 0)break;
  }
  for(i=0;i<16;i++){
  	if(i2c_write(EE_OEM_ADDR,(u8*)&OEMInfor.Oem,OEM_DRIVER_PACK_LENGTH) == 0)break;
  }
  
  for(i=0;i<16;i++)
  {
	if(i2c_write(EE_HOST_ADDR,(u8*)&OEMInfor.Host,OEM_DRIVER_PACK_LENGTH) == 0)break;
  }
}

/*******************************************************************************
* 名称: E2_SaveOEMinfor
* 功能: 保存系统信息到E2ROM中
* 形参:       
* 返回: 无
* 说明: 
*******************************************************************************/
void E2_SaveOEMinfor(void)
{
  u8 i;
  for(i=0;i<16;i++){
  	if(i2c_write(EE_OEM_ADDR,(u8*)&OEMInfor.Oem,OEM_DRIVER_PACK_LENGTH) == 0)break;
  }
  
  for(i=0;i<16;i++)
  {
	if(i2c_write(EE_HOST_ADDR,(u8*)&OEMInfor.Host,OEM_DRIVER_PACK_LENGTH) == 0)break;
  }
}
/*******************************************************************************
* 名称: E2_ReadSYSinfor
* 功能: 保存系统信息到E2ROM中
* 形参:       
* 返回: 无
* 说明: 
*******************************************************************************/
void E2_ReadSYSinfor(void)
{
  u8 dat[EE_SYS_LEN + EE_RGB_LEN];
  u8 i;
  for(i=0;i<16;i++)
  {
    if(i2c_read(EE_SYS_ADDR,&dat[0],EE_SYS_LEN) == 0)break;
  }  
  for(i=0;i<16;i++)
  {
    if(i2c_read(EE_RGB_ADDR ,&dat[EE_SYS_LEN],EE_RGB_LEN) == 0)break;
  }
  
  SysInfor.MainMode    = dat[SYS_MMODEADDR];
  SysInfor.Brightness  = dat[SYS_CONTRASTADDR1];
  SysInfor.Brightness<<= 8;
  SysInfor.Brightness |= dat[SYS_CONTRASTADDR2];
  SysInfor.wColor      = dat[SYS_WCOLOR];
  SysInfor.yColor      = dat[SYS_YCOLOR];
  SysInfor.rColor      = dat[EE_SYS_LEN + SYS_RCOLOR];
  SysInfor.gColor      = dat[EE_SYS_LEN + SYS_GCOLOR];
  SysInfor.bColor      = dat[EE_SYS_LEN + SYS_BCOLOR];
  
  SysInfor.Other       = dat[SYS_OTHER];
  SysInfor.CtrLen      = dat[SYS_CTRADDR];//读取绑定遥控器数
}
/*******************************************************************************
* 名称: E2_SaveSYSinfor
* 功能: 保存系统信息到E2ROM中
* 形参:       
* 返回: 无
* 说明: 
*******************************************************************************/
void E2_SaveSYSinfor(void)
{
  u8 i;
  u8 dat[EE_SYS_LEN];
  u8 dat1[EE_RGB_LEN];
  
  dat[SYS_MMODEADDR] 	= SysInfor.MainMode;
  dat[SYS_CONTRASTADDR1]= SysInfor.Brightness>>8;
  dat[SYS_CONTRASTADDR2]= SysInfor.Brightness;
  dat[SYS_WCOLOR]		= SysInfor.wColor;
  dat[SYS_YCOLOR]		= SysInfor.yColor;
  
  dat[SYS_OTHER]		= SysInfor.Other;
  dat[SYS_CTRADDR]		= SysInfor.CtrLen;//读取绑定遥控器数
  
  dat1[SYS_RCOLOR]		= SysInfor.rColor;
  dat1[SYS_GCOLOR]		= SysInfor.gColor;
  dat1[SYS_BCOLOR]		= SysInfor.bColor;
  
  for(i=0;i<16;i++){
  	if(i2c_write(EE_SYS_ADDR,&dat[0],EE_SYS_LEN) == 0)break;
  }
  for(i=0;i<16;i++){
  	if(i2c_write(EE_RGB_ADDR,&dat1[0],EE_RGB_LEN) == 0)break;
  }
}
/*******************************************************************************
* 名称: E2_ReadKeyScene
* 功能: 
* 形参:       
* 返回: 无
* 说明: 读取情景模式
*******************************************************************************/
void E2_ReadKeyScene(u8 scenesel)
{
  u16 brightness;
  u8 dat[EE_SCE_LEN];
  u8 i, addr;
  
  addr = EE_SCE1_BADDR + scenesel * 8;	
  for(i=0;i<16;i++)
  {
    if(i2c_read(addr,&dat[0],EE_SCE_LEN) == 0)break;
  }
  for(i=0;i<16;i++)
  {
    if(i2c_read(EE_LAMPFLAG_ADDR + scenesel,&SysInfor.lSW,1) == 0)break;
  }		
  
  
  brightness  = dat[1];
  brightness<<= 8;
  brightness |= dat[2];
  if(brightness <= LIGHT_CONSTRAST && 
     brightness >= LIGHT_CONSTRASTNIGHT)
    SysInfor.Brightness = brightness;
  
  if(
     (dat[3] + dat[4]) >= LIHGT_MAXCOLOR 
       && dat[3] <= LIHGT_MAXCOLOR 
         && dat[4] <= LIHGT_MAXCOLOR )
  {
    SysInfor.wColor = dat[3];
    SysInfor.yColor = dat[4];
    SysInfor.rColor = dat[5];
    SysInfor.gColor = dat[6];
    SysInfor.bColor = dat[7];
  }
  if(dat[0] == M_DRI_ON)
  {
    SysInfor.MainMode = M_DRI_ON;
    if(SysInfor.ShowCnt == 0)
    {
      if(SysInfor.lSW & RGB_ON)
        LED_Update_LightBuf(SysInfor.wColor,SysInfor.yColor,SysInfor.rColor,SysInfor.gColor,SysInfor.bColor,SysInfor.Brightness);	
      else
        LED_Update_LightBuf(SysInfor.wColor,SysInfor.yColor,0,0,0,SysInfor.Brightness);
    }
  }
  else if(dat[0] == M_DRI_OFF)
  {
    SysInfor.MainMode = M_DRI_OFF;
    if(SysInfor.lSW & RGB_ON)
      LED_Update_LightBuf(0,0,SysInfor.rColor,SysInfor.gColor,SysInfor.bColor,SysInfor.Brightness);
    else 		
      LED_Update_LightBuf(SysInfor.wColor,SysInfor.yColor,SysInfor.rColor,SysInfor.gColor,SysInfor.bColor,0);
  }
}
/*******************************************************************************
* 名称: E2_ReadKeySave
* 功能: 
* 形参:       
* 返回: 无
* 说明: 保存情景模式
*******************************************************************************/
void E2_ReadKeySave(u8 scenesel)
{
  u8 i,addr;
  u8 dat[EE_SCE_LEN];
  
  addr = EE_SCE1_BADDR + scenesel * 8;
  
  if(SysInfor.MainMode == M_DRI_OFF){
	dat[0] 	= M_DRI_OFF;
  }else{
    dat[0] 	= M_DRI_ON;
  }
  dat[1]	= SysInfor.Brightness>>8;
  dat[2]	= SysInfor.Brightness;
  dat[3]	= SysInfor.wColor;
  dat[4]	= SysInfor.yColor;
  dat[5]	= SysInfor.rColor;
  dat[6]	= SysInfor.gColor;
  dat[7]	= SysInfor.bColor;
  for(i=0;i<16;i++){
  	if(i2c_write(addr,&dat[0],EE_SCE_LEN) == 0)break;
  }
  for(i=0;i<16;i++){
  	if(i2c_write(EE_LAMPFLAG_ADDR + scenesel,&SysInfor.lSW,1) == 0)break;
  }
  
  SysInfor.ShowCnt = SHOW_CNT1;
}

/*******************************************************************************
* 名称: E2_RemoteSave
* 功能: 保存遥控器ID到E2ROM中
* 形参:       
* 返回: 无
* 说明: 
*******************************************************************************/
void E2_RemoteSave(u32 remote,u8 lamp)
{
  u8 i;
  u16 addr;
  u8  dat[EE_CTR_MOTESIZE];
  
  if(lamp == LAMP_ALL)lamp = 1;
  
  if(SysInfor.CtrLen < EE_CTR_MOTELEN)//可绑定遥控器数没有满
  {
    addr = EE_CTR_BADDR + (SysInfor.CtrLen<<3);
    SysInfor.CtrLen++;
  }
  else
  {
    addr = EE_CTR_LADDR;
  }
  
  dat[0] = remote>>24;
  dat[1] = remote>>16;
  dat[2] = remote>>8;
  dat[3] = remote;
  dat[4] = lamp>>8;
  dat[5] = lamp;
  
  for(i=0;i<16;i++){
  	if(i2c_write(addr,&dat[0],EE_CTR_MOTESIZE) == 0)break;
  }
  delay_us(5000);//5ms
  for(i=0;i<16;i++)
  {
	if(i2c_write(EE_SYS_ADDR+SYS_CTRADDR,&SysInfor.CtrLen,1) == 0)break;
  }
}
/*******************************************************************************
* 名称: E2_ClearRemote_All
* 功能: 清除所有对码
* 形参:       
* 返回: 无
* 说明: 
*******************************************************************************/
void E2_ClearRemote_All(void)
{
  u8 i;
  SysInfor.CtrLen = 0;
  for(i=0;i<16;i++){
  	if(i2c_write(EE_SYS_ADDR+SYS_CTRADDR,&SysInfor.CtrLen,1) == 0)break;
  }
}
/*******************************************************************************
* 名称: E2_RemoteCheck
* 功能: 检测遥控器ID是否绑定
* 形参:       
* 返回: 无
* 说明: 
*******************************************************************************/
u8 E2_RemoteCheck(u32 remote,u8 lamp)
{
  u8  i,j,rev=0;
  u8  dat[EE_CTR_MOTESIZE];
  u32 remoteid;
  u16 rlampid;
  u16 addr = EE_CTR_BADDR;
  
  for(i=0;i<SysInfor.CtrLen;i++)
  {
  	for(j=0;j<16;j++)
  	{
      if(i2c_read(addr,&dat[0],EE_CTR_MOTESIZE) == 0)break;
  	}
    remoteid  = dat[0];
    remoteid<<= 8;
    remoteid |= dat[1];
    remoteid<<= 8;
    remoteid |= dat[2];
    remoteid<<= 8;
    remoteid |= dat[3];
    rlampid   = dat[4];
    rlampid <<= 8;
    rlampid  |= dat[5];
    addr += 8;
    
    if(remoteid == remote)
    {
      rev = 2;
      if(lamp == LAMP_ALL || lamp == rlampid)//所有区域
      {
        return 1;
      }
    }
  }
  return rev;
}


