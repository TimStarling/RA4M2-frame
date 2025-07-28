#include "tim_app.h"
int timer_500ms = 0;
extern uint8_t ucLed[3];
/*��ʱ����ʼ������-1ms��ʱ��*/
void GPT_Timing_Init(void)
{
	/*��ʼ��GPT0ģ��*/
	R_GPT_Open(&g_timer0_ctrl, &g_timer0_cfg);
	/*����GPT0��ʱ��*/
	R_GPT_Start(&g_timer0_ctrl);
}

/*GPT�жϻص�����-1ms��ʱ��*/
void gpt0_callback(timer_callback_args_t* p_args)
{
	/*��ʱ������¼�*/
	if(TIMER_EVENT_CYCLE_END== p_args->event)
	{
		/*D6��1s������˸*/
		if(++timer_500ms==500){
			ucLed[2] = !ucLed[2];
			timer_500ms=0;
		}
		
	}
}

/*
	���ܣ�����PWMռ�ձ�
	ռ�ձȷ�Χ��0-100 
*/
void GPT_PWM_SetDuty(uint8_t duty)
{
   timer_info_t info;
   uint32_t current_period_counts;
   uint32_t duty_cycle_counts;
   if (duty > 100)
   duty = 100; //����ռ�ձȷ�Χ��0-100
   duty = 100 - duty;
   R_GPT_InfoGet(&g_timer5_ctrl, &info);
   current_period_counts = info.period_counts;
   duty_cycle_counts = (uint32_t)(((uint64_t) current_period_counts *duty) / 100);
   R_GPT_DutyCycleSet(&g_timer5_ctrl, duty_cycle_counts, GPT_IO_PIN_GTIOCB);
}

/*
	���ܣ�����PWMƵ�� 
	��λ��Hz
*/
void GPT_PWM_SetPeriod(uint32_t period)
{
	uint32_t set_data = 6000000/period;//6MHz��GPT�ϵ�ʱ�ӷ�Ƶ����
	fsp_err_t err = R_GPT_PeriodSet(&g_timer5_ctrl, set_data);
    assert(FSP_SUCCESS == err);
    R_BSP_SoftwareDelay (20, BSP_DELAY_UNITS_MILLISECONDS);//��ʱ ��֤���óɹ�
}

//P100Ĭ�����1kHZ ռ�ձ�Ϊ50%�ķ���
void GPT_PWM_Init(void)
{
    // ��ʼ�� GPT ģ�� 
    R_GPT_Open(&g_timer5_ctrl, &g_timer5_cfg);
    // ���� GPT ��ʱ�� 
    R_GPT_Start(&g_timer5_ctrl);
   
    //��������Ƶ��Ϊ2.5kHZ
	//GPT_PWM_SetPeriod(2500);
	// ��������ռ�ձ�Ϊ 80%  ע��������Ƶ�� ������ռ�ձ�
	//GPT_PWM_SetDuty(80);
}

