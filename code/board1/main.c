#include <STC/STC12C5A60S2.H>
#include <common.h>
#include "uart.h"
#include "mp3.h"

sbit STEP_0_SIGNAL = P0^5;	//��һ�ؿ��� ����
sbit STEP_1_SIGNAL = P0^0;	  //��һ�����
sbit STEP_2_SIGNAL = P0^4;	   //�ڶ������ �������صĽ���
sbit STEP_5_SIGANL; // 
sbit STEP_6_LINE_SIGNAL = P4^0; //16�������߽���
sbit STEP_6_TO_7_DOOR =  P4^2; //��������ɵĵ����
sbit STEP_7_DOOR;
sbit STEP_7_SIGNAL; 
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
				
				play_mp3(0x00,0x01);	   //���ŵ�һ���ļ��еĵ�һ������
			} 
		}
		//��һ�������ſ��ؿ��� ֱ�Ӿ�������� 
		if(step == 2)  //����4
		{
			if(STEP_2_SIGNAL == 1) //�������� 
			{
				step = 5; //��ȥ��5������ 
				
				delay_ms(5000);
				play_mp3(0x00,0x02);
			}
		}

		if(step == 5)
		{
			if(STEP_6_LINE_SIGNAL == 1)
			{	
				delay_ms(500);
				if(STEP_5_SIGANL == 1)
				{
					step = 6;
				} 
			} 
		}
		
		if(step == 6) //����5 �ӵ��� 
		{
			if(STEP_6_LINE_SIGNAL == 1)
			{
				delay_ms(500);
				if(STEP_6_LINE_SIGNAL == 1) //���߳ɹ� ��6����� 
				{
					step = 7;
					play_mp3(0x00,0x02);
				 	STEP_6_TO_7_DOOR = 0; //��������� 
				}
			} 
		}
		
		if(step == 7)//������
		{
			if(STEP_7_SIGNAL == 1)
			{
				delay_ms(500);
				if(STEP_7_SIGNAL == 1)
				{
					step = 8;
					play_mp3(0x00,0x02);
					
					STEP_7_DOOR = 0; //��7���� 
				}
			}
		} 
	}
}

//��ʼ�����п�
void INIT_COM()
{
	
}