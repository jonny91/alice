#include <STC/STC12C5A60S2.H>
#include <string.h>
#include <common.h>
#include "uart.h"
#include "mp3.h"

//��ˮ�� �����
sbit OUTPUT_07 = P0^7;
//��ͨˮ�� ��ťͨ��
sbit OUTPUT_42 = P4^2;
//�������Ƹ�
sbit OUTPUT_10 = P1^0; //��ʼ�� �ߵ�ƽ
sbit OUTPUT_11 = P1^1;

//ˮ����ӵ��ڲ�
sbit INPUT_06 = P0^6;
//6���Ž�
sbit INPUT_05 = P0^5;
sbit INPUT_04 = P0^4;
sbit INPUT_03 = P0^3;
sbit INPUT_02 = P0^2;
sbit INPUT_01 = P0^1;
sbit INPUT_00 = P0^0;

//�������ش�������
sbit INPUT_P23 = P2^3; 

//6����ť
sbit INPUT_44 = P4^4;
sbit INPUT_45 = P4^5;
sbit INPUT_41 = P4^1;

sbit INPUT_24 = P2^4;
sbit INPUT_25 = P2^5;
sbit INPUT_26 = P2^6;

//��ǰ�Ĳ��� û�в���� = 0
unsigned char step = 0;

unsigned char step_1_flag_1 = 0;
unsigned char step_1_flag_2 = 0;
unsigned char step_1_flag_3 = 0;
unsigned char step_1_flag_4 = 0;
unsigned char step_1_flag_5 = 0;
unsigned char step_1_flag_6 = 0;

int btnStep = 0;//��Ұ����ڼ��� 
int totalLength = 6;//��ť �ܲ���
unsigned char code buttonStep[6] = {4,5,5,6,6,6};
unsigned char button_step_player[6] = {0,0,0,0,0,0};

int PLAY_6_BTN();
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
			if(INPUT_06 == 0)	//ˮ�ܽ�ͨ
			{
				OUTPUT_07 = 0;
				play_mp3(0,1);
				step = 1;			
			}	
		}
		if(step == 1)	 
		{
			if( (INPUT_05 == 0) && (step_1_flag_1 == 0))
			{
				delay_ms(50);
				if( (INPUT_05 == 0) && (step_1_flag_1 == 0))
				{
				step_1_flag_1 = 1;
				}
			}
			if( (INPUT_04 == 0) && (step_1_flag_2 == 0))
			{
			 	delay_ms(50);
				 if( (INPUT_04 == 0) && (step_1_flag_2 == 0))
				{
					step_1_flag_2 = 1;
				}
			}
			if( (INPUT_03 == 0)	&& (step_1_flag_3 == 0))
			{
			 	delay_ms(50);	
				if( (INPUT_03 == 0)	&& (step_1_flag_3 == 0))	
				{	
					step_1_flag_3 = 1;
				}
			}
			if( (INPUT_02 == 0) && (step_1_flag_4 == 0))
			{
			 	delay_ms(50);
				if( (INPUT_02 == 0) && (step_1_flag_4 == 0))	
				{
					step_1_flag_4 = 1;
				}
			}
			if( (INPUT_01 == 0) && (step_1_flag_5 == 0))
			{
			 	delay_ms(50);
				if( (INPUT_01 == 0) && (step_1_flag_5 == 0))
				{
					step_1_flag_5 = 1;
				}
			}
			if( (INPUT_00 == 0)	&& (step_1_flag_6 == 0))
			{
				delay_ms(50);
				if( (INPUT_00 == 0)	&& (step_1_flag_6 == 0))
				{	
					step_1_flag_6 = 1;
				}
			}
			if((step == 1) && (step_1_flag_1 == 1 )&& (step_1_flag_2 == 1) && (step_1_flag_3 == 1) && (step_1_flag_4 == 1 )&& (step_1_flag_5 == 1) && (step_1_flag_6 == 1))
			{			
				step = 2;  //6���Ž��Ŷ���
				OUTPUT_42 = 1;
				play_mp3(0,1);
			}
		}
		if(step == 2)  //��6����ť
		{
			if(PLAY_6_BTN() == 1)	 //������
			{
				step = 3;
			
				OUTPUT_42 = 0; //�رհ�ť��

				OUTPUT_10 = 1;	 //���Ƹ�
				play_mp3(0,9);
			}
		}

		if(step == 3)
		{
			if(INPUT_P23 == 1)
			{
				delay_ms(50);
				if(INPUT_P23 == 1)
				{
					step = 4;
					OUTPUT_11 = 1; //���Ƹ�
					play_mp3(0,10);
				}
			} 
		}
	}
}

