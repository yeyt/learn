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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʱ��ʼ�� 
	uart_init(115200);	//���ڳ�ʼ��������Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�  
	LED_CMD();
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);         //�򴮿�1��������
				if(t <= (strlen(USART_RX_BUF)-1))
				{
					cmd_str[t]=USART_RX_BUF[t];
				}
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			}
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
			match_cmd(cmd_str);
		}else
		{
			times++;
			if(times%5000==0)
			{
				printf("\r\n���������ʵ��\r\n");
				printf("yeyt\r\n\r\n\r\n");
			}
			if(times%200==0)printf("����������,�Իس�������\r\n");  
			delay_ms(10);   
		}
			
	}
}

