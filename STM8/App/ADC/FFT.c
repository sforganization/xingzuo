#include<math.h>
#include "stm8s.h"
#include "fft.h"



#define PI      3.14159265358979                 //����Բ����ֵ
#define PI2     6.28318530717959
#define FFT_N   16                                 //���帣��Ҷ�任�ĵ���


/*-ȫ�ֱ���----------------------------------------------------*/
static u16  ADValueTab[FFT_N] = {0};

struct compx {double real,imag;};                                    //����һ�������ṹ
struct compx s[FFT_N];                                             //FFT������������S[1]��ʼ��ţ����ݴ�С�Լ�����
struct compx EE(struct compx a,struct compx b);
u16     Save;

/*--------------------------------------------------------------*/
const u8 SelectTable[FFT_N] ={
  0,0,0,0,      //R
  1,1,          //
  2,2,2,        //G
  3,3,          //
  4,4,4,        //B
  5,5                              
};
const typedef_RGB_ClassColor RGB_Table[LIGHT_RGB_COLORGEAR]=            //RGB   
{
  {LAMP_RGB_MAXCOLOR,      LAMP_RGB_MINCOLOR,      LAMP_RGB_MINCOLOR,	RED   },
  {LAMP_RGB_MAXCOLOR,      LAMP_RGB_MAXCOLOR,      LAMP_RGB_MINCOLOR,	YELLOW},
  {LAMP_RGB_MINCOLOR,      LAMP_RGB_MAXCOLOR,      LAMP_RGB_MINCOLOR,	GREEN },
  {LAMP_RGB_MINCOLOR,      LAMP_RGB_MAXCOLOR,      LAMP_RGB_MAXCOLOR,	CYAN  }, //����ɫ ��
  {LAMP_RGB_MINCOLOR,      LAMP_RGB_MINCOLOR,      LAMP_RGB_MAXCOLOR,	BLUE  },
  {LAMP_RGB_MAXCOLOR,      LAMP_RGB_MINCOLOR,      LAMP_RGB_MAXCOLOR,	PURPLE},
};

/*******************************************************************
����ԭ�ͣ�structcompx EE(struct compx b1,struct compx b2)
�������ܣ��������������г˷�����
��������������������嶨��ĸ���a,b
���������a��b�ĳ˻��������������ʽ���
*******************************************************************/
struct compx EE(struct compx a,struct compx b)      
{
  struct compx c;
  c.real=a.real*b.real-a.imag*b.imag;
  c.imag=a.real*b.imag+a.imag*b.real;
  return(c);
}

/*****************************************************************
����ԭ�ͣ�voidFFT(struct compx *xin,int N)
�������ܣ�������ĸ�������п��ٸ���Ҷ�任��FFT��
���������*xin�����ṹ������׵�ַָ�룬struct��
*****************************************************************/
void FFT(struct compx *xin)
{
  int f,m,nv2,nm1,i,k,l,j=0;
  struct compx u,w,t;
  
  nv2=FFT_N/2;                  //��ַ���㣬������Ȼ˳���ɵ�λ�򣬲����׵��㷨
  nm1=FFT_N-1;  
  for(i=0;i<nm1;i++)        
  {
    if(i<j)                    //���i<j,�����б�ַ
    {
      t      =  xin[j];           
      xin[j] =  xin[j];
      xin[j] =  t;
    }
    k=nv2;                    //��j����һ����λ��
    while(k<(j + 1))               //���k<j,��ʾj�����λΪ1   
    {           
      j  = j-k;                 //�����λ���0
      k  = k/2;                 //k/2���Ƚϴθ�λ���������ƣ�����Ƚϣ�ֱ��ĳ��λΪ0
    }
    j = j+k;                   //��0��Ϊ1
    
  }
  {
    int le,lei,ip;                           //FFT����ˣ�ʹ�õ����������FFT����
    f = FFT_N;
    for(l=1;(f=f/2)!=1;l++)                 //����l��ֵ����������μ���
      ;
    for(m=1;m<=l;m++)                         // ���Ƶ��νἶ��
    {                                        //m��ʾ��m�����Σ�lΪ���μ�����l=log��2��N
      le     =  2<<(m-1);                            //le���ν���룬����m�����εĵ��ν����le��
      lei    = le/2;                              //ͬһ���ν��вμ����������ľ���
      u.real = 1.0;                            //uΪ���ν�����ϵ������ʼֵΪ1
      u.imag = 0.0;
      w.real = cos(PI/lei);                    //wΪϵ���̣�����ǰϵ����ǰһ��ϵ������
      w.imag =-sin(PI/lei);
      for(j=0;j<=lei-1;j++)                   //���Ƽ��㲻ͬ�ֵ��νᣬ������ϵ����ͬ�ĵ��ν�
      {
        for(i=j;i<=FFT_N-1;i=i+le)            //����ͬһ���ν����㣬������ϵ����ͬ���ν�
        {
          ip=i+lei; //i��ip�ֱ��ʾ�μӵ�������������ڵ�
          t=EE(xin[ip],u); //�������㣬�����ʽ
          xin[ip].real = xin[i].real-t.real;
          xin[ip].imag = xin[i].imag-t.imag;
          xin[i].real  = xin[i].real+t.real;
          xin[i].imag  = xin[i].imag+t.imag;
        }
        u = EE(u,w);                          //�ı�ϵ����������һ����������
      }
    }
  }
  
}
/************************************************************
����ԭ�ͣ�
�������ܣ�����FFT�任
�����������
�����������
************************************************************/
void MusicFFT(void)  
{  
  u8 i,r,g,b;  
  u16 count,br,tmp;
   
  for(i=0;i<FFT_N-1;i++) //����ǰ��һ��Ԫ��
  {
      ADValueTab[i] = ADValueTab[i + 1]; 
  }
  ADValueTab[15] = GetADValue();
  
  for(i=0;i<FFT_N;i++)
  {                     
      count  += ADValueTab[i];
  } 
  
  tmp = abs(count - Save);
  

  if(tmp > 400)
  {
        i = (u8)rand()%5;
        r = RGB_Table[i].R;
        g = RGB_Table[i].G;
        b = RGB_Table[i].B;
      if     (tmp > 900)   {br = 800;   SysInfor.MusicTick = 250; SysInfor.uPdateTick = 1;}
       else if(tmp > 800)  {br = 600;   SysInfor.MusicTick = 140; SysInfor.uPdateTick = 1;}
        else if(tmp > 700)  {br = 450;  SysInfor.MusicTick = 100; SysInfor.uPdateTick = 1;}
         else if(tmp > 450)  {br = 300;  SysInfor.MusicTick = 100; SysInfor.uPdateTick = 1;}
         else                 {br =100; SysInfor.MusicTick = 30; SysInfor.uPdateTick = 4;}
      LED_Update_Light(0,0,r,g,b,br);  //���ֲ���
      LED_Update_LightBuf(0,0,r,g,b,80);  //���ֲ���
  }
  else
  {
     SysInfor.MusicTick = 1;
  }
  Save = count;
}