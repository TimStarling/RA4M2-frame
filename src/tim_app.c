#include "tim_app.h"
int timer_500ms = 0;
extern uint8_t ucLed[3];
/*定时器初始化函数-1ms定时器*/
void GPT_Timing_Init(void)
{
	/*初始化GPT0模块*/
	R_GPT_Open(&g_timer0_ctrl, &g_timer0_cfg);
	/*启动GPT0定时器*/
	R_GPT_Start(&g_timer0_ctrl);
}

/*GPT中断回调函数-1ms定时器*/
void gpt0_callback(timer_callback_args_t* p_args)
{
	/*定时器溢出事件*/
	if(TIMER_EVENT_CYCLE_END== p_args->event)
	{
		/*D6以1s周期闪烁*/
		if(++timer_500ms==500){
			ucLed[2] = !ucLed[2];
			timer_500ms=0;
		}
		
	}
}

/*
	功能：设置PWM占空比
	占空比范围：0-100 
*/
void GPT_PWM_SetDuty(uint8_t duty)
{
   timer_info_t info;
   uint32_t current_period_counts;
   uint32_t duty_cycle_counts;
   if (duty > 100)
   duty = 100; //限制占空比范围：0-100
   duty = 100 - duty;
   R_GPT_InfoGet(&g_timer5_ctrl, &info);
   current_period_counts = info.period_counts;
   duty_cycle_counts = (uint32_t)(((uint64_t) current_period_counts *duty) / 100);
   R_GPT_DutyCycleSet(&g_timer5_ctrl, duty_cycle_counts, GPT_IO_PIN_GTIOCB);
}

/*
	功能：设置PWM频率 
	单位：Hz
*/
void GPT_PWM_SetPeriod(uint32_t period)
{
	uint32_t set_data = 6000000/period;//6MHz由GPT上的时钟分频决定
	fsp_err_t err = R_GPT_PeriodSet(&g_timer5_ctrl, set_data);
    assert(FSP_SUCCESS == err);
    R_BSP_SoftwareDelay (20, BSP_DELAY_UNITS_MILLISECONDS);//延时 保证设置成功
}

//P100默认输出1kHZ 占空比为50%的方波
void GPT_PWM_Init(void)
{
    // 初始化 GPT 模块 
    R_GPT_Open(&g_timer5_ctrl, &g_timer5_cfg);
    // 启动 GPT 定时器 
    R_GPT_Start(&g_timer5_ctrl);
   
    //重新设置频率为2.5kHZ
	//GPT_PWM_SetPeriod(2500);
	// 重新设置占空比为 80%  注：先设置频率 再设置占空比
	//GPT_PWM_SetDuty(80);
}

