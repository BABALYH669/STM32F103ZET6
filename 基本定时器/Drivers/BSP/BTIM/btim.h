#ifndef __BTIM_H
#define __BTIM_H
#include "./SYSTEM/sys/sys.h"
void btim_timx_base_init(uint16_t psc,uint16_t arr);
extern TIM_HandleTypeDef g_timx_handle;

#endif
