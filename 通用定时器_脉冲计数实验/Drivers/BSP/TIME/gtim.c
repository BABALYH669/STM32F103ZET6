#include "./BSP/TIME/gtim.h"

TIM_HandleTypeDef g_tim_cnt_chy_handle;
void gtim_timx_cnt_chy_init(uint16_t psc)
{
    TIM_SlaveConfigTypeDef tim_slave_config = {0};

    g_tim_cnt_chy_handle.Instance = TIM2;
    g_tim_cnt_chy_handle.Init.Prescaler = psc;
    g_tim_cnt_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP; //递增计数模式
    g_tim_cnt_chy_handle.Init.Period = 65535;
    HAL_TIM_IC_Init(&g_tim_cnt_chy_handle);
    
    tim_slave_config.SlaveMode = TIM_SLAVEMODE_EXTERNAL1; //从模式选择
    tim_slave_config.InputTrigger = TIM_TS_TI1FP1;//输入触发源选择
    tim_slave_config.TriggerPolarity = TIM_TRIGGERPOLARITY_RISING; //触发极性
    tim_slave_config.TriggerFilter = 0; //输入滤波器选择

    HAL_TIM_SlaveConfigSynchro(&g_tim_cnt_chy_handle,&tim_slave_config);
    HAL_TIM_IC_Start(&g_tim_cnt_chy_handle,TIM_CHANNEL_1);
}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        GPIO_InitTypeDef gpio_init_struct;
        __HAL_RCC_TIM2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pin = GPIO_PIN_0;
        gpio_init_struct.Pull = GPIO_PULLDOWN;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA,&gpio_init_struct);
    }
}

