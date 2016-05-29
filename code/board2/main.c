#include <STC/STC12C5A60S2.H>
#include "common.h"
#include "uart.h" 
#include "mp3.h"

//两个继电器 输入
sbit INPUT_40 = P4^0;
sbit INPUT_20 = P2^0;

//4个信箱 继电器
sbit INPUT_44 = P4^4; 
sbit INPUT_45 = P4^5; 
sbit INPUT_01 = P0^1; 
sbit INPUT_02 = P0^2; 

//接电线继电器
sbit INPUT_21 = P2^1;

//信封 + 接电线 电磁锁开关
sbit OUTPUT_43 = P4^3; 

//最后电磁锁
sbit OUTPUT_17 = P1^7;

char step = 0;
void INIT_COM();

char message[4] = {0,0,0,0};
char i = 0;

char step1_0 = 0;
char step1_1 = 0; //两个门禁
char step1_2 = 0;//接电线

void main()
{
	sys_init();
	INIT_COM();
	uart_init();
	mp3_init();
	
	play_mp3(0,1);

	while(1)
	{
		if(step == 0)
		{
			if( (step1_0 == 0) && (INPUT_40 == 0))
			{
				delay_ms(50);
				if( (step1_0 == 0) && (INPUT_40 == 0))
				{
					step1_0 = 1;
					play_mp3(0,1);
				}
			}

			if( (step1_1 == 0) && (INPUT_20 == 0))
			{
				delay_ms(50);
				if( (step1_1 == 0) && (INPUT_20 == 0))
				{
					step1_1 = 1;
					play_mp3(0,2);
				}
			}

			if((step1_2 == 0)&&(INPUT_21 == 0))
			{
				delay_ms(50);
				if((step1_2 == 0)&&(INPUT_21 == 0))
				{
					step1_2 = 1;
					play_mp3(0,3);
				}
			}

			if((step1_0 == 1)&&(step1_1 == 1)&&(step1_2==1))
			{
				OUTPUT_43 = 0;
				step = 1;
				play_mp3(0,4);
			}
		}
		
		//信封
		if(step == 1)
		{
			if(INPUT_44 == 0)
			{
				message[0] = 1;
				play_mp3(0,1);
			}
			if(INPUT_45 == 0)
			{
				message[1] = 1;
				play_mp3(0,2);
			}
			if(INPUT_01 == 0)
			{
				message[2] = 1;
				play_mp3(0,3);
			}
			if(INPUT_02 == 0)
			{
				message[3] = 1;
				play_mp3(0,4);
			}


			if((message[0]==1)&&(message[1]==1)&&(message[2]==1)&&(message[3]==1))
			{
				 step = 2;		 //信封完成
				 OUTPUT_17 = 0;
				 play_mp3(0,5);
			}
		} 
	} 
}


//初始化所有口
void INIT_COM()
{
	OUTPUT_43 = 1;
	INPUT_40 = 1;
	INPUT_20 = 1;
	INPUT_21 = 1;

	INPUT_44 = 1;
	INPUT_45 = 1;
	INPUT_01 = 1;
	INPUT_02 = 1;

	OUTPUT_17 = 1;
}