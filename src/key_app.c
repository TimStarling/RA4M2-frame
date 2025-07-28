#include "bsp_system.h"
extern system_parameter sp;
uint8_t key_val = 0;  // 当前按键状态
uint8_t key_old = 0;  // 前一按键状态
uint8_t key_down = 0; // 按下的按键
uint8_t key_up = 0;   // 释放的按键

uint32_t Key_Scan(bsp_io_port_pin_t key)
 {
	bsp_io_level_t state;
 //读取按键引脚电平
	R_IOPORT_PinRead(&g_ioport_ctrl,key,&state);
	if (BSP_IO_LEVEL_HIGH == state)
	{
		return 0;//按键没有被按下
	}
	 else
	{
		do //等待按键释放
		{
			R_IOPORT_PinRead(&g_ioport_ctrl,key,&state);
		}while (BSP_IO_LEVEL_LOW== state);
	 }
	 return 1; //按键被按下了
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
	按键检测函数
	K2 K3 K4按键按下对应的数值刷新为 
	如：K2按下时key_up为2 其他时刻为0 
		K2弹起时key_down为2 其他时刻为0 
		K2长按时key_old为2 其他时刻为0 
*/
void key_proc()
{
	// 读取当前按键状态
    key_val = key_read();
  // 计算按下的按键（当前按下状态与前一状态异或，并与当前状态相与）
    key_down = key_val & (key_old ^ key_val);
  // 计算释放的按键（当前未按下状态与前一状态异或，并与前一状态相与）
    key_up = ~key_val & (key_old ^ key_val);
  // 更新前一按键状态
    key_old = key_val;
	
	switch(key_down){
		case 2:
			/*功能：K2按下时 sp.system_mode加一 最多到2*/
			if(++sp.system_mode==2)sp.system_mode=0;
			break;
		case 3:

			break;
		case 4:

			break;

		
	}
  
}