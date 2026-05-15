#ifndef __GTIM_H
#define __GTIM_H
#include "./SYSTEM/SYS/sys.h"
void gtim_timx_cnt_chy_init(uint16_t psc);
extern TIM_HandleTypeDef g_tim_cnt_chy_handle;
#endif
