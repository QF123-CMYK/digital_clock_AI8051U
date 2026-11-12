#include "led.h"

void LED_Port_Init(void)
{
	P0M0 = 0x00; P0M1 = 0x00; 		//P0准双向口
	P4M1 &= ~0x01; P4M0 |= 0x01;	//P40推挽输出

	P40 = 0;	//开启LED灯电源
	P0 = 0XFF;	//LED灯默认全灭
}
