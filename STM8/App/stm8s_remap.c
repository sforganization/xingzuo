#include "stm8s_remap.h"




/*******************************************************************************
* ����: AlternateFunctionRemapping
* ����: ѡ������ӳ�������
* �β�: Function ��Ҫ��ӳ��Ĺ���      
* ����: ��
* ˵��: ���������Ҫ��ӡ���ݵ�ʱ��
         ���Զ����ĵط����#define DEBUG_AFR���ɣ����س����ֻ�е�һ��ִ��
         ��ӡ��������ǰ�Ĺ��ܲ��ǶԵģ�ִ����֮ǰ�ͱ�д��flash,������޸ĵĻ���
         ÿ�ζ����������ݶ���һ��������ִֻ��һ�ξ����ˣ������õ�ʱ�򣬾��ڵ�
         �Ե�ʱ�����ִ��һ�ξͿ��ԣ��Ժ󶼲���Ҫ�����ˣ������ٴθ��ġ�
         �ڵ���AlternateFunctionRemapping����֮ǰ��Ҫ��ʼ�����ں���Uart_Init
         ��Щ����д��flash,����һ�μ���,�ڵ��Ե�ʱ�����м���
******************************************************************************/

void AlternateFunctionRemapping(Remap_Function_TypeDef Function)
{
  uint8_t Function_temp;
  
  FLASH_Unlock(FLASH_MEMTYPE_DATA);/*Ҫ��ѡ���ֽ�д����������Ҫ�Ƚ���FLASH*/
  while(!(FLASH->IAPSR & FLASH_IAPSR_DUL));/*�ȴ��������*/
  /*��ѡ������ӳ������ÿ���ͬʱд������ᱻ���ǣ�����ڲ���֮ǰ��ȡ��ǰ��״̬���ٸ��ݵ�ǰ��״̬�����޸�*/
  Function_temp=(uint8_t)(FLASH_ReadOptionByte(AFR_ADDRESS)>>8);
  #ifdef  DEBUG_AFR
  printf("\r\nFunction_temp:%x\r\n",Function_temp);
  #endif

  while(!(FLASH->IAPSR & FLASH_IAPSR_DUL));/*�ȴ��������*/
  FLASH_ProgramOptionByte(AFR_ADDRESS,Function|Function_temp);
  
  #ifdef  DEBUG_AFR
  Function_temp=(uint8_t)(FLASH_ReadOptionByte(AFR_ADDRESS)>>8);
  printf("\r\nFunction_temp:%x\r\n",Function_temp);
  #endif
  FLASH_Lock(FLASH_MEMTYPE_DATA);/*������Ҫ����*/
   
}


/*******************************************************************************
* ����: DefaultFunctionRemapping
* ����: �ָ�Ĭ�Ϲ��ܵ�����
* �β�: Function ��Ҫ�ָ�Ĭ�ϵĹ���      
* ����: ��
* ˵��: ���������Ҫ��ӡ���ݵ�ʱ��
         ���Զ����ĵط����#define DEBUG_AFR���ɣ����س����ֻ�е�һ��ִ��
         ��ӡ��������ǰ�Ĺ��ܲ��ǶԵģ�ִ����֮ǰ�ͱ�д��flash,������޸ĵĻ���
         ÿ�ζ����������ݶ���һ��������ִֻ��һ�ξ����ˣ������õ�ʱ�򣬾��ڵ�
         �Ե�ʱ�����ִ��һ�ξͿ��ԣ��Ժ󶼲���Ҫ�����ˣ������ٴθ��ġ�
         �ڵ���DefaultFunctionRemapping����֮ǰ��Ҫ��ʼ�����ں���Uart_Init  
         ��Щ����д��flash,����һ�μ���,�ڵ��Ե�ʱ�����м���
******************************************************************************/
void DefaultFunctionRemapping(Default_Function_TypeDef Function)
{
  uint8_t Function_temp;
  
  FLASH_Unlock(FLASH_MEMTYPE_DATA);/*Ҫ��ѡ���ֽ�д����������Ҫ�Ƚ���FLASH*/
  while(!(FLASH->IAPSR & FLASH_IAPSR_DUL));/*�ȴ��������*/
  /*��ѡ������ӳ������ÿ���ͬʱд������ᱻ���ǣ�����ڲ���֮ǰ��ȡ��ǰ��״̬���ٸ��ݵ�ǰ��״̬�����޸�*/
  Function_temp=(uint8_t)(FLASH_ReadOptionByte(AFR_ADDRESS)>>8);
  #ifdef  DEBUG_AFR
  printf("\r\nFunction_temp:%x\r\n",Function_temp);
  #endif

  FLASH_ProgramOptionByte(AFR_ADDRESS,Function & Function_temp);
  
  #ifdef  DEBUG_AFR
  Function_temp=(uint8_t)(FLASH_ReadOptionByte(AFR_ADDRESS)>>8);
  printf("\r\nFunction_temp:%x\r\n",Function_temp);
  #endif
  FLASH_Lock(FLASH_MEMTYPE_DATA);/*������Ҫ����*/
}


