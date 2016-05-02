#include <STC/STC12C5A60S2.H>
#include <common.h>
#include "uart.h"
#include "mp3.h"

sbit STEP_0_SIGNAL = P4^4;	//第一关开启 关门
sbit STEP_1_SIGNAL = P0^0;	  //第一关完成
sbit STEP_2_SIGNAL = P0^4;	   //第二个完成 霍尔开关的接入
sbit STEP_5_SIGANL = P1^4; // 
sbit STEP_6_LINE_SIGNAL = P4^0; //16个点连线接入
sbit STEP_6_TO_7_DOOR =  P4^2; //第六关完成的电磁锁
sbit STEP_7_DOOR = P1^2;
sbit STEP_7_SIGNAL = P1^3; 

sbit TEST_HIGH = P0^1;
sbit TEST_LOW = P0^2;
//当前的步骤 没有参与过 = 0
signed char step = 0;

sbit OUT3_2 = P3^2;
sbit OUT3_3 = P3^3;
sbit OUT3_4 = P3^4;
sbit OUT3_5 = P3^5;
sbit OUT3_6 = P3^6;
sbit OUT3_7 = P3^7;

void playStep3();

void main()
{
	sys_init();
	OUT3_2 = 0;
	OUT3_3 = 0;
	OUT3_4 = 0;	
	OUT3_5 = 0;	
	OUT3_6 = 0;	
	OUT3_7 = 0;
	uart_init();
	mp3_init();
	play_mp3(0x00,0x01);
	return;
	
	while(1)
	{
		TEST_HIGH = 1;
		TEST_LOW = 0;
		if(step == 0)
		{
			mp3(0x00);
			if(STEP_0_SIGNAL == 1) //门关了 
			{
				step = 2; 
				delay_ms(5000);
				
				play_mp3(0x00,0x01);	   //播放第一个文件夹的第一个音乐
			} 
		}
		//第一关由敲门开关控制 直接就算完成了 
		if(step == 2)  //机关4
		{
			if(STEP_2_SIGNAL == 1) //霍尔开关 
			{
				step = 5; //进去第5个谜题 
				
				delay_ms(5000);
				play_mp3(0x00,0x02);
			}
		}

		if(step == 5)
		{
			if(STEP_6_LINE_SIGNAL == 1)
			{	
				delay_ms(500);
				if(STEP_5_SIGANL == 1)
				{
					step = 6;
				} 
			} 
		}
		
		if(step == 6) //机关5 接电线 
		{
			if(STEP_6_LINE_SIGNAL == 1)
			{
				delay_ms(500);
				if(STEP_6_LINE_SIGNAL == 1) //接线成功 第6关完成 
				{
					step = 7;
					play_mp3(0x00,0x02);
				 	STEP_6_TO_7_DOOR = 0; //电磁锁开门 
				}
			} 
		}
		
		if(step == 7)//茶会解密
		{
			if(STEP_7_SIGNAL == 1)
			{
				delay_ms(500);
				if(STEP_7_SIGNAL == 1)
				{
					step = 8;
					play_mp3(0x00,0x02);
					
					STEP_7_DOOR = 0; //打开7的门 
				}
			}
		} 
	}
}

//初始化所有口
void INIT_COM()
{
	
}