/******************** (C) COPYRIGHT  ���iCreateǶ��ʽ���������� **************
 * �ļ���  ��soft_i2c.c
 * ����    ��ģ��I2C������   
 * ʵ��ƽ̨�����STM8������
 * ��汾  ��V2.1.0
 * ����    �����  QQ��779814207
 * ����    ��
 * �Ա�    ��http://shop71177993.taobao.com/
 *�޸�ʱ�� ��2012-12-9

*******************************************************************************/

#include "stm8s.h"
#include "soft_i2c.h"

void delay_us(uint16_t nCount)
{
  u32 del = nCount*8;
  //48M 0.32uS
  //24M 0.68uS
  //16M 1.02us
  while(del--);
}

/*******************************************************************************
* ����: IIC_Init()
* ����: 
* �β�:       
* ����: ��
* ˵��: 
*******************************************************************************/
void IIC_Init(void)
{					     
  Set_I2C_SCL_Out;
  Set_I2C_SDA_Out;
  IIC_SCL_H;
  IIC_SDA_H;
#if (SYSINFOR_PRINTF == 1)
  printf("IIC_Init\r\n");
#endif
}
/*******************************************************************************
* ����: IIC_delay()
* ����: 
* �β�:       
* ����: 
* ˵��: 
*******************************************************************************/
void IIC_delay(void) 
{ 
  u8 i=7; //��������Ż��ٶ� ����������͵�5����д�� 
  while(i)  
  {  
    i--;  
  }  
} 
/*******************************************************************************
* ����: IIC_Start()
* ����: ����IIC��ʼ�ź�
* �β�:       
* ����: 
* ˵��: 
*******************************************************************************/
void IIC_Start(void)
{
  IIC_SDA_H; 
  IIC_SCL_H; 
  IIC_delay(); 
  if(!IIC_SDA_READ)return; //SDA��Ϊ�͵�ƽ������æ,�˳� 
  IIC_SDA_L; 
  IIC_delay(); 
  if(IIC_SDA_READ) return; //SDA��Ϊ�ߵ�ƽ�����߳���,�˳� 
  IIC_SCL_L; 
  IIC_delay(); 
}	  
/*******************************************************************************
* ����: IIC_Stop()
* ����: ����IICֹͣ�ź�
* �β�:       
* ����: 
* ˵��: 
*******************************************************************************/
void IIC_Stop(void)
{
  IIC_SCL_L; 
  IIC_delay(); 
  IIC_SDA_L; 
  IIC_delay(); 
  IIC_SCL_H; 
  IIC_delay(); 
  IIC_SDA_H; 
  IIC_delay(); 
  IIC_SCL_L;
  IIC_delay(); 
}      
/*******************************************************************************
* ����: IIC_Wait_Ack()
* ����: Ӧ���ź�
* �β�:       
* ����: 
* ˵��: true����Ӧ��ɹ� false����Ӧ��ʧ��
*******************************************************************************/
bool IIC_Wait_Ack(void)
{
  IIC_SCL_L; 
  IIC_delay(); 
  IIC_SDA_H; 
  IIC_delay(); 
  IIC_SCL_H; 
  IIC_delay(); 
  if(IIC_SDA_READ)//��Ӧ��
  { 
    IIC_SCL_L; 
    return FALSE; 
  } 
  IIC_SCL_L; 
  return TRUE; 
} 
/*******************************************************************************
* ����: IIC_Ack()
* ����: ACKӦ��
* �β�:       
* ����: 
* ˵��: 
*******************************************************************************/
void IIC_Ack(void)
{
  IIC_SCL_L; 
  IIC_delay(); 
  IIC_SDA_L; 
  IIC_delay(); 
  IIC_SCL_H; 
  IIC_delay(); 
  IIC_SCL_L; 
  IIC_delay(); 
}
/*******************************************************************************
* ����: IIC_NAck()
* ����: ������ACKӦ��
* �β�:       
* ����: 
* ˵��: 
*******************************************************************************/		    
void IIC_NAck(void)
{
  IIC_SCL_L; 
  IIC_delay(); 
  IIC_SDA_H; 
  IIC_delay(); 
  IIC_SCL_H; 
  IIC_delay(); 
  IIC_SCL_L; 
  IIC_delay(); 
}
/*******************************************************************************
* ����: IIC_Send_Byte()
* ����: IIC����һ���ֽ�
* �β�:       
* ����: 
* ˵��: true ok��false nok
*******************************************************************************/			  
bool IIC_Send_Byte(u8 sdata)
{                        
  u8 i=8; 
  
  while(i--) 
  { 
    IIC_SCL_L; 
    IIC_delay(); 
    if(sdata&0x80)IIC_SDA_H;   
    else        IIC_SDA_L;    
    sdata<<=1; 
    IIC_delay(); 
    IIC_SCL_H; 
    IIC_delay(); 
  } 
  IIC_SCL_L; 
  
  return (IIC_Wait_Ack());
} 	    
/*******************************************************************************
* ����: IIC_NAck()
* ����: ��1���ֽ�
* �β�: ����ACK      
* ����: 
* ˵��: nend = TRUE ����
*******************************************************************************/
u8 IIC_Read_Byte(bool nend)
{
  u8 i=8; 
  u8 ReceiveByte=0; 
  
  IIC_SDA_H; 
  while(i--) 
  { 
    ReceiveByte<<=1;       
    IIC_SCL_L; 
    IIC_delay(); 
    IIC_SCL_H; 
    IIC_delay(); 
    if(IIC_SDA_READ) 
    { 
      ReceiveByte|=0x01; 
    } 
  } 
  IIC_SCL_L;					 
  if(nend)
    IIC_Ack();  //����ACK
  else
    IIC_NAck(); //����NACK   
  return ReceiveByte;
}
/*******************************************************************************
* ����: AT24CXX_ReadOneByte()
* ����: ��AT24CXXָ����ַ��������
* �β�: ReadAddr:��ʼ�����ĵ�ַ      
* ����: 
* ˵��: ���������� 
*******************************************************************************/
bool ReadOneByte(u8 raddr,u8* rdata)
{				  		  	    																 
  IIC_Start();  
  if(EE_TYPE>AT24C16)
  {
    if(IIC_Send_Byte(0xA0) == FALSE){//����д����
      IIC_Stop();
      return FALSE;
    }
    if(IIC_Send_Byte(raddr>>8) == FALSE){//����д����
      IIC_Stop();
      return FALSE;
    }		 
  }else{
    if(IIC_Send_Byte(0XA0+((raddr>>8)<<1)) == FALSE){//����д����
      IIC_Stop();
      return FALSE;
    }
  }
  if(IIC_Send_Byte(raddr) == FALSE){   //���͵͵�ַ
    IIC_Stop();
    return FALSE;
  }	    
  IIC_Start();  
  if(IIC_Send_Byte(0xA1) == FALSE){   //�������ģʽ
    IIC_Stop();
    return FALSE;
  } 
  *rdata = IIC_Read_Byte(FALSE);		   
  IIC_Stop();	    
  return TRUE;
}
/*******************************************************************************
* ����: AT24CXX_WriteOneByte()
* ����: ��AT24CXXָ����ַд��һ������
* �β�: DataToWrite:Ҫд�������   WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
* ����: 
* ˵��: 
*******************************************************************************/
bool WriteOneByte(u8 waddr,u8 wdata)
{				   	  	    																 
  IIC_Start();  
  if(EE_TYPE>AT24C16)
  {
    if(IIC_Send_Byte(0xA0) == FALSE){    //ѡ��I2C
      IIC_Stop();
      return FALSE;
    }
    if(IIC_Send_Byte(waddr>>8) == FALSE){//�߰�λ��ַ
      IIC_Stop();
      return FALSE;
    }
  }else
  {
    if(IIC_Send_Byte(0XA0+((waddr>>8)<<1)) == FALSE){//����д����
      IIC_Stop();
      return FALSE;
    }
  }	 	   
  if(IIC_Send_Byte(waddr) == FALSE){   //���͵͵�ַ
    IIC_Stop();
    return FALSE;
  } 										  		   
  if(IIC_Send_Byte(wdata) == FALSE){   //����DATA
    IIC_Stop();
    return FALSE;
  } 		    	   
  IIC_Stop();//����һ��ֹͣ���� 
  return TRUE;
}
/*******************************************************************************
* ����: AT24CXX_WriteLenByte()
* ����: дlen����
* �β�: waddr wdata len
* ����: 
* ˵��: Ϊ����6206��һ�£�����ʱFAULT����ȷд��
*******************************************************************************/
bool i2c_write(u8 waddr,u8 *wdata,u8 len)
{  	
  IIC_Start();  
  if(EE_TYPE>AT24C16)
  {
    if(IIC_Send_Byte(0xA0) == FALSE){    //ѡ��I2C
      IIC_Stop();
      return TRUE;
    }
    if(IIC_Send_Byte(waddr>>8) == FALSE){//�߰�λ��ַ
      IIC_Stop();
      return TRUE;
    }
  }else
  {
    if(IIC_Send_Byte(0XA0+((waddr>>8)<<1)) == FALSE){//����д����
      IIC_Stop();
      return TRUE;
    }
  }	 	   
  if(IIC_Send_Byte(waddr) == FALSE){   //���͵͵�ַ
    IIC_Stop();
    return TRUE;
  }
  for(;len>0;len--){
    if(IIC_Send_Byte(*wdata++) == FALSE){     //�����ֽ�
      IIC_Stop();
      return TRUE;
    }
  }		    	   
  IIC_Stop();//����һ��ֹͣ���� 
  return FALSE;												    
}
/*******************************************************************************
* ����: AT24CXX_ReadLenByte()
* ����: ��len�ֽ�����
* �β�: raddr  rdata len
* ����: 
* ˵��: 
*******************************************************************************/
bool i2c_read(u8 raddr,u8 *rdata,u8 len)
{  	
  IIC_Start();  
  if(EE_TYPE>AT24C16)
  {
    if(IIC_Send_Byte(0xA0) == FALSE){//����д����
      IIC_Stop();
      return TRUE;
    }
    if(IIC_Send_Byte(raddr>>8) == FALSE){//����д����
      IIC_Stop();
      return TRUE;
    }		 
  }else{
    if(IIC_Send_Byte(0XA0+((raddr>>8)<<1)) == FALSE){//����д����
      IIC_Stop();
      return TRUE;
    }
  }
  if(IIC_Send_Byte(raddr) == FALSE){   //���͵͵�ַ
    IIC_Stop();
    return TRUE;
  }	    
  IIC_Start();  
  if(IIC_Send_Byte(0xA1) == FALSE){   //�������ģʽ
    IIC_Stop();
    return TRUE;
  } 
  while(len != 0){
    len--;
    if(len == 0)*rdata = IIC_Read_Byte(FALSE); //FALSE ��ȡ���
    else        *rdata++ = IIC_Read_Byte(TRUE);//TRUE  δ����
    
  }
  IIC_Stop();	
  
  return FALSE;
}

