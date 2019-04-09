#ifndef __LEDDRIVER_H
#define __LEDDRIVER_H

/* 头文件  -------------------------------------------------------------------*/
#include "stm8s.h"

#ifdef _MAININC_
#define EXTERN
#else
#define EXTERN extern
#endif



/*
*/

/* typedef  -----------------------------------------------------------------*/

/* Motor函数 -------------------------------------------------------------------*/
void    Motor_DriverInit(void);
int abs(int a);



#endif