int PLAY_6_BTN()
{
  	int i ;
//	GET_ARRAY_LEN(buttonStep , totalLength);	
	if(INPUT_44 == 0)
	{
		delay_ms(50);
		if(INPUT_44 == 0)
		{
			while(INPUT_44 == 0); //�ɿ�
			button_step_player[btnStep] =  1;
			btnStep ++;
			play_mp3(0,2);
		}
	}
	
	if(INPUT_45 == 0)
	{
		delay_ms(50);
		if(INPUT_45 == 0)
		{
			while(INPUT_45 == 0); //�ɿ� 
			button_step_player[btnStep] =  2;
	   		btnStep ++;
   			play_mp3(0,3);
		}
	}
	
	if(INPUT_41 == 0)
	{
		delay_ms(50);
		if(INPUT_41 == 0)
		{
			while(INPUT_41 == 0); //�ɿ� 
			button_step_player[btnStep] =  3;
		   	btnStep ++;
			play_mp3(0,4);
		}
	}

	if(INPUT_24 == 0)
	{
		delay_ms(50);
		if(INPUT_24 == 0)
		{
			while(INPUT_24 == 0); //�ɿ�
			button_step_player[btnStep] =  4;			
		   	btnStep ++;
			play_mp3(0,5);
		}
	}

	if(INPUT_25 == 0)
	{
		delay_ms(50);
		if(INPUT_25 == 0)
		{
			while(INPUT_25 == 0); //�ɿ� 			
			button_step_player[btnStep] =  5;			
			btnStep ++;
			play_mp3(0,6);
		}
	}

	if(INPUT_26 == 0)
	{
		delay_ms(50);
		if(INPUT_26 == 0)
		{
			while(INPUT_26 == 0); //�ɿ� 
			button_step_player[btnStep] =  6;			
			btnStep ++;
			play_mp3(0,7);
		}
	}

	if(btnStep == totalLength) //�����㹻�Ĳ��� 
	{
		for(i = 0 ; i < totalLength ; i++)
		{
			if((button_step_player[i] != buttonStep[i]))
			{
				btnStep = 0; //�д��� ��Ҳ�����0 ������ 
				memset(button_step_player,0,6);
				OUTPUT_42 = 0;
				delay_ms(2000);
				OUTPUT_42 = 1;
				return 0;
			}
		}
		//������
	    OUTPUT_42 = 0;
		play_mp3(0,8);
		return 1;
	} 
	return 0;
}



//��ʼ�����п�
void INIT_COM()
{
	INPUT_06 = 1;

	//�Ƹ�
	OUTPUT_10 = 0;
	OUTPUT_11 = 0;

	//��ˮ�� ��������
	OUTPUT_07 = 1;
	//��ͨˮ�� ��ťͨ��
	OUTPUT_42 = 0;

	//6���Ž� Ĭ���Ž���
	INPUT_05 = 1;
	INPUT_04 = 1;
	INPUT_03 = 1;
	INPUT_02 = 1;
	INPUT_01 = 1;
	INPUT_00 = 1;

	//6����ť
	INPUT_44 = 1;
	INPUT_45 = 1;
	INPUT_41 = 1;
	INPUT_26 = 1;
	INPUT_24 = 1;
	INPUT_25 = 1;
	
	//�������� 
	INPUT_P23 = 1;
}