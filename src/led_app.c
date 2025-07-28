#include "bsp_system.h"
extern system_parameter sp;
uint8_t ucLed[3] = {0,0,0};
//��ӦD2 D3 D6 ����LED
void led_disp(uint8_t *ucLed)
{
	uint8_t temp=0x00;
	static uint8_t temp_old = 0xff;
	for(int i=0;i<4;i++){
		temp |= ucLed[i]<<i;
	}
	if(temp != temp_old){
		R_IOPORT_PinWrite(&g_ioport_ctrl,BSP_IO_PORT_00_PIN_02,ucLed[0]);
		R_IOPORT_PinWrite(&g_ioport_ctrl,BSP_IO_PORT_01_PIN_03,ucLed[1]);
		R_IOPORT_PinWrite(&g_ioport_ctrl,BSP_IO_PORT_01_PIN_04,ucLed[2]);
	}
}

/*
	LEDִ�к���
	ucLed[0]=0 D2LEDϨ��
	ucLed[0]=1 D2LED����
	�Դ�����
*/
void led_proc()
{
	led_disp(ucLed);
	/*���ܣ�����ģʽ�л��ı�led��*/
	ucLed[0]=0;
	ucLed[1]=0;
	ucLed[sp.system_mode]=1;
}