#include "adc_app.h"

void ADC_Init(void)
{
	fsp_err_t err;
	err = R_ADC_Open(&g_adc0_ctrl, &g_adc0_cfg);
	
	err = R_ADC_ScanCfg(&g_adc0_ctrl, &g_adc0_channel_cfg);
	assert(FSP_SUCCESS == err);
}

extern volatile bool scan_complete_flag;

/*ADC0通道1采集P000上电压*/
float get_adcdata()
{
	uint16_t adc_data1;
	(void)R_ADC_ScanStart(&g_adc0_ctrl);
	while (!scan_complete_flag) //等待转换完成标志
	{
		;
	}
	scan_complete_flag = false; //重新清除标志位
	/* 读取通道 0 数据 */
	R_ADC_Read(&g_adc0_ctrl, ADC_CHANNEL_1, &adc_data1);
	/* ADC原始数据转换为电压值（ADC参考电压为3.3V）*/
	float a1 = adc_data1*3.3f/4095;
	return a1;
}

