#ifndef __REMAP_H
#define __REMAP_H

#include "stm8s.h"

#define AFR_ADDRESS     0x4803

typedef enum{
  Default_AFR7=(uint8_t)0x7f,
  Default_AFR6=(uint8_t)0xbf,
  Default_AFR5=(uint8_t)0xdf,
  Default_AFR4=(uint8_t)0xef,
  Default_AFR3=(uint8_t)0xf7,
  Default_AFR2=(uint8_t)0xfb,
  Default_AFR1=(uint8_t)0xfd,
  Default_AFR0=(uint8_t)0xfe,
}Default_Function_TypeDef;


typedef enum{
  AFR7=(uint8_t)0x80,
//0: AFR7 remapping option inactive: Default alternate functions(1).
//1: Port C3 alternate function = TIM1_CH1N;
//   port C4 alternate function = TIM1_CH2N.
  AFR6=(uint8_t)0x40,//Reserved.
  AFR5=(uint8_t)0x20,//Reserved.
  AFR4=(uint8_t)0x10,
//0: AFR4 remapping option inactive: Default alternate functions(1).
//1: Port B4 alternate function = ADC_ETR;
//   port B5 alternate function = TIM1_BKIN.
  AFR3=(uint8_t)0x08,
//0: AFR3 remapping option inactive: Default alternate function(1).
//1: Port C3 alternate function = TLI.
  AFR2=(uint8_t)0x04,//Reserved
  AFR1=(uint8_t)0x02,
//0: AFR1 remapping option inactive: Default alternate functions(1).
//1: Port A3 alternate function = SPI_NSS; 
//   port D2 alternate function = TIM2_CH3.
  AFR0=(uint8_t)0x01,
//0: AFR0 remapping option inactive: Default alternate functions(1).
//1: Port C5 alternate function = TIM2_CH1; 
//   port C6 alternate function = TIM1_CH1; 
//   port C7 alternate function = TIM1_CH2.
}Remap_Function_TypeDef;

void AlternateFunctionRemapping(Remap_Function_TypeDef Function);
void DefaultFunctionRemapping(Default_Function_TypeDef Function);


#endif

