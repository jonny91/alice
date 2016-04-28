#include <STC/STC12C5A60S2.H>
#include <common.h>
#include "uart.h"
#include "mp3.h"

sbit STEP_0_SIGNAL = P0^5;	//第一关开启 关门
sbit STEP_1_SIGNAL = P0^0;	  //第一关完成
sbit STEP_2_SIGNAL = P0^4;	   //第二个完成 霍尔开关的接入
sbit STEP_5_LINE_SIGNAL = P4^0; //16个点连线接入
sbit STEP_5_TO_6_DOOR =  P4^2; //第五关完成的电磁锁 
//当前的步骤 没有参与过 = 0
signed char step = 0;

void playStep3();

void main()
{
	sys_init();
	mp3_init();
	
	while(1)
	{
		if(step == 0)
		{
			if(STEP_0_SIGNAL == 1) //门关了 
			{
				step = 2; 
				delay_ms(5000);
				
				playMp3(0x00,0x01);	   //播放第一个文件夹的第一个音乐
			} 
		}
		//第一关由敲门开关控制 直接就算完成了 
		if(step == 2)  //机关4
		{
			if(STEP_2_SIGNAL == 1) //霍尔开关 
			{
				step = 5; //进去第5个谜题 
				
				delay_ms(5000);
				playMp3(0x00,0x02);
			}
		}
		
		if(step == 5) //机关5 接电线 
		{
			if(STEP_5_LINE_SIGNAL == 1)
			{
				delay_ms(500);
				if(STEP_5_LINE_SIGNAL == 1) //接线成功 第5关完成 
				{
					step = 6;
					playMp3(0x00,0x02);
				 	STEP_5_TO_6_DOOR = 0; //电磁锁开门 
				}
			} 
		} 
	}
}

//初始化所有口
void INIT_COM()
{
	
}