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

#define EE_OEM_ADDR             0//OEM��ַ
#define EE_HOST_ADDR            8//OEM��ַ
/*
#define EE_OEM_DRIVERTYPE       0//�豸���ʹ洢��ַ
#define EE_OEM_DRIVERID1        1//�豸ID1�洢��ַ
#define EE_OEM_DRIVERID2        2//�豸ID2�洢��ַ
#define EE_OEM_DRIVERID3        3//�豸ID3�洢��ַ
#define EE_OEM_DRIVERID4        4//�豸ID4�洢��ַ
#define EE_OEM_DRIVERLAYER      5//�豸���ڲ�

#define EE_HOST_DRIVERTYPE      6 //�������ʹ洢��ַ
#define EE_HOST_DRIVERID1       7 //����ID1�洢��ַ
#define EE_HOST_DRIVERID2       8 //����ID2�洢��ַ
#define EE_HOST_DRIVERID3       9 //����ID3�洢��ַ
#define EE_HOST_DRIVERID4       10//����ID4�洢��ַ
#define EE_HOST_DRIVERLAYER     11//�������ڲ�
*/

#define EE_CTR_BADDR            16//��ң������ַ
#define EE_CTR_EADDR            80//��Ŀ64/8=8
#define EE_CTR_LADDR 			72//���һ��ң������ַ

#define EE_CTR_MOTELEN          8 //�ɰ�ң������
#define EE_CTR_MOTESIZE         6 //ң����ID=4byte,����+��=2byte
 
#define EE_SYS_ADDR             128//ϵͳ��Ϣ��ַ
#define EE_SYS_LEN				    7//WY RGB ��ͬϵͳ��Ϣ����
#define SYS_MMODEADDR        	0//��ģʽ
#define SYS_CONTRASTADDR1    	1//���ȱ����ַ1
#define SYS_CONTRASTADDR2    	2//���ȱ����ַ2
#define SYS_WCOLOR           	3//�׹�
#define SYS_YCOLOR           	4//�ƹ�
#define SYS_OTHER            	5//le������Ϣ
#define SYS_CTRADDR          	6//��ң��������ַ

#define EE_RGB_ADDR             136//ϵͳ��Ϣ��ַ
#define EE_RGB_LEN				3//RGB��Ϣ����
#define SYS_RCOLOR           	0//��
#define SYS_GCOLOR           	1//��
#define SYS_BCOLOR           	2//��

#define EE_SCE_LEN				     8 //
#define EE_SCE1_BADDR               144//һ���龰  1  ��ͨң���龰 
// #define EE_SCE1_MODE             144//����
// #define EE_SCE1_BRIGH            145//����H
// #define EE_SCE1_BRIGL            146//����L
// #define EE_SCE1_WCOL             147//W
// #define EE_SCE1_YCOL             148//Y
// #define EE_SCE1_RCOL             149//R
// #define EE_SCE1_GCOL             150//G
// #define EE_SCE1_BCOL             151//B
#define EE_SCE2_BADDR            152//һ���龰 2
#define EE_SCE3_BADDR            160//һ���龰 3
#define EE_SCE4_BADDR            168//һ���龰 4
#define EE_SCE5_BADDR            176//һ���龰 5  ���⿪���龰1
#define EE_SCE6_BADDR            184//һ���龰 6  ���⿪���龰2
#define EE_SCE7_BADDR            192//һ���龰 7  ���⿪���龰3
#define EE_SCE8_BADDR            200//һ���龰 8  ���⿪���龰4


#define EE_LAMPFLAG_ADDR          208//����״̬��־ 
#define EE_LAMPFLAG1_ADDR         208//����״̬��־
#define EE_LAMPFLAG2_ADDR         209//����״̬��־ 
#define EE_LAMPFLAG3_ADDR         210//����״̬��־ 
#define EE_LAMPFLAG4_ADDR         211//����״̬��־ 
#define EE_LAMPFLAG5_ADDR         212//����״̬��־
#define EE_LAMPFLAG6_ADDR         213//����״̬��־ 
#define EE_LAMPFLAG7_ADDR         214//����״̬��־ 
#define EE_LAMPFLAG8_ADDR         215//����״̬��־ 

#define SYS_PONSETBIT           0x01       //�ϵ�ֶο���
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

