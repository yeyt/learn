#include "led.h"  	 
#include "cmd.h" 

//��ʼ��PB0�����.��ʹ��ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOFʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
	GPIO_SetBits(GPIOB,GPIO_Pin_0);//GPIOF9,F10��S�øߣ�����

}

void led_high(void)
{
	printf("on\r\n");
	GPIO_SetBits(GPIOB,GPIO_Pin_0);//GPIOF9,F10��S�øߣ�����
}


void led_low(void)
{
	printf("off\r\n");
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);//GPIOF9,F10��S�øߣ�����
}

void LED_CMD(void)
{
	cmd led_cmd[] = {
	{"led_on",led_low},
	{"led_of",led_high},
	};
	
	register_cmd(led_cmd,2);
	
}

