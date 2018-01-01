#ifndef __LED_H
#define __LED_H
#include "sys.h"

//LED端口定义
#define LED0 PBout(0)	// DS0	 

void LED_Init(void);//初始化	
void LED_CMD(void);//注册led命令

#endif
