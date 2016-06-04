#include <STC/STC12C5A60S2.H>
#include <string.h>
#include <common.h>
#include "uart.h"
#include "mp3.h"

//��ͨˮ�� ��ťͨ��
sbit OUTPUT_42 = P4^2;

//�������Ƹ�
sbit OUTPUT_10 = P1^0; //��ʼ�� �ߵ�ƽ
sbit OUTPUT_11 = P1^1;
sbit OUTPUT_12 = P1^2;

//ˮ����ӵ��ڲ�
sbit INPUT_06 = P0^6;
sbit INPUT_15 = P1^5;

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
sbit INPUT_14 = P1^4;
sbit INPUT_13 = P1^3;
sbit INPUT_07 = P0^7;

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

unsigned char btnTime = 0;//�ڼ��ְ�ť
int btnStep = 0;//��Ұ����ڼ���
int totalLength;//��ť �ܲ���
unsigned char code buttonStep[4][6] = {{1,2,3,4,5,6},{1,2,3,4,5,6},{1,2,3,4,5,6},{1,2,3,4,5,6}};
unsigned char button_step_player[4][6] = {{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};

int PLAY_6_BTN();
void INIT_COM();


void main()
{
	sys_init();
	INIT_COM();
	uart_init();
	mp3_init();

	//�����ӳ� �ű�������
	delay_ms(10000);
	play_mp3(0,1);
	
	while(1)
	{
		if(step == 0)
		{
			if((INPUT_06 == 0) && (INPUT_15 == 0))	//ˮ�ܽ�ͨ
			{
				delay_ms(50);
				if((INPUT_06 == 0) && (INPUT_15 == 0))	//ˮ�ܽ�ͨ
				{
					OUTPUT_12 = 1;  //�������
			  		play_mp3(0,2);
					step = 1;		
				}
			}	
		}	
		else if(step == 1)	 
		{		
			delay_ms(50);			  
			if((INPUT_05 == 0) && (step_1_flag_1 == 0))
			{
				delay_ms(50);
				if(INPUT_05==0)
				{
					step_1_flag_1 = 1;
					play_mp3(0,3);
				}
			}
			if( (INPUT_04 == 0) && (step_1_flag_2 == 0))
			{
			 	delay_ms(50);
				 if(INPUT_04 == 0)
				{
					step_1_flag_2 = 1;
					play_mp3(0,4);
				}
			}
			if( (INPUT_03 == 0)	&& (step_1_flag_3 == 0))
			{
			 	delay_ms(50);	
				if(INPUT_03 == 0)	
				{	
					step_1_flag_3 = 1;
					play_mp3(0,5);
				}
			}
			if( (INPUT_02 == 0) && (step_1_flag_4 == 0))
			{
			 	delay_ms(50);
				if(INPUT_02 == 0)	
				{
					step_1_flag_4 = 1;
					play_mp3(0,6);
				}
			}
			if((INPUT_01 == 0)&&(step_1_flag_5 == 0))
			{
			 	delay_ms(50);
				if(INPUT_01 == 0)
				{
					step_1_flag_5 = 1;
					play_mp3(0,7);
				}
			}
			if( (INPUT_00 == 0)	&& (step_1_flag_6 == 0))
			{
				delay_ms(50);
				if(INPUT_00 == 0)
				{	
					step_1_flag_6 = 1;
					play_mp3(0,8);
				}
			}
			if((step_1_flag_1==1)&&(step_1_flag_2 == 1)&&(step_1_flag_3 == 1)&&(step_1_flag_4==1)&&(step_1_flag_5==1)&&(step_1_flag_6==1))
			{			
				step = 2;  //6���Ž��Ŷ���
				OUTPUT_42 = 1;			
				play_mp3(0,9);
			}
		}
		else if(step==2)  //��6����ť
		{
			delay_ms(50);
			if(PLAY_6_BTN() == 1)	 //������
			{
				btnTime = 1;
	
				play_mp3(0,10);
				step = 3;			
			}
		}

		else if(step == 3)
		{
			if(PLAY_6_BTN() == 1)
			{		
				play_mp3(0,11);	  //���ľ���ʾ
				step = 4;
			}	
		}

		else if(step == 4)
		{
			if(PLAY_6_BTN() == 1)
			{
				play_mp3(0,12);
				step = 5;
			}
		}
		else if(step == 5)
		{
			if(PLAY_6_BTN() == 1)
			{
				OUTPUT_42 = 0; //�رհ�ť��

				OUTPUT_10 = 1;	 //���Ƹ�
				play_mp3(0,17);

				step = 6;
			}
		}

		else if(step == 6)
		{
			if(INPUT_P23 == 0)
			{
				delay_ms(50);
				if(INPUT_P23 == 0)
				{
					step = 7;
					OUTPUT_11 = 1; //���Ƹ�
					play_mp3(0,18);
				}
			} 
		}
	}
}

int PLAY_6_BTN()
{
  	int i ;
	GET_ARRAY_LEN(buttonStep[btnTime] , totalLength);	
	if(INPUT_14 == 0)
	{
		delay_ms(50);
		if(INPUT_14 == 0)
		{
			while(INPUT_14==0); //�ɿ�
			button_step_player[btnTime][btnStep] = 6;
			btnStep++;
		}
	}
	
	if(INPUT_13 == 0)
	{
		delay_ms(50);
		if(INPUT_13 == 0)
		{
			while(INPUT_13==0); //�ɿ� 
			button_step_player[btnTime][btnStep] =  5;
	   		btnStep++;
		}
	}
	
	if(INPUT_07 == 0)
	{
		delay_ms(50);
		if(INPUT_07 == 0)
		{
			while(INPUT_07==0); //�ɿ� 
			button_step_player[btnTime][btnStep] =  4;
		   	btnStep++;
		}
	}

	if(INPUT_24 == 0)
	{
		delay_ms(50);
		if(INPUT_24 == 0)
		{
			while(INPUT_24==0); //�ɿ�
			button_step_player[btnTime][btnStep] =  1;			
		   	btnStep++;
		}
	}

	if(INPUT_25 == 0)
	{
		delay_ms(50);
		if(INPUT_25 == 0)
		{
			while(INPUT_25 == 0); //�ɿ� 			
			button_step_player[btnTime][btnStep] = 2;			
			btnStep++;
		}
	}

	if(INPUT_26 == 0)
	{
		delay_ms(50);
		if(INPUT_26 == 0)
		{
			while(INPUT_26 == 0); //�ɿ� 
			button_step_player[btnTime][btnStep] = 3;			
			btnStep ++;
		}
	}

	if(btnStep == totalLength) //�����㹻�Ĳ��� 
	{
		for(i = 0 ; i < totalLength ; i++)
		{
			if((button_step_player[btnTime][i] != buttonStep[btnTime][i]))
			{
				btnStep = 0; //�д��� ��Ҳ�����0 ������ 
				memset(button_step_player[btnTime],0,totalLength);
			
				if(btnTime == 0)
				{
					play_mp3(0,13);
				}
				else if(btnTime == 1)
				{
					play_mp3(0,14);
				}
				else if(btnTime == 2)
				{
					play_mp3(0,15);
				}
				else if(btnTime == 3)
				{
					play_mp3(0,16);
				}
				return 0;
			}
		}
		return 1;
	} 
	return 0;
}



//��ʼ�����п�
void INIT_COM()
{
	INPUT_06 = 1;
	INPUT_15 = 1;

	//�Ƹ�
	OUTPUT_10 = 0;
	OUTPUT_11 = 0;
	OUTPUT_12 = 0;

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
	INPUT_14 = 1;
	INPUT_13 = 1;
	INPUT_07 = 1;
	INPUT_26 = 1;
	INPUT_24 = 1;
	INPUT_25 = 1;
	
	//�������� 
	INPUT_P23 = 1;
}