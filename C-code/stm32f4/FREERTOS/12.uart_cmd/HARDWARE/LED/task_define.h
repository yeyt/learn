#ifndef __TASK_DEFINE_H
#define __TASK_DEFINE_H
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//�������ȼ�
#define LED0_TASK_PRIO		2
//�����ջ��С	
#define LED0_STK_SIZE 		50  
//������
TaskHandle_t LED0Task_Handler;
//������
void led0_task(void *pvParameters);

//�������ȼ�
#define LCD_TASK_PRIO		3
//�����ջ��С	
#define LCD_STK_SIZE 		50  
//������
TaskHandle_t LCDTask_Handler;
//������
void lcd_task(void *pvParameters);

//�������ȼ�
#define UART_TASK_PRIO		4
//�����ջ��С	
#define UART_STK_SIZE 		200  
//������
TaskHandle_t UARTTask_Handler;
//������
void uart_task(void *pvParameters);

//��ֵ�ź������ 
SemaphoreHandle_t BinarySemaphore; //��ֵ�ź������ 


#endif

