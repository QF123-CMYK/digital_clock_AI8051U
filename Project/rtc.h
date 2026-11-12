#ifndef __RTC_H__
#define __RTC_H__

#include "config.h"

//extern bit flag_rtc;

void RTC_Init(void);		// RTC初始化：起振、设初始时间、启动走时
void RTC_ReadTime(void);	// 读RTC当前时分秒，刷新到全局变量hour/minute/second

#endif
