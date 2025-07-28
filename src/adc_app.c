#include "adc_app.h"

void ADC_Init(void)
{
	fsp_err_t err;
	err = R_ADC_Open(&g_adc0_ctrl, &g_adc0_cfg);
	
	err = R_ADC_ScanCfg(&g_adc0_ctrl, &g_adc0_channel_cfg);
	assert(FSP_SUCCESS == err);
}

extern volatile bool scan_complete_flag;

/*ADC0ͨ��1�ɼ�P000�ϵ�ѹ*/
float get_adcdata()
{
	uint16_t adc_data1;
	(void)R_ADC_ScanStart(&g_adc0_ctrl);
	while (!scan_complete_flag) //�ȴ�ת����ɱ�־
	{
		;
	}
	scan_complete_flag = false; //���������־λ
	/* ��ȡͨ�� 0 ���� */
	R_ADC_Read(&g_adc0_ctrl, ADC_CHANNEL_1, &adc_data1);
	/* ADCԭʼ����ת��Ϊ��ѹֵ��ADC�ο���ѹΪ3.3V��*/
	float a1 = adc_data1*3.3f/4095;
	return a1;
}

