#include <stc12.h>
#include "uart.h"

sbit STEP_1_SIGNAL = P0^0;	  //第一关完成
sbit STEP_2_SIGNAL = P0^1;
//当前的步骤 没有参与过 = 0
unsigned char step = 0;

void playStep3();

void main()
{
	TMOD = 0x01;
	EA = 1;
	ET0 = 1;
	TH0 = 0xB8;
	TL0 = 0;
}

void interruptTimer() interrupt 1
{
	TH0 = 0xB8;
	TL0 = 0;
	
	//当前第0步骤 
	if(step == 0)
	{
		if(STEP_1_SIGNAL == 1)
		{
			step = 1;
		} 
	}
	else if(step == 1)	   //第一关完成
	{
		if(STEP_2_SIGNAL == 1)
		{
			step = 2;
		}
	}
	else if(step == 2)	  //第二关完成
	{
		playStep3();
	}
}

void playStep3()
{
}