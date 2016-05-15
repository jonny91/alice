#include <STC/STC12C5A60S2.H>
#include <string.h>
#include <common.h>
#include "uart.h"
#include "mp3.h"

//��ˮ�� �����
sbit OUTPUT_07 = P0^7;
//�������Ƹ�
sbit OUTPUT_21 = P2^1; //��ʼ�� �ߵ�ƽ
sbit OUTPUT_22 = P2^2;

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
sbit INPUT_46 = P4^6;
sbit INPUT_42 = P4^2;
sbit INPUT_10 = P1^0;


//��ǰ�Ĳ��� û�в���� = 0
signed char step = 0;

int btnStep = 0;//��Ұ����ڼ��� 
int totalLength;//��ť �ܲ���
char code buttonStep[] = {1,2,3,4,5,6};
char button_step_player[] = {0};

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
			if(INPUT_06 == 1)	//ˮ�ܽ�ͨ
			{
				delay_ms(50);
				if(INPUT_06 == 1)
				{
					OUTPUT_07 = 0;
					play_mp3(0,1);
					step = 1;
				}			
			}	
		}
		if(step == 1)
		{
			if(INPUT_05 == 0 && INPUT_04 == 0 && INPUT_03 == 0 && INPUT_02 == 0 && INPUT_01 == 0 && INPUT_00 == 0)
			{
				delay_ms(50);
				if(INPUT_05 == 0 && INPUT_04 == 0 && INPUT_03 == 0 && INPUT_02 == 0 && INPUT_01 == 0 && INPUT_00 == 0)
				{
					step = 2;  //6���Ž��Ŷ���
					play_mp3(0,1);
				}
			}
		}
		if(step == 2)  //��6����ť
		{
			if(PLAY_6_BTN() == 1)	 //������
			{
				step = 3;
				OUTPUT_21 = 0;	 //���Ƹ�
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
					OUTPUT_22 = 0; //���Ƹ�
					play_mp3(0,10);
				}
			} 
		}
	}
}

int PLAY_6_BTN()
{
  	int i;
	GET_ARRAY_LEN(buttonStep , totalLength);	
	if(INPUT_44 == 1)
	{
		delay_ms(50);
		if(INPUT_44 == 1)
		{
			while(INPUT_44 == 0); //�ɿ� 
			button_step_player[btnStep] =  1;
			btnStep ++;
			play_mp3(0,2);
		}
	}
	
	if(INPUT_45 == 1)
	{
		delay_ms(50);
		if(INPUT_45 == 1)
		{
			while(INPUT_45 == 0); //�ɿ� 
			button_step_player[btnStep] =  2;
	   		btnStep ++;
   			play_mp3(0,3);
		}
	}
	
	if(INPUT_41 == 1)
	{
		delay_ms(50);
		if(INPUT_41 == 1)
		{
			while(INPUT_41 == 0); //�ɿ� 
			button_step_player[btnStep] =  3;
		   	btnStep ++;
			play_mp3(0,4);
		}
	}
	
	if(INPUT_46 == 1)
	{
		delay_ms(50);
		if(INPUT_46 == 1)
		{
			while(INPUT_46 == 0); //�ɿ� 			
			button_step_player[btnStep] =  4;			
		   	btnStep ++;
			play_mp3(0,5);
		}
	}

	if(INPUT_42 == 1)
	{
		delay_ms(50);
		if(INPUT_42 == 1)
		{
			while(INPUT_42 == 0); //�ɿ� 			
			button_step_player[btnStep] =  5;			
			btnStep ++;
			play_mp3(0,6);
		}
	}

	if(INPUT_10 == 1)
	{
		delay_ms(50);
		if(INPUT_10 == 1)
		{
			while(INPUT_10 == 0); //�ɿ� 
			button_step_player[btnStep] =  6;			
			btnStep ++;
			play_mp3(0,7);
		}
	}

	if(btnStep == totalLength) //�����㹻�Ĳ��� 
	{
		for(i = 0 ; i < totalLength ; i++)
		{
			if(button_step_player[i] != buttonStep[i])
			{
				btnStep = 0; //�д��� ��Ҳ�����0 ������ 
				return 0;
			}
		}
		play_mp3(0,8);
		return 1;
	} 
	return 0;
}



//��ʼ�����п�
void INIT_COM()
{
	INPUT_06 = 0;

	//�Ƹ�
	OUTPUT_21 = 1;
	OUTPUT_22 = 1;

	//��ˮ�� ��������
	OUTPUT_07 = 1;

	//6���Ž� Ĭ���Ž���
	INPUT_05 = 1;
	INPUT_04 = 1;
	INPUT_03 = 1;
	INPUT_02 = 1;
	INPUT_01 = 1;
	INPUT_00 = 1;

	//6����ť
	INPUT_44 = 0;
	INPUT_45 = 0;
	INPUT_41 = 0;
	INPUT_46 = 0;
	INPUT_42 = 0;
	INPUT_10 = 0;
	
	//�������� 
	INPUT_P23 = 1;
}