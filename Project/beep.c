#include "beep.h"

void BEEP_Port_Init(void)
{
	P5M1 &= ~0x01; P5M0 |= 0x01;//ÍÆÍìÊä³ö
	P50 = 0;					//P50ÖÃ0£¬¶Ï¿ª·äÃùÆ÷
}
