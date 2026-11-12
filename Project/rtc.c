#include "rtc.h"

//bit flag_rtc = 0;

//void RTC_Isr(void)	interrupt RTC_VECTOR
//{
//	
//}


/**
* @brief RTC初始化：启动32.768K时钟源、写入初始时间、启动RTC走时
* @note 初始时间在这里改，第一次上电会按这个时间开始走
*/
void RTC_Init(void)
{
	X32KCR = 0xc0;				//启动外部 32K 晶振
	while(!(X32KCR & 0x01));	//等待时钟稳定
	RTCCFG &= ~0X02;			//选择外部 32K 作为 RTC 时钟源
	
	//写入初始时间：手动授时。可以升级成网络授时、卫星授时（GPS/北斗），涉及通信协议。
	INIYEAR   = 0;				// 年
    INIMONTH  = 0;				// 月            
    INIDAY    = 0;				// 日             
    INIHOUR   = 19;				// 时            
    INIMIN    = 25;   			// 分          
    INISEC    = 10;   			// 秒          
    INISSEC   = 0;  			// 1/128s           
	
	RTCIF = 0x00;				//清除RTC中断标志
	RTCIEN = 0x00;				//关闭RTC所有中断
	
	//启动RTC并装载初始值
	RTCCR = 0x01;				//RTC开始计数
	RTCCFG |= 0x01;				//把INI寄存器的值装进计数器
	while(RTCCFG & 0x01);		//等硬件装载完成（会自动清零）
}

/**
* @brief 读RTC的时、分、秒
* @note 主循环里每秒调用一次
*/
void RTC_ReadTime(void)
{
	hour = RTCHOUR;				//读时
	minute = RTCMIN;			//读分
    second = RTCSEC;			//读秒
}
