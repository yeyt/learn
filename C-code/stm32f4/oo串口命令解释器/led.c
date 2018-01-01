#include "led.h"  	 
#include "cmd.h" 

//初始化PB0输出口.并使能时钟		    
//LED IO初始化
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOF时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	GPIO_SetBits(GPIOB,GPIO_Pin_0);//GPIOF9,F10设S置高，灯灭

}

void led_high(void)
{
	printf("on\r\n");
	GPIO_SetBits(GPIOB,GPIO_Pin_0);//GPIOF9,F10设S置高，灯灭
}


void led_low(void)
{
	printf("off\r\n");
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);//GPIOF9,F10设S置高，灯灭
}

void LED_CMD(void)
{
	cmd led_cmd[] = {
	{"led_on",led_low},
	{"led_of",led_high},
	};
	
	register_cmd(led_cmd,2);
	
}

