#include <STC12C5A60S2.H>
#include "common.h"
#include "uart.h" 
#include "mp3.h"

sbit INPUT_2 = P0^1; //2�� ������·���� 
sbit OUTPUT_2_DOOR = P0^1; //2 ��3�� ����� 
sbit INPUT_3_LINE_SIGNAL = P0^1; //3 �� ����������·���� 
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
					OUTPUT_2_DOOR = 0; // ��2��3�ĵش��� 
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