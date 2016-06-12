#include <STC/STC12C5A60S2.H>
#include <string.h>
#include <common.h>
#include "uart.h"
#include "mp3.h"

//接通水管 按钮通电
sbit OUTPUT_42 = P4^2;

//正反接推杆
sbit OUTPUT_10 = P1^0; //初始化 高电平
sbit OUTPUT_11 = P1^1;
sbit OUTPUT_12 = P1^2;

//水管外接到内部
sbit INPUT_06 = P0^6;
sbit INPUT_15 = P1^5;

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
sbit INPUT_14 = P1^4;
sbit INPUT_13 = P1^3;
sbit INPUT_07 = P0^7;

sbit INPUT_24 = P2^4;
sbit INPUT_25 = P2^5;
sbit INPUT_26 = P2^6;

//声音控制
sbit OUTPUT_16 = P1^6;
sbit INPUT_17 = P1^7;

//当前的步骤 没有参与过 = 0
unsigned char step = 0;

unsigned char step_1_flag_1 = 0;
unsigned char step_1_flag_2 = 0;
unsigned char step_1_flag_3 = 0;
unsigned char step_1_flag_4 = 0;
unsigned char step_1_flag_5 = 0;
unsigned char step_1_flag_6 = 0;

unsigned char btnTime = 0;//第几轮按钮
int btnStep = 0;//玩家按到第几个

//狗 兔子 老鼠 松鼠 猫 刺猬
unsigned char code buttonStep[4][6] = {{1,3,1,4,5,2},{1,6,2,5,3,4},{4,6,2,5,2,3},{5,2,3,4,5,3}};
unsigned char button_step_player[4][6] = {{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};

int PLAY_6_BTN(char count);
void INIT_COM();


void main()
{
	sys_init();
	INIT_COM();
	uart_init();
	mp3_init();

	//开机延迟 放背景音乐
	delay_ms(1000);
	play_mp3(0,0x01);

	while(1)
	{	
		if(INPUT_17 == 0)
		{
			delay_ms(50);
			if(INPUT_17 == 0)
			{
				delay_ms(50);
				//关闭声音
				mp3(0x02);
				INPUT_17 = 1;
			}
		}
		if(step == 0)
		{
			if((INPUT_06 == 0) && (INPUT_15 == 0))	//水管接通
			{
				delay_ms(50);
				if((INPUT_06 == 0) && (INPUT_15 == 0))	//水管接通
				{
					OUTPUT_12 = 1;  //电磁锁打开
					delay_ms(100);
			  		play_mp3(0,0x02);
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
					play_mp3(0,0x04);
				}
			}
			if( (INPUT_04 == 0) && (step_1_flag_2 == 0))
			{
			 	delay_ms(50);
				 if(INPUT_04 == 0)
				{
					step_1_flag_2 = 1;
					play_mp3(0,0x05);
				}
			}
			if( (INPUT_03 == 0)	&& (step_1_flag_3 == 0))
			{
			 	delay_ms(50);	
				if(INPUT_03 == 0)	
				{	
					step_1_flag_3 = 1;
					play_mp3(0,0x03);
				}
			}
			if( (INPUT_02 == 0) && (step_1_flag_4 == 0))
			{
			 	delay_ms(50);
				if(INPUT_02 == 0)	
				{
					step_1_flag_4 = 1;
					play_mp3(0,0x07);
				}
			}
			if((INPUT_01 == 0)&&(step_1_flag_5 == 0))
			{
			 	delay_ms(50);
				if(INPUT_01 == 0)
				{
					step_1_flag_5 = 1;
					play_mp3(0,0x06);
				}
			}
			if( (INPUT_00 == 0)	&& (step_1_flag_6 == 0))
			{
				delay_ms(50);
				if(INPUT_00 == 0)
				{	
					step_1_flag_6 = 1;
					play_mp3(0,0x08);
				}
			}
			if((step_1_flag_1==1)&&(step_1_flag_2 == 1)&&(step_1_flag_3 == 1)&&(step_1_flag_4==1)&&(step_1_flag_5==1)&&(step_1_flag_6==1))
			{			
				step = 2;  //6个门禁放对了
				OUTPUT_42 = 1;
				delay_ms(5000);			
				play_mp3(0,0x09); //全部摆对
			}
		}
		else if(step==2)  //按6个按钮
		{
			btnTime = 0;
			delay_ms(50);
			if(PLAY_6_BTN(6) == 1)	 //按对了
			{
				play_mp3(0,0x0a);
				step = 3;			
			}
		}

		else if(step == 3)
		{
			btnTime = 1;
			if(PLAY_6_BTN(6) == 1)
			{		
				play_mp3(0,0x0b);	  //第四局提示
				step = 4;
			}	
		}

		else if(step == 4)
		{
			btnTime = 2;
			if(PLAY_6_BTN(6) == 1)
			{
				play_mp3(0,0x0c);
				step = 5;
			}
		}
		else if(step == 5)
		{
			btnTime = 3;
			if(PLAY_6_BTN(6) == 1)
			{
				OUTPUT_42 = 0; //关闭按钮灯

				OUTPUT_10 = 1;	 //打开推杆
				delay_ms(5000);
				play_mp3(0,0x11); //全部正确 + 吃饼干提示

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
					OUTPUT_11 = 1; //打开推杆
					delay_ms(2000);
					//游戏结束P1.6变低电平，播放018
					OUTPUT_16 = 0;
					play_mp3(0,0x12);		  //吃饼干全部正确 + 背景音乐 + 找扇子提示
				}
			} 
		}
	}
}

