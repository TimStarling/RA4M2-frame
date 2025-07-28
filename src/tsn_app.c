#include "tsn_app.h"
extern system_parameter sp;


//ADC ת����ɱ�־λ
volatile bool scan_complete_flag = false;
//ADC�жϻص�����
void adc_callback(adc_callback_args_t * p_args)
{
	FSP_PARAMETER_NOT_USED(p_args);
	scan_complete_flag = true;
}

/*ADC0�ڲ�ͨ���ɼ�CPU�¶�*/
double Read_temper_data(void)
{
	uint16_t adc_data0;
	double a0;
	(void)R_ADC_ScanStart(&g_adc0_ctrl);
	while (!scan_complete_flag) //�ȴ�ת����ɱ�־
	{
		;
	}
	scan_complete_flag = false; //���������־λ
	/* ��ȡͨ�� 0 ���� */
	R_ADC_Read(&g_adc0_ctrl, ADC_CHANNEL_TEMPERATURE, &adc_data0);
	/* ADCԭʼ����ת��Ϊ��ѹֵ��ADC�ο���ѹΪ3.3V��*/
	return adc_data0;
 }
/*
	���ܣ���ȡ�¶Ȳ���ӡ
	

 */
float temperature_get()
{
	float value = Read_temper_data();
	uint32_t    cal127;
	//��ȡ����У��ֵ
    adc_info_t adc_info;
    (void) R_ADC_InfoGet(&g_adc0_ctrl, &adc_info);
    cal127 = (int32_t) adc_info.calibration_data;
	//���㹫ʽ�и������ֵ�����Ұ��չ�ʽ������¶�ֵ
    float slope = 4.0f/1000;
    float v1= 3.3f * cal127 / 4096;
    float vs = 3.3f * value /4096;
    float temperature = (vs - v1) / slope + 127;
	return temperature;
	
}	