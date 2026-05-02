#ifndef __KEYAPP_H__
#define __KEYAPP_H__

#include <stdint.h>

#define KEY2_MASK (1U << 0)
#define KEY3_MASK (1U << 1)
#define KEY4_MASK (1U << 2)

extern uint8_t key_val;
extern uint8_t key_old;
extern uint8_t key_down;
extern uint8_t key_up;

void key_proc(void);

#endif
