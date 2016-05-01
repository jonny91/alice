#include <STC12C5A60S2.H>
#include "common.h"
#include "uart.h" 
#include "mp3.h"

sbit INPUT_2 = P0^1; //2中 串联线路输入 
sbit OUTPUT_2_DOOR = P0^1; //2 到3的 电磁锁 
sbit INPUT_3_LINE_SIGNAL = P0^1; //3 的 霍尔开关线路输入 
unsigned char step = 2;

void main()
{
	sys_init();
	mp3_init(); 
	while(1)
	{
		if(step == 2)
		{		
			if(INPUT_2 == 1)
			{
				delay_ms(500);
				if(INPUT_2 == 1)
				{
					OUTPUT_2_DOOR = 0; // 打开2到3的地磁锁 
					step = 3;
				}			
			}
		}
		
		if(step == 3)
		{
			if(INPUT_3_LINE_SIGNAL == 1)
			{
				delay_ms(500); 
				if(INPUT_3_LINE_SIGNAL == 1)
				{
					
				}
			} 
		}
	}
}