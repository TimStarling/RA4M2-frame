#include "bsp_system.h"
#include "key_app.h"

extern system_parameter sp;

uint8_t key_val = 0;  // 当前按键状态位图
uint8_t key_old = 0;  // 上一次按键状态位图
uint8_t key_down = 0; // 本次按下边沿事件
uint8_t key_up = 0;   // 本次抬起边沿事件

static uint8_t key_is_pressed(bsp_io_port_pin_t pin)
{
    bsp_io_level_t state = BSP_IO_LEVEL_HIGH;
    R_IOPORT_PinRead(&g_ioport_ctrl, pin, &state);
    return (state == BSP_IO_LEVEL_LOW) ? 1U : 0U;
}

static uint8_t key_read_state(void)
{
    uint8_t state = 0;

    if (key_is_pressed(BSP_IO_PORT_01_PIN_11)) state |= KEY2_MASK;
    if (key_is_pressed(BSP_IO_PORT_01_PIN_12)) state |= KEY3_MASK;
    if (key_is_pressed(BSP_IO_PORT_00_PIN_13)) state |= KEY4_MASK;

    return state;
}

void key_proc(void)
{
    key_val = key_read_state();

    /*
     * 边沿检测：
     * key_down: 0->1
     * key_up  : 1->0
     */
    key_down = (uint8_t)(key_val & (uint8_t)(~key_old));
    key_up = (uint8_t)(key_old & (uint8_t)(~key_val));

    key_old = key_val;

    if (key_down & KEY2_MASK)
    {
        if (++sp.system_mode >= 2)
        {
            sp.system_mode = 0;
        }
    }
}
