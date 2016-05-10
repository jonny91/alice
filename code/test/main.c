#include <STC12C5A60S2.H>
#include <common.h>
#include "uart.h"
#include "mp3.h"

sbit p05 = P0^5;
sbit p06 = P0^6;
sbit p07 = P0^7;
   
sbit p10 = P1 ^ 0;
sbit p11 = P1^ 1;
sbit p12 = P1^ 2;
sbit p13 = P1^ 3;
sbit p14 = P1^ 4;
sbit p15 = P1^ 5;
sbit p16 = P1^ 6;
sbit p17 = P1^ 7;

sbit p42 = P4^2;
sbit p44 = P4^4;


void main()
{
	sys_init();
	p05 = 0;	    //button

	p10 = 1;
	p11 = 0;
	p12 = 0;
	p13 = 0;						
	p16 = 0;
	p14 = 0;

	p44 = 0;	p15 = 0;
	p17 = 0;															   																

	p42 = 1;   
 	p07 = 1;

	while(1)
	{
		if(p05 == 1)
		{
			delay_ms(50);
			if(p05 == 1)
			{
			//	p10 = 0;
			}	
		}  
	}
}