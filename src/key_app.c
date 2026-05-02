#include "bsp_system.h"

extern system_parameter sp;

uint8_t key_val = 0;  // 当前按键状态位图
uint8_t key_old = 0;  // 上一次按键状态位图
uint8_t key_down = 0; // 本次按下事件位图
uint8_t key_up = 0;   // 本次抬起事件位图

#define KEY2_MASK (1U << 0)
#define KEY3_MASK (1U << 1)
#define KEY4_MASK (1U << 2)

static uint8_t Key_IsPressed(bsp_io_port_pin_t key)
{
    bsp_io_level_t state;

    // 按键低电平有效：LOW = 按下，HIGH = 松开
    R_IOPORT_PinRead(&g_ioport_ctrl, key, &state);
    return (state == BSP_IO_LEVEL_LOW) ? 1U : 0U;
}

static uint8_t key_read(void)
{
    uint8_t state = 0;

    if (Key_IsPressed(BSP_IO_PORT_01_PIN_11)) state |= KEY2_MASK;
    if (Key_IsPressed(BSP_IO_PORT_01_PIN_12)) state |= KEY3_MASK;
    if (Key_IsPressed(BSP_IO_PORT_00_PIN_13)) state |= KEY4_MASK;

    return state;
}

/*
 * 按键状态检测：
 * key_down 仅在按下边沿置位，key_up 仅在抬起边沿置位。
 * 例如 K2：
 *   按下瞬间 key_down 包含 KEY2_MASK
 *   抬起瞬间 key_up   包含 KEY2_MASK
 */
void key_proc(void)
{
    // 读取当前按键状态位图
    key_val = key_read();

    // 检测按下边沿：当前为 1，上一拍为 0
    key_down = key_val & (uint8_t)(~key_old);

    // 检测抬起边沿：当前为 0，上一拍为 1
    key_up = key_old & (uint8_t)(~key_val);

    // 保存状态用于下一次边沿检测
    key_old = key_val;

    if (key_down & KEY2_MASK)
    {
        // 功能：K2 按下时切换 system_mode（0/1）
        if (++sp.system_mode == 2) sp.system_mode = 0;
    }

    if (key_down & KEY3_MASK)
    {
        // 预留：K3 按下处理
    }

    if (key_down & KEY4_MASK)
    {
        // 预留：K4 按下处理
    }
}
