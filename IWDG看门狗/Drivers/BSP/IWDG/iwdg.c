#include "./BSP/IWDG/iwdg.h"

IWDG_HandleTypeDef g_iwdg_handle;

uint8_t prer;
uint16_t rlr;

void iwdg_init(uint8_t prer,uint16_t rlr)
{
    g_iwdg_handle.Instance = IWDG;
    g_iwdg_handle.Init.Prescaler = prer;
    g_iwdg_handle.Init.Reload = rlr;
    HAL_IWDG_Init(&g_iwdg_handle);
}

void iwdg_feed(void)
{
    HAL_IWDG_Refresh(&g_iwdg_handle);
}
