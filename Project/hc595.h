#ifndef __HC595_H__
#define __HC595_H__

#include "config.h"

void HC595_Port_Init(void);
void HC595_SendByte(uint8_t dat);
void HC595_Latch(void);

#endif
