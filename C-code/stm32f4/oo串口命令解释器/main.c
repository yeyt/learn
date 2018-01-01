#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "cmd.h"

int main(void)
{ 
 
	u8 t;
	u8 len;	
	u16 times=0;  
	char cmd_str[31]=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	uart_init(115200);	//串口初始化波特率为115200
	LED_Init();		  		//初始化与LED连接的硬件接口  
	LED_CMD();
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);         //向串口1发送数据
				if(t <= (strlen(USART_RX_BUF)-1))
				{
					cmd_str[t]=USART_RX_BUF[t];
				}
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			}
			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0;
			match_cmd(cmd_str);
		}else
		{
			times++;
			if(times%5000==0)
			{
				printf("\r\n命令解释器实验\r\n");
				printf("yeyt\r\n\r\n\r\n");
			}
			if(times%200==0)printf("请输入命令,以回车键结束\r\n");  
			delay_ms(10);   
		}
			
	}
}

