#ifndef __STM8_USER_H
#define __STM8_USER_H

/* ͷ�ļ�  -------------------------------------------------------------------*/
#include "stm8s.h"

#ifdef _MAININC_
#define EXTERN
#else
#define EXTERN extern
#endif


/* ���ӽӿ�  -----------------------------------------------------------------*/  

/* enum  ---------------------------------------------------------------------*/

/* Ԥ����  -------------------------------------------------------------------*/

//------------------------------------------------------
//max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 250000 = 1.024 ms
//min time base is 0.008 ms if TIM4_PERIOD = 1   --> (  1 + 1) / 250000 = 0.008 ms
#define TIME_DEVI  62  //����ʱ�ӷ�Ƶ   (124+1)/250000 = 0.25ms      

#define MOTOR_COVER_TIME  4 //���õ����ƽ�źŷ�תƵ��              �붨ʱ����Ƶ��� //0.5ms x 2 =1ms��Ӧ�޸�ʱ���ж�����ֵ SysTickInit();


#define RECIVE_MAX  8     

/* typedef  -----------------------------------------------------------------*/
//ϵͳ������Ϣ
typedef struct //
{
   uv16 SysTick;   //ϵͳ����


   char bMessage;    //��Ϣ�Ƿ���Ч  
   char bMotor1Zero; //���1�Ƿ����
   char bMotor2Zero; //���2�Ƿ����
   char bMotor3Zero; //���3�Ƿ����
   char bMotor4Zero; //���4�Ƿ����

   
   char bMotor1Status; //���1״̬
   char bMotor2Status; //���2״̬
   char bMotor3Status; //���3״̬
   char bMotor4Status; //���4״̬

   
   char u8DetectM1Timer; //���1��������ʱ��
   char u8DetectM2Timer; //���1��������ʱ��
   char u8DetectM3Timer; //���1��������ʱ��
   char u8DetectM4Timer; //���1��������ʱ��

   
   u32 volatile  u32Motor1Count; //���1������*2
   u32 volatile  u32Motor2Count; //���2������*2
   u32 volatile  u32Motor3Count; //���3������*2
   u32 volatile  u32Motor4Count; //���4������*2
   
   char volatile bUpdate;     //�����Ƿ����
   char volatile bStateMode;       //���ģʽ ����
   
   u32 u32SysTick; //ϵͳ����
   char u8Constellatory;    //����
   unsigned int u16Years; 
   char u8Month;
   char u8Day;

   char u8Constellatory_s;    //����
   unsigned int u16Years_s; 
   char u8Month_s;
   char u8Day_s;

   char u8Recive[RECIVE_MAX];
   char u8RecPtr;            //��������ƫ��
   bool bRecComplite;       //���ڽ������
   
}typedef_SysInformation;

typedef enum  MOTOR_STATUS
{
  M_IDLE = 0,
  M_ZERO,
  M_RUN,
  M_READY,
}MOTOR_STATUS_EN;  
  
typedef enum  MOTOR_MODE
{
  M_MODE_UP = 0,
  M_MODE_DOWN,
}MOTOR_MODE_EN;  


/* ȫ�ֱ���  -----------------------------------------------------------------*/
EXTERN  typedef_SysInformation   SysInfor;

/* �����ӿ�  -----------------------------------------------------------------*/
void            DelayUs(uint16_t nCount);
void            DelayMs(uint16_t nCount);
u8               GetCRC(u8 *buf,u8 len);
void            SysResetOEMinformation(void);
void            SysParameterInit(void);
void            SysTickInit(void);


#endif
