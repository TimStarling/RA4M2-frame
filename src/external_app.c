#include "external_app.h"

void P015_IRQ_Init(void)
{
	fsp_err_t err = FSP_SUCCESS;
	/* Open ICU module */
	err = R_ICU_ExternalIrqOpen(&g_external_irq0_ctrl, &g_external_irq0_cfg);
	/* �����ж� */
	err = R_ICU_ExternalIrqEnable(&g_external_irq0_ctrl);
}


//P015��ƽ̧��ʱ�����ж�
void P015_interrupt (external_irq_callback_args_t * p_args)
{
     /*�ж��ж�ͨ��*/
	if (13 == p_args->channel)
	{
		printf("P015 interrupt!\r\n");
	}
}