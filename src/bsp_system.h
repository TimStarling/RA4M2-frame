#include "hal_data.h"
#include "stdio.h"
#include <stdlib.h>
#include "key_app.h"
#include "led_app.h"
#include "math.h"


typedef struct{
	int system_mode;//系统模式
	
	char uart_buffer[50];//串口数据储存
	
	float cpu_temper;
	float adc_data;
}system_parameter;

void scheduler_init();
void scheduler_run();
void systick_init(uint32_t IT_freqency);//中断初始化

void UART9_Init(void);
void uart_proc();
void uart_print();


void ADC_Init(void);
float get_adcdata();
float temperature_get();

void GPT_PWM_Init(void);
void GPT_Timing_Init(void);

void P015_IRQ_Init(void);

