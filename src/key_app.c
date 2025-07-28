#include "bsp_system.h"
extern system_parameter sp;
uint8_t key_val = 0;  // ��ǰ����״̬
uint8_t key_old = 0;  // ǰһ����״̬
uint8_t key_down = 0; // ���µİ���
uint8_t key_up = 0;   // �ͷŵİ���

uint32_t Key_Scan(bsp_io_port_pin_t key)
 {
	bsp_io_level_t state;
 //��ȡ�������ŵ�ƽ
	R_IOPORT_PinRead(&g_ioport_ctrl,key,&state);
	if (BSP_IO_LEVEL_HIGH == state)
	{
		return 0;//����û�б�����
	}
	 else
	{
		do //�ȴ������ͷ�
		{
			R_IOPORT_PinRead(&g_ioport_ctrl,key,&state);
		}while (BSP_IO_LEVEL_LOW== state);
	 }
	 return 1; //������������
}

uint8_t key_read()
{
	uint8_t temp = 0;
	if(Key_Scan(BSP_IO_PORT_01_PIN_11) == 1)temp = 2;
	if(Key_Scan(BSP_IO_PORT_01_PIN_12) == 1)temp = 3;
	if(Key_Scan(BSP_IO_PORT_00_PIN_13) == 1)temp = 4;
	return temp;
}


/*
	������⺯��
	K2 K3 K4�������¶�Ӧ����ֵˢ��Ϊ 
	�磺K2����ʱkey_upΪ2 ����ʱ��Ϊ0 
		K2����ʱkey_downΪ2 ����ʱ��Ϊ0 
		K2����ʱkey_oldΪ2 ����ʱ��Ϊ0 
*/
void key_proc()
{
	// ��ȡ��ǰ����״̬
    key_val = key_read();
  // ���㰴�µİ�������ǰ����״̬��ǰһ״̬��򣬲��뵱ǰ״̬���룩
    key_down = key_val & (key_old ^ key_val);
  // �����ͷŵİ�������ǰδ����״̬��ǰһ״̬��򣬲���ǰһ״̬���룩
    key_up = ~key_val & (key_old ^ key_val);
  // ����ǰһ����״̬
    key_old = key_val;
	
	switch(key_down){
		case 2:
			/*���ܣ�K2����ʱ sp.system_mode��һ ��ൽ2*/
			if(++sp.system_mode==2)sp.system_mode=0;
			break;
		case 3:

			break;
		case 4:

			break;

		
	}
  
}