#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "task_define.h"
#include "lcd.h"

int main(void)
{ 
 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	delay_init(168);		//��ʼ����ʱ����
	uart_init(115200);     	//��ʼ������
	LED_Init();		        //��ʼ��LED��
	LCD_Init(); 
 	LCD_Clear(WHITE);
  POINT_COLOR=RED;
		//������ʼ����
  xTaskCreate((TaskFunction_t )start_task,            //������
              (const char*    )"start_task",          //��������
              (uint16_t       )START_STK_SIZE,        //�����ջ��С
              (void*          )NULL,                  //���ݸ��������Ĳ���
              (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
              (TaskHandle_t*  )&StartTask_Handler);   //������              
  vTaskStartScheduler();          //�����������
}

//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
	  //������ֵ�ź��� 
    BinarySemaphore=xSemaphoreCreateBinary();   
    //����LED0����
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);
		//����LCD����
		xTaskCreate((TaskFunction_t)lcd_task,
								(const char *   )"lcd_task",
								(uint16_t       )LCD_STK_SIZE,
								(void *         )NULL,
								(UBaseType_t    )LCD_TASK_PRIO,
								(TaskHandle_t   )&LCDTask_Handler);
		xTaskCreate((TaskFunction_t)uart_task,
								(const char *   )"uart_task",
								(uint16_t       )UART_STK_SIZE,
								(void *         )NULL,
								(UBaseType_t    )UART_TASK_PRIO,
								(TaskHandle_t   )&UARTTask_Handler);
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

//LED0������ 
void led0_task(void *pvParameters)
{
    while(1)
    {
        LED0=~LED0;
        vTaskDelay(500);
    }
}  

void lcd_task(void *pvParameters)
{
	while(1)
	{
		LCD_ShowString(10,10,240,24,24,"hello freertos,stm32f4");
		LCD_Draw_Circle(100,80,50);
		vTaskDelay(500);
	}
}

void uart_task(void *pvParameters)
{
	size_t len=0;
	BaseType_t err=pdFALSE;
	u8 *CommandStr;
	
	while(1)
	{
		if(BinarySemaphore != NULL)
		{
			err=xSemaphoreTake(BinarySemaphore,2000);	//��ȡ�ź���
			if(pdTRUE == err)
			{
				len=USART_RX_STA&0x3fff;						//�õ��˴ν��յ������ݳ���
				CommandStr=pvPortMalloc(len);
				sprintf((char*)CommandStr,"%s",USART_RX_BUF);
				CommandStr[len]='\0';	
				printf("����Ϊ��%s \r\n",CommandStr);
				if(strcmp((char*)CommandStr,"LED1ON")==0)
					printf("OKOKOKOKOKOKOK\r\n");
				vPortFree(CommandStr);
				USART_RX_STA=0;
				memset(USART_RX_BUF,0,USART_REC_LEN);			//���ڽ��ջ���������
			}
			else if(pdFALSE ==err )
			{
				printf("����������\r\n");
				vTaskDelay(10);      //��ʱ10ms��Ҳ����10��ʱ�ӽ���	
			}
		}
	}
	
}

