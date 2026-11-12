#include "smg.h"

//共阴极段码表
static uint8_t Code_Seg[] = {
    0x3F,	//“0”
	0x06,	//“1”
	0x5B, 	//“2”
	0x4F, 	//“3”
	0x66, 	//“4”
	0x6D, 	//“5”
	0x7D, 	//“6”
	0x07, 	//“7”
	0x7F, 	//“8”
	0x6F,	//“9”
	0x00,	//熄灭
	0x40	//“-”
};

//位码表
static uint8_t Code_Bit[] = {
	0x01, 	//第0位
	0x02,
	0x04,
	0x08,
	0x10,
	0x20,
	0x40,
	0x80  	//第7位
};			//从第0位开始显示

//显示缓存
uint8_t smg_buf[SMG_NUM] = {
	0,
	0,
	SMG_DASH,
	0,
	0,
	SMG_DASH,
	0,
	0
};									

uint8_t scan_idx = 0;	//扫描下标，取值0~7

uint16_t hour = 0;
uint16_t minute = 0;
uint16_t second = 0;
uint16_t count_ms = 0;		//毫秒计数器

//数码管初始化
void SMG_Init(void)
{	
	HC595_Port_Init();		//I/O口初始化
	
	HC595_SendByte(0x00);	//段码清零
	HC595_SendByte(0xff);	//位码清零	
	HC595_Latch();			//锁存输出
}

//数码管扫描,显示“00-00-00”
void SMG_Scan(void)
{
	uint8_t segdat;	//用于存放段码数据
	uint8_t bitdat;	//用于存放位选码数据
	
	//消隐
	HC595_SendByte(0x00);	//段码清零
	HC595_SendByte(0xff);	//位码清零
	HC595_Latch();			//锁存输出，全灭
	
	// 根据当前的扫描下标，查表得到段码、位选码
	segdat = Code_Seg[smg_buf[scan_idx]];
	bitdat =~ Code_Bit[scan_idx];	//共阴极
	
	//根据原理图，要先发送段码
	HC595_SendByte(segdat);	//先发送段码
	HC595_SendByte(bitdat);	//再发送位选
	HC595_Latch();			//锁存输出，点亮当前位
	
	// 轮换到下一位，为下一次调用做准备
	scan_idx++;
	if(scan_idx >= SMG_NUM) 
	{
		scan_idx = 0;
	}
}

//更新显示缓存
void SMG_Update(void)
{
	smg_buf[0] = hour / 10;
	smg_buf[1] = hour % 10;
	
	smg_buf[2] = SMG_DASH;
	
	smg_buf[3] = minute / 10;
	smg_buf[4] = minute % 10;
	
	smg_buf[5] = SMG_DASH;
	
	smg_buf[6] = second / 10;
	smg_buf[7] = second % 10;	
}
