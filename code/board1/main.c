#include <STC/STC12C5A60S2.H>
#include <string.h>
#include <common.h>
#include "uart.h"
#include "mp3.h"

//��ͨˮ�� ��ťͨ��
sbit OUTPUT_42 = P4^2;

//�������Ƹ�
sbit OUTPUT_10 = P1^0; //��ʼ�� �ߵ�ƽ
sbit OUTPUT_11 = P1^1;
sbit OUTPUT_12 = P1^2;

//ˮ����ӵ��ڲ�
sbit INPUT_06 = P0^6;
sbit INPUT_15 = P1^5;

//6���Ž�
sbit INPUT_05 = P0^5;
sbit INPUT_04 = P0^4;
sbit INPUT_03 = P0^3;
sbit INPUT_02 = P0^2;
sbit INPUT_01 = P0^1;
sbit INPUT_00 = P0^0;

//�������ش�������
sbit INPUT_P23 = P2^3;

//6����ť
sbit INPUT_14 = P1^4;
sbit INPUT_13 = P1^3;
sbit INPUT_07 = P0^7;

sbit INPUT_24 = P2^4;
sbit INPUT_25 = P2^5;
sbit INPUT_26 = P2^6;

//��������
sbit OUTPUT_16 = P1^6;
sbit INPUT_17 = P1^7;

//��ǰ�Ĳ��� û�в���� = 0
unsigned char step = 0;

unsigned char step_1_flag_1 = 0;
unsigned char step_1_flag_2 = 0;
unsigned char step_1_flag_3 = 0;
unsigned char step_1_flag_4 = 0;
unsigned char step_1_flag_5 = 0;
unsigned char step_1_flag_6 = 0;

int btnStep = 0;//��Ұ����ڼ���

//�� ���� ���� ���� è ���
unsigned char code btnStep_0[6] = {1,3,1,4,5,2};
unsigned char code btnStep_1[6] = {1,6,2,5,3,4};
unsigned char code btnStep_2[6] = {4,6,2,5,2,3};
unsigned char code btnStep_3[6] = {5,2,3,4,5,3};

unsigned char playStep_0[6] = {0,0,0,0,0,0};
unsigned char playStep_1[6] = {0,0,0,0,0,0};
unsigned char playStep_2[6] = {0,0,0,0,0,0};
unsigned char playStep_3[6] = {0,0,0,0,0,0};

int i = 0;

int PLAY_6_BTN(char count);
void INIT_COM();


