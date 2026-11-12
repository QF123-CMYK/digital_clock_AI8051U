#include "config.h"

void SYS_Init(void)
{
	EAXFR = 1;			// 允许访问扩展的特殊寄存器，ENABLE XFR
	WTST = 0;			// 设置取程序代码等待时间，WAIT SPEED TIME
						// 赋值为0表示不等待，程序以最快速度访问。
	CKCON = 0;			// 设置访问片内的xdata速度，CKCON：Clock Control，时钟控制寄存器
						// 赋值为0表示用最快速度访问。
	
	usb_init();			// USB初始化
	
	LED_Port_Init();	// LED灯初始化
	BEEP_Port_Init();	// 蜂鸣器初始化
	Timer0_Init();		// 定时器0初始化
	SMG_Init();			// 数码管初始化
		
	EA = 1;				// 打开总中断
}

void main(void)
{
	SYS_Init();			// 初始化
	
	while(1)
	{
		SMG_Update();	//更新显示缓存
	}
}
