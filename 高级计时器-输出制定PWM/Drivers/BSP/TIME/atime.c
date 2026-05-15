#include "./BSP/TIME/atime.h"

TIM_HandleTypeDef g_timx_npwm_chy_handle;
static uint8_t g_npwm_remain = 0;

void atim_timx_npwm_chy_init(uint16_t arr,uint16_t psc)
{
    TIM_OC_InitTypeDef timx_oc_npwm_chy = {0};

    g_timx_npwm_chy_handle.Instance = TIM8;
    g_timx_npwm_chy_handle.Init.Prescaler = psc;
    g_timx_npwm_chy_handle.Init.Period = arr;
    g_timx_npwm_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    g_timx_npwm_chy_handle.Init.RepetitionCounter = 0;
    HAL_TIM_PWM_Init(&g_timx_npwm_chy_handle);

    timx_oc_npwm_chy.OCMode = TIM_OCMODE_PWM1;
    timx_oc_npwm_chy.Pulse = arr/2;
    timx_oc_npwm_chy.OCPolarity = TIM_OCPOLARITY_HIGH;
    HAL_TIM_PWM_ConfigChannel(&g_timx_npwm_chy_handle,&timx_oc_npwm_chy,TIM_CHANNEL_1);
    __HAL_TIM_ENABLE_IT(&g_timx_npwm_chy_handle,TIM_IT_UPDATE);
    HAL_TIM_PWM_Start(&g_timx_npwm_chy_handle,TIM_CHANNEL_1);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM8)
    {
        GPIO_InitTypeDef gpio_init_sturct;
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_TIM8_CLK_ENABLE();
        //定时器8的引脚时PC6
        gpio_init_sturct.Pin = GPIO_PIN_6;
        gpio_init_sturct.Mode = GPIO_MODE_AF_PP;
        gpio_init_sturct.Pull = GPIO_PULLUP;
        gpio_init_sturct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOC, &gpio_init_sturct);

        HAL_NVIC_SetPriority(TIM8_UP_IRQn,1,3);
        HAL_NVIC_EnableIRQ(TIM8_UP_IRQn);
    }
}

void atim_timx_npwm_chy_set(uint8_t npwm)
{
    if(npwm == 0) return;

    g_npwm_remain = npwm;
    //TIM_EVENTSOURCE_UPDATE 重装载到影子寄存器
    HAL_TIM_GenerateEvent(&g_timx_npwm_chy_handle,TIM_EVENTSOURCE_UPDATE);
    __HAL_TIM_ENABLE(&g_timx_npwm_chy_handle);
}

void TIM8_UP_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_npwm_chy_handle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM8)
    {
        if(g_npwm_remain)
        {
            TIM8->RCR = g_npwm_remain - 1;
            HAL_TIM_GenerateEvent(&g_timx_npwm_chy_handle,TIM_EVENTSOURCE_UPDATE);
            __HAL_TIM_ENABLE(&g_timx_npwm_chy_handle);
            g_npwm_remain = 0;
        }
        else
        {
            TIM8->CR1 &=~(1 << 0);
        }
    }
}
