#include "timer.h"

bit flag_Timer0 = 0;		//定时器0标志位

uint16_t count_500ms = 0;

void Timer0_Isr(void) interrupt 1
{
	flag_Timer0 = 1;
	SMG_Scan();
	count_ms++;
	
	if(count_ms >= 1000)	// 1s
	{
		count_ms = 0;
		second++;
		
		if(second >= 60)	// 1min
		{
			second = 0; minute++;
			
			if(minute >= 60)	// 1h
			{
				minute = 0; hour++;
				
				if(hour >= 24)	//24h制
				{
					hour = 0;
				}
			}
		}
	}
}

void Timer0_Init(void)		//1毫秒@40.000MHz
{
	AUXR |= 0x80;			//定时器时钟1T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0xC0;				//设置定时初始值
	TH0 = 0x63;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;				//使能定时器0中断
}
