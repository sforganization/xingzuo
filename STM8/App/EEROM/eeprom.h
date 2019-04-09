/**
  ******************************************************************************
  * @file    eeprom.h
  * @author  STMicroelectronics - MCD Application Team
  * @version V2.0.0
  * @date    07/04/2011
  * @brief   EEPROM read/write routines - header
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

#ifndef EEPROM2_H
#define EEPORM2_H


#include "WirlessApp.h"

#define EEPROM_SIZE             256
    
#ifdef _MAININC_
#define EXTERN
#else
#define EXTERN extern
#endif    

#include "WirlessApp.h"

#define EE_OEM_ADDR             0//OEM地址
#define EE_HOST_ADDR            8//OEM地址
/*
#define EE_OEM_DRIVERTYPE       0//设备类型存储地址
#define EE_OEM_DRIVERID1        1//设备ID1存储地址
#define EE_OEM_DRIVERID2        2//设备ID2存储地址
#define EE_OEM_DRIVERID3        3//设备ID3存储地址
#define EE_OEM_DRIVERID4        4//设备ID4存储地址
#define EE_OEM_DRIVERLAYER      5//设备所在层

#define EE_HOST_DRIVERTYPE      6 //主机类型存储地址
#define EE_HOST_DRIVERID1       7 //主机ID1存储地址
#define EE_HOST_DRIVERID2       8 //主机ID2存储地址
#define EE_HOST_DRIVERID3       9 //主机ID3存储地址
#define EE_HOST_DRIVERID4       10//主机ID4存储地址
#define EE_HOST_DRIVERLAYER     11//主机所在层
*/

#define EE_CTR_BADDR            16//绑定遥控器地址
#define EE_CTR_EADDR            80//数目64/8=8
#define EE_CTR_LADDR 			72//最后一个遥控器地址

#define EE_CTR_MOTELEN          8 //可绑定遥控器数
#define EE_CTR_MOTESIZE         6 //遥控器ID=4byte,区域+灯=2byte
 
#define EE_SYS_ADDR             128//系统信息地址
#define EE_SYS_LEN				    7//WY RGB 共同系统信息长度
#define SYS_MMODEADDR        	0//主模式
#define SYS_CONTRASTADDR1    	1//亮度保存地址1
#define SYS_CONTRASTADDR2    	2//亮度保存地址2
#define SYS_WCOLOR           	3//白光
#define SYS_YCOLOR           	4//黄光
#define SYS_OTHER            	5//le其他信息
#define SYS_CTRADDR          	6//绑定遥控器数地址

#define EE_RGB_ADDR             136//系统信息地址
#define EE_RGB_LEN				3//RGB信息长度
#define SYS_RCOLOR           	0//红
#define SYS_GCOLOR           	1//绿
#define SYS_BCOLOR           	2//蓝

#define EE_SCE_LEN				     8 //
#define EE_SCE1_BADDR               144//一键情景  1  普通遥控情景 
// #define EE_SCE1_MODE             144//开关
// #define EE_SCE1_BRIGH            145//亮度H
// #define EE_SCE1_BRIGL            146//亮度L
// #define EE_SCE1_WCOL             147//W
// #define EE_SCE1_YCOL             148//Y
// #define EE_SCE1_RCOL             149//R
// #define EE_SCE1_GCOL             150//G
// #define EE_SCE1_BCOL             151//B
#define EE_SCE2_BADDR            152//一键情景 2
#define EE_SCE3_BADDR            160//一键情景 3
#define EE_SCE4_BADDR            168//一键情景 4
#define EE_SCE5_BADDR            176//一键情景 5  随意开关情景1
#define EE_SCE6_BADDR            184//一键情景 6  随意开关情景2
#define EE_SCE7_BADDR            192//一键情景 7  随意开关情景3
#define EE_SCE8_BADDR            200//一键情景 8  随意开关情景4


#define EE_LAMPFLAG_ADDR          208//开关状态标志 
#define EE_LAMPFLAG1_ADDR         208//开关状态标志
#define EE_LAMPFLAG2_ADDR         209//开关状态标志 
#define EE_LAMPFLAG3_ADDR         210//开关状态标志 
#define EE_LAMPFLAG4_ADDR         211//开关状态标志 
#define EE_LAMPFLAG5_ADDR         212//开关状态标志
#define EE_LAMPFLAG6_ADDR         213//开关状态标志 
#define EE_LAMPFLAG7_ADDR         214//开关状态标志 
#define EE_LAMPFLAG8_ADDR         215//开关状态标志 

#define SYS_PONSETBIT           0x01       //上电分段开关
/*---FUNCTIONS---*/
void EEPROM_Unlock(void);
void EEPROM_CloseSwitchPower(void);
void E2_SaveSYSinfor(void);
void E2_ReadSYSinfor(void);
void E2_SaveOEMinfor(void);
void E2_ReadOEMinfor(void);
void E2_ReadFirstRemote(RemoteType* remote);
void E2_ClearRemote_All(void);
void E2_RemoteSave(u32 remoteid,u8 lampid);
u8   E2_RemoteCheck(u32 remoteid,u8 lampid);

void E2_ReadKeyScene(u8 scenesel);
void E2_ReadKeySave(u8 scenesel);

#endif

