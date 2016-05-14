#include <STC/STC12C5A60S2.H>
#include <string.h>
#include <common.h>
#include "uart.h"
#include "mp3.h"

//接水管 电磁锁
sbit OUTPUT_07 = P0^7;
//正反接推杆
sbit OUTPUT_21 = P2^1;
sbit OUTPUT_22 = P2^2;

//水管外接到内部
sbit INPUT_06 = P0^6;
//6个门禁
sbit INPUT_05 = P0^5;
sbit INPUT_04 = P0^4;
sbit INPUT_03 = P0^3;
sbit INPUT_02 = P0^2;
sbit INPUT_01 = P0^1;
sbit INPUT_00 = P0^0;

//6个按钮
sbit INPUT_44 = P4^4;
sbit INPUT_45 = P4^5;
sbit INPUT_41 = P4^1;
sbit INPUT_46 = P4^6;
sbit INPUT_42 = P4^2;
sbit INPUT_10 = P1^0;


//当前的步骤 没有参与过 = 0
signed char step = 0;

int totalLength;//按钮 总步骤
char buttonStep[] = {1,2,3,4,5,6};
char buttonStepPlayer[];
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
			if(INPUT_06 == 1)	//水管接通
			{
				delay_ms(50);
				if(INPUT_06 == 1)
				{
					OUTPUT_07 = 0;
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
					step = 2;  //6个门禁放对了
				}
			}
		}
		if(step == 2)  //按6个按钮
		{
			if(PLAY_6_BTN() == 1)	 //按对了
			{
				step = 3;
				OUTPUT_21 = 1;	 //打开推杆
				OUTPUT_22 = 0;
			}
		}

		if(step == 3)
		{
			
		}
	}
}

int btnStep = 0;
int PLAY_6_BTN()
{
  	int i;
	GET_ARRAY_LEN(buttonStep , totalLength);	
	if(INPUT_44 == 1)
	{
		delay_ms(50);
		if(INPUT_44 == 1)
		{
			buttonStepPlayer[btnStep] =  1;
			btnStep ++;
		}
	}
	
	if(INPUT_45 == 1)
	{
		delay_ms(50);
		if(INPUT_45 == 1)
		{
			buttonStepPlayer[btnStep] =  2;
	   		btnStep ++;
		}
	}
	
	if(INPUT_41 == 1)
	{
		delay_ms(50);
		if(INPUT_41 == 1)
		{
			buttonStepPlayer[btnStep] =  3;
		   	btnStep ++;
		}
	}
	
	if(INPUT_46 == 1)
	{
		delay_ms(50);
		if(INPUT_46 == 1)
		{
			buttonStepPlayer[btnStep] =  4;			
		   	btnStep ++;
		}
	}

	if(INPUT_42 == 1)
	{
		delay_ms(50);
		if(INPUT_42 == 1)
		{
			buttonStepPlayer[btnStep] =  5;			
			btnStep ++;
		}
	}

	if(INPUT_10 == 1)
	{
		delay_ms(50);
		if(INPUT_10 == 1)
		{
			buttonStepPlayer[btnStep] =  6;			
			btnStep ++;
		}
	}

	
	for(i = 0 ; i < btnStep ; i++)
	{
		if(buttonStepPlayer[i] == buttonStep[i])
		{
			continue;
		}
		else   //如果有一位不一样
		{
			memset(buttonStepPlayer,0,sizeof(buttonStepPlayer));
			i = 0;
			break;
		}
	}

	if(i == totalLength - 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}



//初始化所有口
void INIT_COM()
{
	INPUT_06 = 0;

	//推杆
	OUTPUT_21 = 0;
	OUTPUT_22 = 1;

	//接水管 输出电磁锁
	OUTPUT_07 = 1;

	//6个门禁 默认门禁打开
	INPUT_05 = 1;
	INPUT_04 = 1;
	INPUT_03 = 1;
	INPUT_02 = 1;
	INPUT_01 = 1;
	INPUT_00 = 1;

	//6个按钮
	INPUT_44 = 0;
	INPUT_45 = 0;
	INPUT_41 = 0;
	INPUT_46 = 0;
	INPUT_42 = 0;
	INPUT_10 = 0;

}