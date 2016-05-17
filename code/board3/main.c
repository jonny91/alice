#include <STC12C5A60S2.H>
#include <string.h>
#include <common.h>
#include "uart.h"
#include "mp3.h"

//4个按钮输入 
sbit INPUT_06 = P0^6;
sbit INPUT_07 = P0^7;
sbit INPUT_46 = P4^6;
sbit INPUT_41 = P4^1;

sbit INPUT_05 = P0^5; 

//涂玫瑰 电磁锁
sbit OUTPUT_43 = P4^3;
//最后一个电磁锁
sbit OUTPUT_17 = P1^7;

//接灯带
//第一个灯:
//RGB
sbit OUTPUT_00 = P0^0;
sbit OUTPUT_01 = P0^1;
sbit OUTPUT_02 = P0^2;
//第二个灯:
//RGB
sbit OUTPUT_03 = P0^3;
sbit OUTPUT_04 = P0^4;
sbit OUTPUT_45 = P4^5;
//第三个灯:
//RGB
sbit OUTPUT_27 = P2^7;
sbit OUTPUT_26 = P2^6;
sbit OUTPUT_25 = P2^5;
//第四个灯:
//RGB
sbit OUTPUT_40 = P4^0;
sbit OUTPUT_20 = P2^0;
sbit OUTPUT_21 = P2^1;  

char step = 0; 

//RGB RED:011b = 3	低电平亮
char color[] = {0,1,2,3,4,5,6,7}; //8种颜色
//初始化都灭
char color_step_0 = 7;
char color_step_1 = 7;
char color_step_2 = 7;
char color_step_3 = 7;

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
			if(INPUT_06 == 0)
			{
				delay_ms(50);
				if(INPUT_06 == 0)
				{
					color_step_0 = (++color_step_0)%8;
					color_step_1 = (++color_step_1)%8;
					light(0,color_step_0);
					light(1,color_step_1);
				}
			} 
			
			if(INPUT_07 == 0)
			{
				delay_ms(50);
				if(INPUT_07 == 0)
				{
					color_step_0 = (++color_step_0)%8;
					color_step_1 = (++color_step_1)%8;	
					color_step_2 = (++color_step_2)%8;
					light(0,color_step_0);
					light(1,color_step_1);
					light(2,color_step_2);
				}
			} 
			
			if(INPUT_46 == 0)
			{
				delay_ms(50);
				if(INPUT_46 == 0)
				{
					color_step_1 = (++color_step_1)%8; 
					color_step_2 = (++color_step_2)%8;	
					color_step_3 = (++color_step_3)%8;
					
					light(1,color_step_1);
					light(2,color_step_2);									
					light(3,color_step_3);
				}
			} 
			
			if(INPUT_41 == 0)
			{
				delay_ms(50);
				if(INPUT_41 == 0)
				{
					color_step_2 = (++color_step_2)%8;
					color_step_3 = (++color_step_3)%8;
					light(2,color_step_2);									
					light(3,color_step_3);
				}
			}
			
			if(color_step_0 == 4 && color_step_1 == 4 && color_step_2 == 4 && color_step_3 == 4)
			{
				step = 2;
				OUTPUT_43 = 0 ;//打开电磁锁 
			}
		}
		
		if(step == 2)
		{
			if(INPUT_05 == 0)
			{
				delay_ms(50);
				if(INPUT_05 == 0)
				{
					step = 3; 
					OUTPUT_17 = 0;//最后一个门 
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
			OUTPUT_00 = (color & 4)>>2; 
			OUTPUT_01 = (color & 2)>>1;
			OUTPUT_02 = color & 1;	
			break;
		}
		
		case 1:
		{
			OUTPUT_03 = (color & 4)>>2; 
			OUTPUT_04 = (color & 2)>>1;
			OUTPUT_25 = color & 1;		
			break;
		}
		
		case 2:
		{
			OUTPUT_27 = (color & 4)>>2; 
			OUTPUT_26 = (color & 2)>>1;
			OUTPUT_25 = color & 1;	
			break;
		}
		
		case 3:
		{
			OUTPUT_40 = (color & 4)>>2; 
			OUTPUT_20 = (color & 2)>>1;
			OUTPUT_21 = color & 1;	
			break;
		}
	}
}

void INIT_COM()
{
	INPUT_06 = 1;
	INPUT_07 = 1; 
	INPUT_46 = 1; 
	INPUT_41 = 1;
	INPUT_05 = 1;
	
	OUTPUT_43 = 1;
	OUTPUT_17 = 1;
	
	OUTPUT_00 = 1; 
	OUTPUT_01 = 1;
	OUTPUT_02 = 1;
	
	OUTPUT_03 = 1;
	OUTPUT_04 = 1;
	OUTPUT_25 = 1;
	
	OUTPUT_27 = 1;
	OUTPUT_26 = 1;
	OUTPUT_25 = 1;
	
	OUTPUT_40 = 1;
	OUTPUT_20 = 1;
	OUTPUT_21 = 1;
}