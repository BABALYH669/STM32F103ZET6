#include "./BSP/TIME/atime.h"

TIM_HandleTypeDef g_timx_cplm_pwm_init;
TIM_BreakDeadTimeConfigTypeDef g_sbreak_dead_time_config;

void atim_timx_cplm_pwm_init(uint16_t arr,uint16_t psc)
{
    TIM_OC_InitTypeDef tim_oc_cplm_pwm ={0};

    g_timx_cplm_pwm_init.Instance = TIM1;
    g_timx_cplm_pwm_init.Init.Prescaler = psc;
    g_timx_cplm_pwm_init.Init.Period = arr;
    g_timx_cplm_pwm_init.Init.CounterMode = TIM_COUNTERMODE_UP;
    g_timx_cplm_pwm_init.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
    HAL_TIM_PWM_Init(&g_timx_cplm_pwm_init);

    tim_oc_cplm_pwm.OCMode = TIM_OCMODE_PWM1;
    tim_oc_cplm_pwm.OCPolarity = TIM_OCPOLARITY_HIGH;
    tim_oc_cplm_pwm.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    tim_oc_cplm_pwm.OCIdleState = TIM_OCIDLESTATE_RESET;
    tim_oc_cplm_pwm.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    HAL_TIM_PWM_ConfigChannel(&g_timx_cplm_pwm_init,&tim_oc_cplm_pwm,TIM_CHANNEL_1);
    
    g_sbreak_dead_time_config.OffStateRunMode = TIM_OSSR_DISABLE;
    g_sbreak_dead_time_config.OffStateIDLEMode = TIM_OSSI_DISABLE;
    g_sbreak_dead_time_config.LockLevel = TIM_LOCKLEVEL_OFF;
    g_sbreak_dead_time_config.BreakState = TIM_BREAK_ENABLE;
    g_sbreak_dead_time_config.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    g_sbreak_dead_time_config.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE;
    HAL_TIMEx_ConfigBreakDeadTime(&g_timx_cplm_pwm_init,&g_sbreak_dead_time_config);
    
    HAL_TIM_PWM_Start(&g_timx_cplm_pwm_init,TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(&g_timx_cplm_pwm_init,TIM_CHANNEL_1);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM1)
    {
        GPIO_InitTypeDef gpio_init_struct;
        __HAL_RCC_GPIOE_CLK_ENABLE();
        __HAL_RCC_TIM1_CLK_ENABLE();

        gpio_init_struct.Pin = GPIO_PIN_8; //重定义功能TIM1_CH1N
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOE,&gpio_init_struct);

        gpio_init_struct.Pin = GPIO_PIN_9;//重定义功能TIM1_CH1
        HAL_GPIO_Init(GPIOE,&gpio_init_struct); 
        gpio_init_struct.Pin = GPIO_PIN_15;//重定义功能TIM1_BKIN
        HAL_GPIO_Init(GPIOE,&gpio_init_struct);

        //使用重定义功能开启重定义时钟
        __HAL_RCC_AFIO_CLK_ENABLE();
        __HAL_AFIO_REMAP_TIM1_ENABLE();
    }

}
void atim_timx_cplm_pwm_set(uint16_t ccr, uint8_t dtg)
{
    __HAL_TIM_SET_COMPARE(&g_timx_cplm_pwm_init,TIM_CHANNEL_1,ccr);
    g_sbreak_dead_time_config.DeadTime = dtg;     
    HAL_TIMEx_ConfigBreakDeadTime(&g_timx_cplm_pwm_init,&g_sbreak_dead_time_config); 
}
