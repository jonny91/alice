#include <STC/STC12C5A60S2.H>
#include <common.h>
#include "uart.h"
#include "mp3.h"

sbit STEP_0_SIGNAL = P0^5;	//��һ�ؿ��� ����
sbit STEP_1_SIGNAL = P0^0;	  //��һ�����
sbit STEP_2_SIGNAL = P0^4;	   //�ڶ������ �������صĽ���
sbit STEP_5_LINE_SIGNAL = P4^0; //16�������߽���
sbit STEP_5_TO_6_DOOR =  P4^2; //�������ɵĵ���� 
//��ǰ�Ĳ��� û�в���� = 0
signed char step = 0;

void playStep3();

void main()
{
	sys_init();
	mp3_init();
	
	while(1)
	{
		if(step == 0)
		{
			if(STEP_0_SIGNAL == 1) //�Ź��� 
			{
				step = 2; 
				delay_ms(5000);
				
				playMp3(0x00,0x01);	   //���ŵ�һ���ļ��еĵ�һ������
			} 
		}
		//��һ�������ſ��ؿ��� ֱ�Ӿ�������� 
		if(step == 2)  //����4
		{
			if(STEP_2_SIGNAL == 1) //�������� 
			{
				step = 5; //��ȥ��5������ 
				
				delay_ms(5000);
				playMp3(0x00,0x02);
			}
		}
		
		if(step == 5) //����5 �ӵ��� 
		{
			if(STEP_5_LINE_SIGNAL == 1)
			{
				delay_ms(500);
				if(STEP_5_LINE_SIGNAL == 1) //���߳ɹ� ��5����� 
				{
					step = 6;
					playMp3(0x00,0x02);
				 	STEP_5_TO_6_DOOR = 0; //��������� 
				}
			} 
		} 
	}
}

//��ʼ�����п�
void INIT_COM()
{
	
}