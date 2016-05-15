#include <STC/STC12C5A60S2.H>
#include "common.h"
#include "uart.h" 
#include "mp3.h"

//两个继电器
sbit INPUT_00 = P0^0;
sbit INPUT_01 = P0^1;
//4个信箱 继电器
sbit INPUT_02 = P0^2; 
sbit INPUT_03 = P0^3; 
sbit INPUT_04 = P0^4; 
sbit INPUT_05 = P0^5; 

//接电线继电器
sbit INPUT_20 = P2^0;
sbit INPUT_21 = P2^1;
sbit INPUT_22 = P2^2;
sbit INPUT_23 = P2^3;
sbit INPUT_24 = P2^4;
sbit INPUT_25 = P2^5;
sbit INPUT_26 = P2^6;
sbit INPUT_27 = P2^7;

//接电线 推杆
sbit OUTPUT_34 = P3^4; 

//信封 电磁锁
sbit OUTPUT_43 = P4^3; 

char step = 0;
void INIT_COM();

char message[] = {0,0,0,0};
char i = 0;

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
			if(INPUT_00 == 0 && INPUT_01 == 0)
			{
				step = 1;
			}
		}

		//接电线
		if(step == 1)
		{
			if(INPUT_20 == 0 && INPUT_21 == 0 && INPUT_22 == 0 && INPUT_23 == 0 && INPUT_24 == 0 && INPUT_25 == 0 && INPUT_26 == 0 && INPUT_27 == 0)
			{
				OUTPUT_34 = 0;
				step = 2;
			}
		}
		
		if(step == 2)
		{
			if(INPUT_02 == 0)
			{
				message[0] = 1;
			}
			if(INPUT_03 == 0)
			{
				message[1] = 1;
			}
			if(INPUT_04 == 0)
			{
				message[2] = 1;
			}
			if(INPUT_05 == 0)
			{
				message[3] = 1;
			}

			for(i = 0 ; i < 4 ; i++)
			{
				if(i == 3 && message[i] == 1)
				{
					step = 3; //信封完成 
					OUTPUT_43 = 0;//电磁锁 断电 
				}
			}
		} 
	} 
}


//初始化所有口
void INIT_COM()
{
	INPUT_00 = 1;
	INPUT_01 = 1;

	INPUT_20 = 1;
	INPUT_21 = 1;
	INPUT_22 = 1;
	INPUT_23 = 1;
	INPUT_24 = 1;
	INPUT_25 = 1;
	INPUT_26 = 1;
	INPUT_27 = 1;
	
	OUTPUT_34 = 1;

	INPUT_02 = 1;
	INPUT_03 = 1;
	INPUT_04 = 1;
	INPUT_05 = 1;
	
	OUTPUT_43 = 1;
}