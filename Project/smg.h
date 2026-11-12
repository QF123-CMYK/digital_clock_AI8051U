#ifndef __SMG_H__
#define __SMG_H__

#include "config.h"

#define		SMG_NUM 	8		//数码管的数量
#define		SMG_BLACK 	10		//熄灭
#define		SMG_DASH 	11		//短横“-”

extern uint8_t scan_idx;
extern uint8_t smg_buf[SMG_NUM];
extern uint16_t hour;
extern uint16_t minute;
extern uint16_t second;
extern uint16_t count_ms;		

//外部接口
void SMG_Init(void);
void SMG_Scan(void);
void SMG_Update(void);

#endif
