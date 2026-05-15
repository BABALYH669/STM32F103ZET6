#include "./BSP/WWDG/wwdg.h"
#include "./BSP/LED/led.h"

WWDG_HandleTypeDef g_wwdg_handle;

void wwdg_init(uint8_t tr,uint8_t wr,uint32_t fprer)
{
    g_wwdg_handle.Instance = WWDG;
    g_wwdg_handle.Init.Counter = tr;
    g_wwdg_handle.Init.Window = wr;
    g_wwdg_handle.Init.Prescaler = fprer;
    g_wwdg_handle.Init.EWIMode = WWDG_EWI_ENABLE;
    HAL_WWDG_Init(&g_wwdg_handle);
}

void HAL_WWDG_MspInit(WWDG_HandleTypeDef *huart)
{
    __HAL_RCC_WWDG_CLK_ENABLE();

    HAL_NVIC_SetPriority(WWDG_IRQn,2,3);
    HAL_NVIC_EnableIRQ(WWDG_IRQn);
}
void WWDG_IRQHandler(void)
{
    HAL_WWDG_IRQHandler(&g_wwdg_handle);
}

void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *huart)
{
    HAL_WWDG_Refresh(&g_wwdg_handle);
    LED1_TOGGLE();
}

