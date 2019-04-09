#ifndef __KEYCONTROL_H_
#define __KEYCONTROL_H_

/* 头文件  -------------------------------------------------------------------*/
#include "stm8s.h"

#ifdef _MAININC_
#define EXTERN
#else
#define EXTERN extern
#endif


/* 板子接口  -----------------------------------------------------------------*/
#define KEY1_PORT       (GPIOA)
#define KEY1_GPIO_PIN   (GPIO_PIN_2)
#define KEY2_PORT       (GPIOB)
#define KEY2_GPIO_PIN   (GPIO_PIN_4)
#define KEYDOWN          RESET

/* typedef  ------------------------------------------------------------------*/
typedef struct 
{
   u16  IdleCount;      //for switch system mode 
   u16  HoldCount;      //KeyInfor.HoldCount
   u16  TimeOutCount;   //SysInfor
   u8   Message;
}typedef_KeyInformation;

/* enum  ---------------------------------------------------------------------*/
enum DefineKEY //SpO2CTR.SystemState
{
  KEY1            = 0x1,
  KEY2            = 0x2,
  KEY1_2          = 0x3,
  HOLD2S_KEY1     = 0x80 | 0x1,
  HOLD2S_KEY2     = 0x80 | 0x2,
  HOLD2S_KEY1_2   = 0x80 | 0x3,
  NOKEY           = 0,
};
#define   KEYSR          16// Hz
#define   KEYSR_500MS    (KEYSR>>1)// Hz
#define   KEYSR_1S       (KEYSR)// Hz
#define   KEYSR_1500MS   (KEYSR+KEYSR_500MS)// Hz
#define   KEYSR_2S       (KEYSR*2)// Hz
#define   KEYSR_3S       (KEYSR*3)// Hz
#define   KEYSR_5S       (KEYSR*5)// Hz
#define   KEYSR_10S      (KEYSR*10)// Hz
#define   KEYSR_30S      (KEYSR*30)// Hz
#define   KEYSR_60S      (KEYSR*60)// Hz
#define   KEYSR_120S     (KEYSR*120)// Hz
/* 全局变量  -----------------------------------------------------------------*/
EXTERN  typedef_KeyInformation   KeyInfor;

/* 函数接口  -----------------------------------------------------------------*/
void            Board_KeyInit(void);
void            Board_KeyScanf(void);
void            Board_KeyTask(void);

#endif