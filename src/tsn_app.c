#include "tsn_app.h"
extern system_parameter sp;


//ADC 转换完成标志位
volatile bool scan_complete_flag = false;
//ADC中断回调函数
void adc_callback(adc_callback_args_t * p_args)
{
	FSP_PARAMETER_NOT_USED(p_args);
	scan_complete_flag = true;
}

/*ADC0内部通道采集CPU温度*/
double Read_temper_data(void)
{
	uint16_t adc_data0;
	double a0;
	(void)R_ADC_ScanStart(&g_adc0_ctrl);
	while (!scan_complete_flag) //等待转换完成标志
	{
		;
	}
	scan_complete_flag = false; //重新清除标志位
	/* 读取通道 0 数据 */
	R_ADC_Read(&g_adc0_ctrl, ADC_CHANNEL_TEMPERATURE, &adc_data0);
	/* ADC原始数据转换为电压值（ADC参考电压为3.3V）*/
	return adc_data0;
 }
/*
	功能：读取温度并打印
	

 */
float temperature_get()
{
	float value = Read_temper_data();
	uint32_t    cal127;
	//获取厂方校验值
    adc_info_t adc_info;
    (void) R_ADC_InfoGet(&g_adc0_ctrl, &adc_info);
    cal127 = (int32_t) adc_info.calibration_data;
	//计算公式中各项的数值，并且按照公式计算出温度值
    float slope = 4.0f/1000;
    float v1= 3.3f * cal127 / 4096;
    float vs = 3.3f * value /4096;
    float temperature = (vs - v1) / slope + 127;
	return temperature;
	
}	