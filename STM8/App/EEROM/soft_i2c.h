
#ifndef SOFT_I2C_H
#define SOFT_I2C_H
#include "stm8s.h"

#ifdef _MAININC_
#define EXTERN
#else
#define EXTERN extern
#endif   



//e2rom
#define I2C_ADDR_WRITE	0xA0
#define I2C_ADDR_READ 	0xA1 

#define I2C_PIN  GPIOB
#define I2C_SCL  GPIO_PIN_4
#define I2C_SDA  GPIO_PIN_5
#define IIC_SCL_H      GPIO_WriteHigh(I2C_PIN, I2C_SCL)
#define IIC_SCL_L      GPIO_WriteLow(I2C_PIN, I2C_SCL)
#define IIC_SDA_H      GPIO_WriteHigh(I2C_PIN, I2C_SDA)
#define IIC_SDA_L      GPIO_WriteLow(I2C_PIN, I2C_SDA)
#define Get_I2C_SDA          GPIO_ReadInputPin(I2C_PIN, I2C_SDA)
#define Set_I2C_SCL_Out      GPIO_Init(I2C_PIN, I2C_SCL, GPIO_MODE_OUT_PP_HIGH_FAST)
#define Set_I2C_SDA_Out      GPIO_Init(I2C_PIN, I2C_SDA, GPIO_MODE_OUT_PP_HIGH_FAST)
#define Set_I2C_SDA_In       GPIO_Init(I2C_PIN, I2C_SDA, GPIO_MODE_IN_FL_NO_IT)

#define IIC_SDA_READ ((I2C_PIN->IDR&I2C_SDA) != 0)//输入SDA 



#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767  



//Mini STM32开发板使用的是24c02，所以定义EE_TYPE为AT24C02
#define EE_TYPE AT24C02


//IIC所有操作函数
void delay_us(uint16_t nCount);
void IIC_Init(void);                           //IIC的IO口				 
void IIC_Start(void);				//IIC开始信号
void IIC_Stop(void);	  			//IIC停止信号
bool IIC_Send_Byte(u8 sdata);			//IIC发送一个字节
bool IIC_Wait_Ack(void); 		        //IIC等待ACK信号
void IIC_Ack(void);			        //IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号
u8 IIC_Read_Byte(bool nend);


EXTERN bool E2_WriteOneByte(u8 waddr,u8 wdata);
EXTERN bool E2_ReadOneByte(u8 raddr,u8* rdata);

bool i2c_write(u8 waddr,u8 *wdata,u8 len);
bool i2c_read(u8 raddr,u8 *rdata,u8 len);
#endif
