#include "./BSP/BTIM/btim.h"
#include "./BSP/LED/led.h"

TIM_HandleTypeDef g_timx_handle;

void btim_timx_base_init(uint16_t psc,uint16_t arr)
{
    g_timx_handle.Instance = TIM6;
    g_timx_handle.Init.Prescaler = psc;
    g_timx_handle.Init.Period = arr;
    HAL_TIM_Base_Init(&g_timx_handle);

    HAL_TIM_Base_Start_IT(&g_timx_handle);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *huart)
{
    if(huart->Instance == TIM6)
    {
        __HAL_RCC_TIM6_CLK_ENABLE();
        HAL_NVIC_SetPriority(TIM6_IRQn,1,3);
        HAL_NVIC_EnableIRQ(TIM6_IRQn);
    }
}

void TIM6_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_handle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *huart)
{
    if(huart->Instance ==TIM6)
    {
        LED0_TOGGLE();
    }
}

