#include <STC/STC12C5A60S2.H>
#include <string.h>
#include <common.h>
#include "uart.h"
#include "mp3.h"

//接水管 电磁锁
sbit OUTPUT_07 = P0^7;
//接通水管 按钮通电
sbit OUTPUT_42 = P4^2;
//正反接推杆
sbit OUTPUT_10 = P1^0; //初始化 高电平
sbit OUTPUT_11 = P1^1;

//水管外接到内部
sbit INPUT_06 = P0^6;
//6个门禁
sbit INPUT_05 = P0^5;
sbit INPUT_04 = P0^4;
sbit INPUT_03 = P0^3;
sbit INPUT_02 = P0^2;
sbit INPUT_01 = P0^1;
sbit INPUT_00 = P0^0;

//霍尔开关串联输入
sbit INPUT_P23 = P2^3; 

//6个按钮
sbit INPUT_44 = P4^4;
sbit INPUT_45 = P4^5;
sbit INPUT_41 = P4^1;

sbit INPUT_24 = P2^4;
sbit INPUT_25 = P2^5;
sbit INPUT_26 = P2^6;

//当前的步骤 没有参与过 = 0
unsigned char step = 0;

unsigned char step_1_flag_1 = 0;
unsigned char step_1_flag_2 = 0;
unsigned char step_1_flag_3 = 0;
unsigned char step_1_flag_4 = 0;
unsigned char step_1_flag_5 = 0;
unsigned char step_1_flag_6 = 0;

int btnStep = 0;//玩家按到第几个 
int totalLength;//按钮 总步骤
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
			if(INPUT_06 == 0)	//水管接通
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
				step = 2;  //6个门禁放对了
				OUTPUT_42 = 1;
				play_mp3(0,1);
			}
		}
		if(step == 2)  //按6个按钮
		{
			if(PLAY_6_BTN() == 1)	 //按对了
			{
				step = 3;
			
				OUTPUT_42 = 0; //关闭按钮灯

				OUTPUT_10 = 1;	 //打开推杆
				play_mp3(0,9);
			}
		}

		if(step == 3)
		{
			if(INPUT_P23 == 0)
			{
				delay_ms(50);
				if(INPUT_P23 == 0)
				{
					step = 4;
					OUTPUT_11 = 1; //打开推杆
					play_mp3(0,10);
				}
			} 
		}
	}
}

int PLAY_6_BTN()
{
  	int i ;
	GET_ARRAY_LEN(buttonStep , totalLength);	
	if(INPUT_44 == 0)
	{
		delay_ms(50);
		if(INPUT_44 == 0)
		{
			while(INPUT_44 == 0); //松开
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
			while(INPUT_45 == 0); //松开 
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
			while(INPUT_41 == 0); //松开 
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
			while(INPUT_24 == 0); //松开
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
			while(INPUT_25 == 0); //松开 			
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
			while(INPUT_26 == 0); //松开 
			button_step_player[btnStep] =  6;			
			btnStep ++;
			play_mp3(0,7);
		}
	}

	if(btnStep == totalLength) //按完足够的步数 
	{
		for(i = 0 ; i < totalLength ; i++)
		{
			if((button_step_player[i] != buttonStep[i]))
			{
				btnStep = 0; //有错误 玩家步骤清0 重新来 
				memset(button_step_player,0,totalLength);
				OUTPUT_42 = 0;
				delay_ms(2000);
				OUTPUT_42 = 1;
				return 0;
			}
		}
		//按对了
		return 1;
	} 
	return 0;
}



//初始化所有口
void INIT_COM()
{
	INPUT_06 = 1;

	//推杆
	OUTPUT_10 = 0;
	OUTPUT_11 = 0;

	//接水管 输出电磁锁
	OUTPUT_07 = 1;
	//接通水管 按钮通电
	OUTPUT_42 = 0;

	//6个门禁 默认门禁打开
	INPUT_05 = 1;
	INPUT_04 = 1;
	INPUT_03 = 1;
	INPUT_02 = 1;
	INPUT_01 = 1;
	INPUT_00 = 1;

	//6个按钮
	INPUT_44 = 1;
	INPUT_45 = 1;
	INPUT_41 = 1;
	INPUT_26 = 1;
	INPUT_24 = 1;
	INPUT_25 = 1;
	
	//霍尔开关 
	INPUT_P23 = 1;
}