#include <STC12C5A60S2.H>
#include <string.h>
#include <common.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "mp3.h"

//4个按钮输入 
sbit INPUT_04 = P0^4;
sbit INPUT_03 = P0^3;
sbit INPUT_23 = P2^3;
sbit INPUT_01 = P0^1;

//霍尔开关输入
sbit INPUT_00 = P0^0; 

//涂玫瑰 电磁锁
sbit OUTPUT_21 = P2^1;
//最后一个电磁锁
sbit OUTPUT_22 = P2^2;

//接灯带
//第一个灯:
//RGB
sbit OUTPUT_42 = P4^2;
sbit OUTPUT_10 = P1^0;
sbit OUTPUT_11 = P1^1;
//第二个灯:
//RGB
sbit OUTPUT_12 = P1^2;
sbit OUTPUT_13 = P1^3;
sbit OUTPUT_14 = P1^4;
//第三个灯:
//RGB
sbit OUTPUT_15 = P1^5;
sbit OUTPUT_16 = P1^6;
sbit OUTPUT_17 = P1^7;
//第四个灯:
//RGB
sbit OUTPUT_43 = P4^3;
sbit OUTPUT_40 = P4^0;
sbit OUTPUT_20 = P2^0;  

char step = 0; 

//RGB RED:100b = 4	
unsigned char color[8] = {0,1,2,3,4,5,6,7}; //8种颜色
//初始化都灭
int color_step_0 = 4;
int color_step_1 = 4;
int color_step_2 = 4;
int color_step_3 = 4;

void light(char lightNumber , char color);
void INIT_COM();
void main()
{        
	sys_init();
	INIT_COM();

	uart_init();
	mp3_init();

	while((color_step_0 == 4)&&( color_step_1 == 4)&&( color_step_2 == 4)&&( color_step_3 == 4))
	{
		color_step_0 = rand()%8;
		color_step_1 = rand()%8;
		color_step_2 = rand()%8;
		color_step_3 = rand()%8;	
	}
	
	light(0,color[color_step_0]);
	light(1,color[color_step_1]);
	light(2,color[color_step_2]);
	light(3,color[color_step_3]);
	while(1)
	{
		if(step == 0)
		{
			if(INPUT_04 == 0)  //J9
			{
				delay_ms(50);
				if(INPUT_04 == 0)
				{
					color_step_0++;
					color_step_1++;
					color_step_0 = (color_step_0)%8;
					color_step_1 = (color_step_1)%8;
					light(0,color_step_0);
					light(1,color_step_1);

					delay_ms(50);
				}
			} 
			
			else if(INPUT_03 == 0)		//J8
			{
				delay_ms(50);
				if(INPUT_03 == 0)
				{
					color_step_0++;
					color_step_1++;
					color_step_2++;
					color_step_0 = (color_step_0)%8;
					color_step_1 = (color_step_1)%8;	
					color_step_2 = (color_step_2)%8;
					light(0,color_step_0);
					light(1,color_step_1);
					light(2,color_step_2);

						 
					delay_ms(50);
				}
			} 
			
			else if(INPUT_23 == 0)			 //J7
			{
				delay_ms(50);
				if(INPUT_23 == 0)
				{
					color_step_1++;
					color_step_2++;
					color_step_3++;
					color_step_1 = (color_step_1)%8; 
					color_step_2 = (color_step_2)%8;	
					color_step_3 = (color_step_3)%8;
					
					light(1,color_step_1);
					light(2,color_step_2);									
					light(3,color_step_3);

					delay_ms(50);
				}
			} 
			
			else if(INPUT_01 == 0)	 //J6
			{
				delay_ms(50);
				if(INPUT_01 == 0)
				{
					color_step_2++;
					color_step_3++;
					color_step_2 = (color_step_2)%8;
					color_step_3 = (color_step_3)%8;
					light(2,color_step_2);									
					light(3,color_step_3);

					delay_ms(50);
				}
			}

			while(INPUT_04 == 0);
			while(INPUT_03 == 0);
			while(INPUT_23 == 0);
			while(INPUT_01 == 0);
			
			
			if(color_step_0 == 4 && color_step_1 == 4 && color_step_2 == 4 && color_step_3 == 4)
			{
				step = 1;
				OUTPUT_21 = 0 ;//打开电磁锁 

				play_mp3(0,1); //玫瑰完成 +　馅饼开门提示
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
					delay_ms(1000);
					OUTPUT_22 = 0;//最后一个门 
					delay_ms(100);
					
					play_mp3(0,2);
					delay_ms(5000);
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
			OUTPUT_42 = ((color & 4)>>2); 
			OUTPUT_10 = ((color & 2)>>1);
			OUTPUT_11 = (color & 1);	
			break;
		}
		
		case 1:
		{
			OUTPUT_12 = ((color & 4)>>2); 
			OUTPUT_13 = ((color & 2)>>1);
			OUTPUT_14 = (color & 1);		
			break;
		}
		
		case 2:
		{
			OUTPUT_15 = ((color & 4)>>2); 
			OUTPUT_16 = ((color & 2)>>1);
			OUTPUT_17 = (color & 1);	
			break;
		}
		
		case 3:
		{
			OUTPUT_43 = ((color & 4)>>2); 
			OUTPUT_40 = ((color & 2)>>1);
			OUTPUT_20 = (color & 1);	
			break;
		}
	}
}

void INIT_COM()
{
	INPUT_04 = 1;
	INPUT_03 = 1; 
	INPUT_23 = 1; 
	INPUT_01 = 1;
	INPUT_00 = 1;
	
	OUTPUT_21 = 1;
	OUTPUT_17 = 1;
	
	OUTPUT_43 = 0; 
	OUTPUT_17 = 0;
	OUTPUT_16 = 0;
	
	OUTPUT_15 = 0;
	OUTPUT_14 = 0;
	OUTPUT_13 = 0;
	
	OUTPUT_12 = 0;
	OUTPUT_11 = 0;
	OUTPUT_10 = 0;
	
	OUTPUT_42 = 0;
	OUTPUT_40 = 0;
	OUTPUT_20 = 0;
}