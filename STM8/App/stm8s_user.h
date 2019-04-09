#ifndef __STM8_USER_H
#define __STM8_USER_H

/* 头文件  -------------------------------------------------------------------*/
#include "stm8s.h"

#ifdef _MAININC_
#define EXTERN
#else
#define EXTERN extern
#endif


/* 板子接口  -----------------------------------------------------------------*/  

/* enum  ---------------------------------------------------------------------*/

/* 预定义  -------------------------------------------------------------------*/

//------------------------------------------------------
//max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 250000 = 1.024 ms
//min time base is 0.008 ms if TIM4_PERIOD = 1   --> (  1 + 1) / 250000 = 0.008 ms
#define TIME_DEVI  62  //设置时钟分频   (124+1)/250000 = 0.25ms      

#define MOTOR_COVER_TIME  4 //设置电机电平信号翻转频率              与定时器分频相关 //0.5ms x 2 =1ms相应修改时钟中断重载值 SysTickInit();


#define RECIVE_MAX  8     

/* typedef  -----------------------------------------------------------------*/
//系统运行信息
typedef struct //
{
   uv16 SysTick;   //系统节拍


   char bMessage;    //消息是否有效  
   char bMotor1Zero; //电机1是否到零点
   char bMotor2Zero; //电机2是否到零点
   char bMotor3Zero; //电机3是否到零点
   char bMotor4Zero; //电机4是否到零点

   
   char bMotor1Status; //电机1状态
   char bMotor2Status; //电机2状态
   char bMotor3Status; //电机3状态
   char bMotor4Status; //电机4状态

   
   char u8DetectM1Timer; //电机1零点检测防抖时间
   char u8DetectM2Timer; //电机1零点检测防抖时间
   char u8DetectM3Timer; //电机1零点检测防抖时间
   char u8DetectM4Timer; //电机1零点检测防抖时间

   
   u32 volatile  u32Motor1Count; //电机1脉冲数*2
   u32 volatile  u32Motor2Count; //电机2脉冲数*2
   u32 volatile  u32Motor3Count; //电机3脉冲数*2
   u32 volatile  u32Motor4Count; //电机4脉冲数*2
   
   char volatile bUpdate;     //数据是否更新
   char volatile bStateMode;       //电机模式 升降
   
   u32 u32SysTick; //系统节拍
   char u8Constellatory;    //星座
   unsigned int u16Years; 
   char u8Month;
   char u8Day;

   char u8Constellatory_s;    //星座
   unsigned int u16Years_s; 
   char u8Month_s;
   char u8Day_s;

   char u8Recive[RECIVE_MAX];
   char u8RecPtr;            //接收数组偏移
   bool bRecComplite;       //串口接收完成
   
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


/* 全局变量  -----------------------------------------------------------------*/
EXTERN  typedef_SysInformation   SysInfor;

/* 函数接口  -----------------------------------------------------------------*/
void            DelayUs(uint16_t nCount);
void            DelayMs(uint16_t nCount);
u8               GetCRC(u8 *buf,u8 len);
void            SysResetOEMinformation(void);
void            SysParameterInit(void);
void            SysTickInit(void);


#endif
