#include <STC/STC12C5A60S2.H>

#define FOSC 11059200L
#define MODE1T                      //Timer clock mode, comment this line is 12T mode, uncomment is 1T mode

#ifdef MODE1T
#define T1MS (65536-FOSC/1000)      //1ms timer calculation method in 1T mode
#else
#define T1MS (65536-FOSC/12/1000)   //1ms timer calculation method in 12T mode
#endif

/*********************************************************/
/*                                                       */
/* ϵͳ��ʼ������  P1-P4���ó��������                   */
/*                                                       */
/*********************************************************/	
void sys_init()
{
	P0M1=0X00;
	P0M0=0Xff;      //����P0Ϊ�������
	
	P1M1=0X00;
	P1M0=0XFF;	    //����P1Ϊ�������
	
	P2M1=0X00;
	P2M0=0XFF;		//����P2��Ϊ�������
	
	P3M1=0X00;
	P3M0=0XFF;	    //����P3Ϊ�������	P3.0 3.1 RXD TXD����Ϊ��ͨIO�� ��ֹ���������

	P4M1=0X00;
	P4M0=0XFF;      //����P4Ϊ�������


}

/*********************************************************/
/*                                                       */
/* 1ms��ʱ����                                           */
/*                                                       */
/*********************************************************/
void delay_ms(int count)  // /* X1ms */	 ��ʱ1ms����
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<1000;j++);
} 
