#ifndef __OCTASK_H
#define __OCTASK_H

/* 头文件  -------------------------------------------------------------------*/
#include "stm8s.h"

#ifdef _MAININC_
#define EXTERN
#else
#define EXTERN extern
#endif




#define OC_DIR		P0DIR
#define OC_PORT	  P0
#define OC_PIN  	BIT5
#define OC_IN1()	OC_PORT |= OC_PIN
#define OC_IOCONFIG()     P0CON = 0x70 | OC_PIN; OC_DIR |= OC_PIN ; OC_IN1()

#define OC_TIMES_POWEROFF		100
#define OC_TIMES_BROKEN 		3000




void OC_TaskPowerOff(void);
void OC_TaskTick(void);

#endif  //光耦