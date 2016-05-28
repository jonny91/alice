#include <STC12C5A60S2.H>
#include <common.h>
#include "uart.h"
#include "mp3.h"

sbit p02 = P0^2;
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

sbit p20 = P2^0;
sbit p40 = P4^0;
sbit p42 = P4^2;
sbit p44 = P4^4;
sbit p27 = P2^7;

void main()
{
	sys_init();
//	INIT_COM();

	uart_init();
	mp3_init();

		play_mp3(0,1);
	while(1)
	{
		p05 = 1;
	}
}