void main()
{
	sys_init();
	INIT_COM();
	uart_init();
	mp3_init();

	//�����ӳ� �ű�������
	delay_ms(1000);
	play_mp3(0,0x01);

	while(1)
	{	
		if(INPUT_17 == 0)
		{
			delay_ms(50);
			if(INPUT_17 == 0)
			{
				delay_ms(50);
				//�ر�����
				mp3(0x02);
				INPUT_17 = 1;
			}
		}
		if(step == 0)
		{
			if((INPUT_06 == 0) && (INPUT_15 == 0))	//ˮ�ܽ�ͨ
			{
				delay_ms(50);
				if((INPUT_06 == 0) && (INPUT_15 == 0))	//ˮ�ܽ�ͨ
				{
					OUTPUT_12 = 1;  //�������
					delay_ms(100);
			  		play_mp3(0,0x02);
					step = 1;		
				}
			}	
		}	
		else if(step == 1)	 
		{		
			delay_ms(50);			  
			if((INPUT_05 == 0) && (step_1_flag_1 == 0))
			{
				delay_ms(50);
				if(INPUT_05==0)
				{
					step_1_flag_1 = 1;
					play_mp3(0,0x04);
				}
			}
			if( (INPUT_04 == 0) && (step_1_flag_2 == 0))
			{
			 	delay_ms(50);
				 if(INPUT_04 == 0)
				{
					step_1_flag_2 = 1;
					play_mp3(0,0x05);
				}
			}
			if( (INPUT_03 == 0)	&& (step_1_flag_3 == 0))
			{
			 	delay_ms(50);	
				if(INPUT_03 == 0)	
				{	
					step_1_flag_3 = 1;
					play_mp3(0,0x03);
				}
			}
			if( (INPUT_02 == 0) && (step_1_flag_4 == 0))
			{
			 	delay_ms(50);
				if(INPUT_02 == 0)	
				{
					step_1_flag_4 = 1;
					play_mp3(0,0x07);
				}
			}
			if((INPUT_01 == 0)&&(step_1_flag_5 == 0))
			{
			 	delay_ms(50);
				if(INPUT_01 == 0)
				{
					step_1_flag_5 = 1;			   
					play_mp3(0,0x06);
				}
			}								 
			if( (INPUT_00 == 0)	&& (step_1_flag_6 == 0))
			{
				delay_ms(50);
				if(INPUT_00 == 0)
				{	
					step_1_flag_6 = 1;
					play_mp3(0,0x08);
				}
			}
			if((step_1_flag_1==1)&&(step_1_flag_2 == 1)&&(step_1_flag_3 == 1)&&(step_1_flag_4==1)&&(step_1_flag_5==1)&&(step_1_flag_6==1))
			{		
				OUTPUT_42 = 0;								
				//ȫ���ڶ�
				send(0X7E);//ָ�ʼλ
				send(0x04);
 				send(0X41);//ָ���ļ��в���
  				send(0x00);//��λ������Ϊָ�����ļ���
   				send(0x09);//���ŵ�music����Ƶ�ļ�
				send(0XEF);//ָ�����λ
				delay_ms(19000);	
				OUTPUT_42 = 1;
				step = 2;  //6���Ž��Ŷ���	
			}
		}
		else if(step==2)  //��6����ť
		{
			delay_ms(50);
			
				if(INPUT_14 == 0)
				{
					delay_ms(50);
					if(INPUT_14 == 0)
					{
						while(INPUT_14==0); //�ɿ�
						playStep_0[btnStep] = 6;
						btnStep++;
					}
				}	
				else if(INPUT_13 == 0)
				{
					delay_ms(50);
					if(INPUT_13 == 0)
					{
						while(INPUT_13==0); //�ɿ� 
						playStep_0[btnStep] =  5;
				   		btnStep++;
					}
				}	
				else if(INPUT_07 == 0)
				{
					delay_ms(50);
					if(INPUT_07 == 0)
					{
						while(INPUT_07==0); //�ɿ� 
						playStep_0[btnStep] =  4;
					   	btnStep++;
					}
				}
				else if(INPUT_24 == 0)
				{
					delay_ms(50);
					if(INPUT_24 == 0)
					{
						while(INPUT_24==0); //�ɿ�
						playStep_0[btnStep] =  1;			
					   	btnStep++;
					}
				}
				else if(INPUT_25 == 0)
				{
					delay_ms(50);
					if(INPUT_25 == 0)
					{
						while(INPUT_25 == 0); //�ɿ� 			
						playStep_0[btnStep] = 2;			
						btnStep++;
					}
				}
				else if(INPUT_26 == 0)
				{
					delay_ms(50);
					if(INPUT_26 == 0)
					{
						while(INPUT_26 == 0); //�ɿ� 
						playStep_0[btnStep] = 3;			
						btnStep ++;
					}
				}

			if(btnStep == 6)
			{
				for( i = 0 ; i < 6 ; i++)	
				{
					if(playStep_0[i] != btnStep_0[i])
					{
						//����
						OUTPUT_42 = 0;
						play_mp3(0,0x0d);
						delay_ms(24000);
						OUTPUT_42 = 1;
						btnStep = 0;
						playStep_0[0] = 0;
						playStep_0[1] = 0;
						playStep_0[2] = 0;
						playStep_0[3] = 0;
						playStep_0[4] = 0;
						playStep_0[5] = 0;
						break; 
					}
				}
				if(i == 6) 
				{
					OUTPUT_42 = 0;
					play_mp3(0,0x0a);
					delay_ms(12000);
					OUTPUT_42 = 1;
					step = 3;	
				}
				btnStep = 0;
			}
		}

		else if(step == 3)
		{
				delay_ms(50);
			
				if(INPUT_14 == 0)
				{
					delay_ms(50);
					if(INPUT_14 == 0)
					{
						while(INPUT_14==0); //�ɿ�
						playStep_1[btnStep] = 6;
						btnStep++;
					}
				}	
				else if(INPUT_13 == 0)
				{
					delay_ms(50);
					if(INPUT_13 == 0)
					{
						while(INPUT_13==0); //�ɿ� 
						playStep_1[btnStep] =  5;
				   		btnStep++;
					}
				}	
				else if(INPUT_07 == 0)
				{
					delay_ms(50);
					if(INPUT_07 == 0)
					{
						while(INPUT_07==0); //�ɿ� 
						playStep_1[btnStep] =  4;
					   	btnStep++;
					}
				}
				else if(INPUT_24 == 0)
				{
					delay_ms(50);
					if(INPUT_24 == 0)
					{
						while(INPUT_24==0); //�ɿ�
						playStep_1[btnStep] =  1;			
					   	btnStep++;
					}
				}
				else if(INPUT_25 == 0)
				{
					delay_ms(50);
					if(INPUT_25 == 0)
					{
						while(INPUT_25 == 0); //�ɿ� 			
						playStep_1[btnStep] = 2;			
						btnStep++;
					}
				}
				else if(INPUT_26 == 0)
				{
					delay_ms(50);
					if(INPUT_26 == 0)
					{
						while(INPUT_26 == 0); //�ɿ� 
						playStep_1[btnStep] = 3;			
						btnStep ++;
					}
				}

			if(btnStep == 6)
			{
				for( i = 0 ; i < 6 ; i++)	
				{
					if(playStep_1[i] != btnStep_1[i])
					{
						//����
						OUTPUT_42 = 0;
						play_mp3(0,0x0e);
						delay_ms(18000);
						OUTPUT_42 = 1;
						btnStep = 0;
						playStep_1[0] = 0;
						playStep_1[1] = 0;
						playStep_1[2] = 0;
						playStep_1[3] = 0;
						playStep_1[4] = 0;
						playStep_1[5] = 0;
						break; 
					}
				}
				if(i == 6) 
				{
					OUTPUT_42 = 0;
					play_mp3(0,0x0b);
					delay_ms(15000);
					OUTPUT_42 = 1;
					step = 4;	
				}
				btnStep = 0;
			}
		}

		else if(step == 4)
		{
				delay_ms(50);
			
				if(INPUT_14 == 0)
				{
					delay_ms(50);
					if(INPUT_14 == 0)
					{
						while(INPUT_14==0); //�ɿ�
						playStep_2[btnStep] = 6;
						btnStep++;
					}
				}	
				else if(INPUT_13 == 0)
				{
					delay_ms(50);
					if(INPUT_13 == 0)
					{
						while(INPUT_13==0); //�ɿ� 
						playStep_2[btnStep] =  5;
				   		btnStep++;
					}
				}	
				else if(INPUT_07 == 0)
				{
					delay_ms(50);
					if(INPUT_07 == 0)
					{
						while(INPUT_07==0); //�ɿ� 
						playStep_2[btnStep] =  4;
					   	btnStep++;
					}
				}
				else if(INPUT_24 == 0)
				{
					delay_ms(50);
					if(INPUT_24 == 0)
					{
						while(INPUT_24==0); //�ɿ�
						playStep_2[btnStep] =  1;			
					   	btnStep++;
					}
				}
				else if(INPUT_25 == 0)
				{
					delay_ms(50);
					if(INPUT_25 == 0)
					{
						while(INPUT_25 == 0); //�ɿ� 			
						playStep_2[btnStep] = 2;			
						btnStep++;
					}
				}
				else if(INPUT_26 == 0)
				{
					delay_ms(50);
					if(INPUT_26 == 0)
					{
						while(INPUT_26 == 0); //�ɿ� 
						playStep_2[btnStep] = 3;			
						btnStep ++;
					}
				}

			if(btnStep == 6)
			{
				for( i = 0 ; i < 6 ; i++)	
				{
					if(playStep_2[i] != btnStep_2[i])
					{
						//����
						OUTPUT_42 = 0;
						play_mp3(0,0x0f);
						delay_ms(21000);
						OUTPUT_42 = 1;
						btnStep = 0;
						playStep_2[0] = 0;
						playStep_2[1] = 0;
						playStep_2[2] = 0;
						playStep_2[3] = 0;
						playStep_2[4] = 0;
						playStep_2[5] = 0;
						break; 
					}
				}
				if(i == 6) 
				{
					OUTPUT_42 = 0;
					play_mp3(0,0x0c);
					delay_ms(15000);
					OUTPUT_42 = 1;
					step = 5;	
				}
				btnStep = 0;
			}
		}
		else if(step == 5)
		{
				delay_ms(50);
			
				if(INPUT_14 == 0)
				{
					delay_ms(50);
					if(INPUT_14 == 0)
					{
						while(INPUT_14==0); //�ɿ�
						playStep_3[btnStep] = 6;
						btnStep++;
					}
				}	
				else if(INPUT_13 == 0)
				{
					delay_ms(50);
					if(INPUT_13 == 0)
					{
						while(INPUT_13==0); //�ɿ� 
						playStep_3[btnStep] =  5;
				   		btnStep++;
					}
				}	
				else if(INPUT_07 == 0)
				{
					delay_ms(50);
					if(INPUT_07 == 0)
					{
						while(INPUT_07==0); //�ɿ� 
						playStep_3[btnStep] =  4;
					   	btnStep++;
					}
				}
				else if(INPUT_24 == 0)
				{
					delay_ms(50);
					if(INPUT_24 == 0)
					{
						while(INPUT_24==0); //�ɿ�
						playStep_3[btnStep] =  1;			
					   	btnStep++;
					}
				}
				else if(INPUT_25 == 0)
				{
					delay_ms(50);
					if(INPUT_25 == 0)
					{
						while(INPUT_25 == 0); //�ɿ� 			
						playStep_3[btnStep] = 2;			
						btnStep++;
					}
				}
				else if(INPUT_26 == 0)
				{
					delay_ms(50);
					if(INPUT_26 == 0)
					{
						while(INPUT_26 == 0); //�ɿ� 
						playStep_3[btnStep] = 3;			
						btnStep ++;
					}
				}

			if(btnStep == 6)
			{
				for( i = 0 ; i < 6 ; i++)	
				{
					if(playStep_3[i] != btnStep_3[i])
					{
						//����
						OUTPUT_42 = 0;
						play_mp3(0,0x10);
						delay_ms(21000);
						OUTPUT_42 = 1;
						btnStep = 0;
						playStep_3[0] = 0;
						playStep_3[1] = 0;
						playStep_3[2] = 0;
						playStep_3[3] = 0;
						playStep_3[4] = 0;
						playStep_3[5] = 0;
						break; 
					}
				}
				if(i == 6) 
				{
					OUTPUT_42 = 0; //�رհ�ť��

					OUTPUT_10 = 1;	 //���Ƹ�
					delay_ms(5000);
					play_mp3(0,0x11); //ȫ����ȷ + �Ա�����ʾ

					step = 6;
				}
				btnStep = 0;
			}
		}

		else if(step == 6)
		{
			if(INPUT_P23 == 0)
			{
				delay_ms(50);
				if(INPUT_P23 == 0)
				{
					step = 7;
					OUTPUT_11 = 1; //���Ƹ�
					delay_ms(2000);
					//��Ϸ����P1.6��͵�ƽ������018
					OUTPUT_16 = 0;
					play_mp3(0,0x12);		  //�Ա���ȫ����ȷ + �������� + ��������ʾ
				}
			} 
		}
	}
}



//��ʼ�����п�
void INIT_COM()
{
	INPUT_06 = 1;
	INPUT_15 = 1;

	//�Ƹ�
	OUTPUT_10 = 0;
	OUTPUT_11 = 0;
	OUTPUT_12 = 0;

	//��ͨˮ�� ��ťͨ��
	OUTPUT_42 = 0;

	//6���Ž� Ĭ���Ž���
	INPUT_05 = 1;
	INPUT_04 = 1;
	INPUT_03 = 1;
	INPUT_02 = 1;
	INPUT_01 = 1;
	INPUT_00 = 1;

	//6����ť
	INPUT_14 = 1;
	INPUT_13 = 1;
	INPUT_07 = 1;
	INPUT_26 = 1;
	INPUT_24 = 1;
	INPUT_25 = 1;
	
	//�������� 
	INPUT_P23 = 1;
			
	//��������
	OUTPUT_16 = 1;
	INPUT_17 = 1;
}