#include "bsp_system.h"
static uint32_t IT_period;//�ж����ڱ���
static uint32_t uwTick = 0;

void systick_init(uint32_t IT_freqency){//�жϳ�ʼ��
	IT_period = SystemCoreClock / IT_freqency;
	SysTick_Config(IT_period);
}

/**
 * @brief SysTick ���жϷ�����
* @param ��
* @retval ��
*/
extern void SysTick_Handler(void); //��Ҫ�� extern ����һ�±������������
void SysTick_Handler(void) {
    uwTick++;
}

uint32_t GetTickCount(void) {
    return uwTick;
}

uint16_t tast_num;
typedef struct{
	void (*task_func)(void);
	uint32_t rate_ms;
	uint32_t lats_run;
} task_t;

static task_t scheduler[]={
	{led_proc,100,0},
	{key_proc,100,0},
	{uart_proc,250,0},
	{uart_print,2000,0}
};

void scheduler_init()
{
	tast_num = sizeof(scheduler)/ sizeof(task_t);
}

void scheduler_run()
{
	for(uint16_t i=0;i<tast_num;i++)
	{
		uint32_t now_time=GetTickCount();
		if(now_time>=scheduler[i].lats_run + scheduler[i].rate_ms){
			scheduler[i].lats_run=now_time;
			scheduler[i].task_func();
		}
	
	}
}