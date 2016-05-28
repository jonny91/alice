#include <STC12C5A60S2.H>
#include <string.h>
#include <common.h>
#include "uart.h"
#include "mp3.h"

//4����ť���� 
sbit INPUT_04 = P0^4;
sbit INPUT_03 = P0^3;
sbit INPUT_02 = P0^2;
sbit INPUT_01 = P0^1;

//������������
sbit INPUT_00 = P0^0; 

//Ϳõ�� �����
sbit OUTPUT_21 = P2^1;
//���һ�������
sbit OUTPUT_22 = P2^2;

//�ӵƴ�
//��һ����:
//RGB
sbit OUTPUT_43 = P4^3;
sbit OUTPUT_17 = P1^7;
sbit OUTPUT_16 = P1^6;
//�ڶ�����:
//RGB
sbit OUTPUT_15 = P1^5;
sbit OUTPUT_14 = P1^4;
sbit OUTPUT_13 = P1^3;
//��������:
//RGB
sbit OUTPUT_12 = P1^2;
sbit OUTPUT_11 = P1^1;
sbit OUTPUT_10 = P1^0;
//���ĸ���:
//RGB
sbit OUTPUT_42 = P4^2;
sbit OUTPUT_40 = P4^0;
sbit OUTPUT_20 = P2^0;  

char step = 0; 

//RGB RED:011b = 3	�͵�ƽ��
char color[] = {0,1,2,3,4,5,6,7}; //8����ɫ
//��ʼ������
char color_step_0 = 2;
char color_step_1 = 5;
char color_step_2 = 1;
char color_step_3 = 0;

void light(char lightNumber , char color);
void INIT_COM();
void main()
{
	sys_init();
	INIT_COM();

	uart_init();
	mp3_init();

	while(1)
	{
		if(step == 0)
		{
			if(INPUT_04 == 0)
			{
				delay_ms(50);
				if(INPUT_04 == 0)
				{
					color_step_0 = (++color_step_0)%8;
					color_step_1 = (++color_step_1)%8;
					light(0,color_step_0);
					light(1,color_step_1);
				}
			} 
			
			if(INPUT_03 == 0)
			{
				delay_ms(50);
				if(INPUT_03 == 0)
				{
					color_step_0 = (++color_step_0)%8;
					color_step_1 = (++color_step_1)%8;	
					color_step_2 = (++color_step_2)%8;
					light(0,color_step_0);
					light(1,color_step_1);
					light(2,color_step_2);
				}
			} 
			
			if(INPUT_02 == 0)
			{
				delay_ms(50);
				if(INPUT_02 == 0)
				{
					color_step_1 = (++color_step_1)%8; 
					color_step_2 = (++color_step_2)%8;	
					color_step_3 = (++color_step_3)%8;
					
					light(1,color_step_1);
					light(2,color_step_2);									
					light(3,color_step_3);
				}
			} 
			
			if(INPUT_01 == 0)
			{
				delay_ms(50);
				if(INPUT_01 == 0)
				{
					color_step_2 = (++color_step_2)%8;
					color_step_3 = (++color_step_3)%8;
					light(2,color_step_2);									
					light(3,color_step_3);
				}
			}
			
			if(color_step_0 == 4 && color_step_1 == 4 && color_step_2 == 4 && color_step_3 == 4)
			{
				step = 1;
				OUTPUT_21 = 0 ;//�򿪵���� 
			}
		}
		
		if(step == 1)
		{
			if(INPUT_00 == 0)
			{
				delay_ms(50);
				if(INPUT_00 == 0)
				{
					step = 2; 
					OUTPUT_22 = 0;//���һ���� 
				} 
			} 
		} 
	}
}

void light(char lightNumber , char color)
{
	switch(lightNumber)
	{
		case 0:
		{
			OUTPUT_43 = (color & 4)>>2; 
			OUTPUT_17 = (color & 2)>>1;
			OUTPUT_16 = color & 1;	
			break;
		}
		
		case 1:
		{
			OUTPUT_15 = (color & 4)>>2; 
			OUTPUT_14 = (color & 2)>>1;
			OUTPUT_13 = color & 1;		
			break;
		}
		
		case 2:
		{
			OUTPUT_12 = (color & 4)>>2; 
			OUTPUT_11 = (color & 2)>>1;
			OUTPUT_10 = color & 1;	
			break;
		}
		
		case 3:
		{
			OUTPUT_42 = (color & 4)>>2; 
			OUTPUT_40 = (color & 2)>>1;
			OUTPUT_20 = color & 1;	
			break;
		}
	}
}

void INIT_COM()
{
	INPUT_04 = 1;
	INPUT_03 = 1; 
	INPUT_02 = 1; 
	INPUT_01 = 1;
	INPUT_00 = 1;
	
	OUTPUT_21 = 1;
	OUTPUT_17 = 1;
	
	OUTPUT_43 = 1; 
	OUTPUT_17 = 1;
	OUTPUT_16 = 1;
	
	OUTPUT_15 = 1;
	OUTPUT_14 = 1;
	OUTPUT_13 = 1;
	
	OUTPUT_12 = 1;
	OUTPUT_11 = 1;
	OUTPUT_10 = 1;
	
	OUTPUT_42 = 1;
	OUTPUT_40 = 1;
	OUTPUT_20 = 1;
}