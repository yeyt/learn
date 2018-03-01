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
 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	delay_init(168);		//初始化延时函数
	uart_init(115200);     	//初始化串口
	LED_Init();		        //初始化LED端
	LCD_Init(); 
 	LCD_Clear(WHITE);
  POINT_COLOR=RED;
		//创建开始任务
  xTaskCreate((TaskFunction_t )start_task,            //任务函数
              (const char*    )"start_task",          //任务名称
              (uint16_t       )START_STK_SIZE,        //任务堆栈大小
              (void*          )NULL,                  //传递给任务函数的参数
              (UBaseType_t    )START_TASK_PRIO,       //任务优先级
              (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
  vTaskStartScheduler();          //开启任务调度
}

//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
	  //创建二值信号量 
    BinarySemaphore=xSemaphoreCreateBinary();   
    //创建LED0任务
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);
		//创建LCD任务
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
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

//LED0任务函数 
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
			err=xSemaphoreTake(BinarySemaphore,2000);	//获取信号量
			if(pdTRUE == err)
			{
				len=USART_RX_STA&0x3fff;						//得到此次接收到的数据长度
				CommandStr=pvPortMalloc(len);
				sprintf((char*)CommandStr,"%s",USART_RX_BUF);
				CommandStr[len]='\0';	
				printf("输入为：%s \r\n",CommandStr);
				if(strcmp((char*)CommandStr,"LED1ON")==0)
					printf("OKOKOKOKOKOKOK\r\n");
				vPortFree(CommandStr);
				USART_RX_STA=0;
				memset(USART_RX_BUF,0,USART_REC_LEN);			//串口接收缓冲区清零
			}
			else if(pdFALSE ==err )
			{
				printf("请输入命令\r\n");
				vTaskDelay(10);      //延时10ms，也就是10个时钟节拍	
			}
		}
	}
	
}

