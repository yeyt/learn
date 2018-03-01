#ifndef __TASK_DEFINE_H
#define __TASK_DEFINE_H
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

//任务优先级
#define LED0_TASK_PRIO		2
//任务堆栈大小	
#define LED0_STK_SIZE 		50  
//任务句柄
TaskHandle_t LED0Task_Handler;
//任务函数
void led0_task(void *pvParameters);

//任务优先级
#define LCD_TASK_PRIO		3
//任务堆栈大小	
#define LCD_STK_SIZE 		50  
//任务句柄
TaskHandle_t LCDTask_Handler;
//任务函数
void lcd_task(void *pvParameters);

//任务优先级
#define UART_TASK_PRIO		4
//任务堆栈大小	
#define UART_STK_SIZE 		200  
//任务句柄
TaskHandle_t UARTTask_Handler;
//任务函数
void uart_task(void *pvParameters);

//二值信号量句柄 
SemaphoreHandle_t BinarySemaphore; //二值信号量句柄 


#endif

