#ifndef __LEDDRIVER_H
#define __LEDDRIVER_H

/* ͷ�ļ�  -------------------------------------------------------------------*/
#include "stm8s.h"

#ifdef _MAININC_
#define EXTERN
#else
#define EXTERN extern
#endif



/*
*/

/* typedef  -----------------------------------------------------------------*/

/* Motor���� -------------------------------------------------------------------*/
void    Motor_DriverInit(void);
int abs(int a);



#endif