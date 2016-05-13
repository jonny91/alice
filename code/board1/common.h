#include <STC/STC12C5A60S2.H>

#define FOSC 11059200L
#define MODE1T                      //Timer clock mode, comment this line is 12T mode, uncomment is 1T mode

#ifdef MODE1T
#define T1MS (65536-FOSC/1000)      //1ms timer calculation method in 1T mode
#else
#define T1MS (65536-FOSC/12/1000)   //1ms timer calculation method in 12T mode
#endif

#define GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));}

/*********************************************************/
/*                                                       */
/* 系统初始化函数  P1-P4设置成推挽输出                   */
/*                                                       */
/*********************************************************/	
void sys_init()
{
	P0M1=0X00;
	P0M0=0Xff;      //设置P0为推挽输出
	
	P1M1=0X00;
	P1M0=0XFF;	    //设置P1为推挽输出
	
	P2M1=0X00;
	P2M0=0XFF;		//设置P2口为推挽输出
	
	P3M1=0X00;
	P3M0=0XFC;	    //设置P3为推挽输出	P3.0 3.1 RXD TXD设置为普通IO口 防止音响的异响

	P4M1=0X00;
	P4M0=0XFF;      //设置P4为推挽输出


}

/*********************************************************/
/*                                                       */
/* 1ms延时程序                                           */
/*                                                       */
/*********************************************************/
void delay_ms(int count)  // /* X1ms */	 延时1ms程序
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<1000;j++);
} 