int PLAY_6_BTN(char totalLength)
{
  	int i ;
	if(INPUT_14 == 0)
	{
		delay_ms(50);
		if(INPUT_14 == 0)
		{
			while(INPUT_14==0); //松开
			button_step_player[btnTime][btnStep] = 6;
			btnStep++;
		}
	}	
	else if(INPUT_13 == 0)
	{
		delay_ms(50);
		if(INPUT_13 == 0)
		{
			while(INPUT_13==0); //松开 
			button_step_player[btnTime][btnStep] =  5;
	   		btnStep++;
		}
	}	
	else if(INPUT_07 == 0)
	{
		delay_ms(50);
		if(INPUT_07 == 0)
		{
			while(INPUT_07==0); //松开 
			button_step_player[btnTime][btnStep] =  4;
		   	btnStep++;
		}
	}
	else if(INPUT_24 == 0)
	{
		delay_ms(50);
		if(INPUT_24 == 0)
		{
			while(INPUT_24==0); //松开
			button_step_player[btnTime][btnStep] =  1;			
		   	btnStep++;
		}
	}
	else if(INPUT_25 == 0)
	{
		delay_ms(50);
		if(INPUT_25 == 0)
		{
			while(INPUT_25 == 0); //松开 			
			button_step_player[btnTime][btnStep] = 2;			
			btnStep++;
		}
	}
	else if(INPUT_26 == 0)
	{
		delay_ms(50);
		if(INPUT_26 == 0)
		{
			while(INPUT_26 == 0); //松开 
			button_step_player[btnTime][btnStep] = 3;			
			btnStep ++;
		}
	}

	if(btnStep == totalLength) //按完足够的步数 
	{
		for(i = 0 ; i < totalLength ; i++)
		{
			if((button_step_player[btnTime][i] != buttonStep[btnTime][i]))
			{
				btnStep = 0; //有错误 玩家步骤清0 重新来 			
			
				if(btnTime == 0)
				{
					memset(button_step_player[btnTime],0,6);
					play_mp3(0,0x0d);
				}
				else if(btnTime == 1)
				{
					memset(button_step_player[btnTime],0,6);
					play_mp3(0,0x0e);
				}
				else if(btnTime == 2)
				{
					memset(button_step_player[btnTime],0,6);
					play_mp3(0,0x0f);
				}
				else if(btnTime == 3)
				{
					memset(button_step_player[btnTime],0,6);
					play_mp3(0,0x10);
				}
				return 0;
			}
		}

		btnStep = 0;
		return 1;
	} 
	return 0;
}



//初始化所有口
void INIT_COM()
{
	INPUT_06 = 1;
	INPUT_15 = 1;

	//推杆
	OUTPUT_10 = 0;
	OUTPUT_11 = 0;
	OUTPUT_12 = 0;

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
	INPUT_14 = 1;
	INPUT_13 = 1;
	INPUT_07 = 1;
	INPUT_26 = 1;
	INPUT_24 = 1;
	INPUT_25 = 1;
	
	//霍尔开关 
	INPUT_P23 = 1;
			
	//声音控制
	OUTPUT_16 = 1;
	INPUT_17 = 1;
}