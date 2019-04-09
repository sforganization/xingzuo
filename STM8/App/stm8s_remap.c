#include "stm8s_remap.h"




/*******************************************************************************
* 名称: AlternateFunctionRemapping
* 功能: 选功能重映射的设置
* 形参: Function 需要重映射的功能      
* 返回: 无
* 说明: 如果调试需要打印数据的时候
         在自定义宏的地方添加#define DEBUG_AFR即可，下载程序后只有第一次执行
         打印出来设置前的功能才是对的，执行完之前就被写进flash,如果不修改的话，
         每次都出来的数据都是一样，所以只执行一次就行了，建议用的时候，就在调
         试的时候进行执行一次就可以，以后都不需要出现了，除非再次更改。
         在调用AlternateFunctionRemapping函数之前需要初始化串口函数Uart_Init
         这些设置写进flash,运行一次即可,在调试的时候运行即可
******************************************************************************/

void AlternateFunctionRemapping(Remap_Function_TypeDef Function)
{
  uint8_t Function_temp;
  
  FLASH_Unlock(FLASH_MEMTYPE_DATA);/*要对选项字节写操作，必须要先解锁FLASH*/
  while(!(FLASH->IAPSR & FLASH_IAPSR_DUL));/*等待解锁完毕*/
  /*备选功能重映射的设置可以同时写多个不会被覆盖，因此在操作之前读取当前的状态，再根据当前的状态进行修改*/
  Function_temp=(uint8_t)(FLASH_ReadOptionByte(AFR_ADDRESS)>>8);
  #ifdef  DEBUG_AFR
  printf("\r\nFunction_temp:%x\r\n",Function_temp);
  #endif

  while(!(FLASH->IAPSR & FLASH_IAPSR_DUL));/*等待解锁完毕*/
  FLASH_ProgramOptionByte(AFR_ADDRESS,Function|Function_temp);
  
  #ifdef  DEBUG_AFR
  Function_temp=(uint8_t)(FLASH_ReadOptionByte(AFR_ADDRESS)>>8);
  printf("\r\nFunction_temp:%x\r\n",Function_temp);
  #endif
  FLASH_Lock(FLASH_MEMTYPE_DATA);/*操作完要加锁*/
   
}


/*******************************************************************************
* 名称: DefaultFunctionRemapping
* 功能: 恢复默认功能的设置
* 形参: Function 需要恢复默认的功能      
* 返回: 无
* 说明: 如果调试需要打印数据的时候
         在自定义宏的地方添加#define DEBUG_AFR即可，下载程序后只有第一次执行
         打印出来设置前的功能才是对的，执行完之前就被写进flash,如果不修改的话，
         每次都出来的数据都是一样，所以只执行一次就行了，建议用的时候，就在调
         试的时候进行执行一次就可以，以后都不需要出现了，除非再次更改。
         在调用DefaultFunctionRemapping函数之前需要初始化串口函数Uart_Init  
         这些设置写进flash,运行一次即可,在调试的时候运行即可
******************************************************************************/
void DefaultFunctionRemapping(Default_Function_TypeDef Function)
{
  uint8_t Function_temp;
  
  FLASH_Unlock(FLASH_MEMTYPE_DATA);/*要对选项字节写操作，必须要先解锁FLASH*/
  while(!(FLASH->IAPSR & FLASH_IAPSR_DUL));/*等待解锁完毕*/
  /*备选功能重映射的设置可以同时写多个不会被覆盖，因此在操作之前读取当前的状态，再根据当前的状态进行修改*/
  Function_temp=(uint8_t)(FLASH_ReadOptionByte(AFR_ADDRESS)>>8);
  #ifdef  DEBUG_AFR
  printf("\r\nFunction_temp:%x\r\n",Function_temp);
  #endif

  FLASH_ProgramOptionByte(AFR_ADDRESS,Function & Function_temp);
  
  #ifdef  DEBUG_AFR
  Function_temp=(uint8_t)(FLASH_ReadOptionByte(AFR_ADDRESS)>>8);
  printf("\r\nFunction_temp:%x\r\n",Function_temp);
  #endif
  FLASH_Lock(FLASH_MEMTYPE_DATA);/*操作完要加锁*/
}


