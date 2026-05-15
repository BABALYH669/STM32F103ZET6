#ifndef __GTIM_H
#define __GTIM_H

#include "./SYSTEM/SYS/sys.h"
void gtim_timx_pwm_chy_init(uint16_t arr,uint16_t psc);
extern TIM_HandleTypeDef g_timx_pwm_chy_handle;
#endif
