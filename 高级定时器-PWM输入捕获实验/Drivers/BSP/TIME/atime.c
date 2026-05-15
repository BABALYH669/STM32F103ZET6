#include "./BSP/TIME/atime.h"

TIM_HandleTypeDef g_timx_pwmin_chy_handle;

uint8_t g_timxchy_pwmin_sta  = 0;   /* PWM输入状态 */
uint16_t g_timxchy_pwmin_psc  = 0;  /* PWM输入分频系数 */
uint32_t g_timxchy_pwmin_hval = 0;  /* PWM的高电平脉宽 */
uint32_t g_timxchy_pwmin_cval = 0;  /* PWM的周期宽度 */

void atim_timx_pwmin_chy_init(void)
{
    TIM_IC_InitTypeDef tim_ic_pwmin_chy = {0};
    TIM_SlaveConfigTypeDef  slave_config = {0};

    g_timx_pwmin_chy_handle.Instance = TIM8;
    g_timx_pwmin_chy_handle.Init.Prescaler = 0;
    g_timx_pwmin_chy_handle.Init.Period = 65535;
    g_timx_pwmin_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_IC_Init(&g_timx_pwmin_chy_handle);

    slave_config.SlaveMode = TIM_SLAVEMODE_RESET;
    slave_config.InputTrigger = TIM_TS_TI1FP1;
    slave_config.TriggerPolarity = TIM_TRIGGERPOLARITY_RISING;
    slave_config.TriggerPrescaler = 0;
    HAL_TIM_SlaveConfigSynchro(&g_timx_pwmin_chy_handle,&slave_config);

    //上升沿检测,选择输入端IC1映射到TI1
    tim_ic_pwmin_chy.ICPolarity = TIM_ICPOLARITY_RISING;
    tim_ic_pwmin_chy.ICPrescaler = TIM_ICPSC_DIV1;
    tim_ic_pwmin_chy.ICSelection = TIM_ICSELECTION_DIRECTTI;
    tim_ic_pwmin_chy.ICFilter = 0;
    HAL_TIM_IC_ConfigChannel(&g_timx_pwmin_chy_handle,&tim_ic_pwmin_chy,TIM_CHANNEL_1);

    //下降沿检测,选择输入端IC2映射到TI1
    tim_ic_pwmin_chy.ICSelection = TIM_ICSELECTION_INDIRECTTI;
    tim_ic_pwmin_chy.ICPolarity = TIM_ICPOLARITY_FALLING;
    HAL_TIM_IC_ConfigChannel(&g_timx_pwmin_chy_handle,&tim_ic_pwmin_chy,TIM_CHANNEL_2);

    //HAL_TIM_IC_Start_IT
    HAL_TIM_IC_Start_IT(&g_timx_pwmin_chy_handle,TIM_CHANNEL_1);
    HAL_TIM_IC_Start(&g_timx_pwmin_chy_handle,TIM_CHANNEL_2);
}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM8)
    {
        GPIO_InitTypeDef gpio_init_struct = {0};
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_TIM8_CLK_ENABLE();

        gpio_init_struct.Pin = GPIO_PIN_6;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLDOWN;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOC,&gpio_init_struct);
        HAL_NVIC_SetPriority(TIM8_CC_IRQn,1,3);
        HAL_NVIC_EnableIRQ(TIM8_CC_IRQn);

    }
}

void TIM8_CC_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_pwmin_chy_handle);
}

void atim_timx_pwmin_chy_restart(void)
{
    sys_intx_disable(); //关闭中断

    g_timxchy_pwmin_sta = 0;
    g_timxchy_pwmin_hval = 0;
    g_timxchy_pwmin_cval = 0;

    sys_intx_enable(); //打开中断
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM8)
    {
        if(g_timxchy_pwmin_sta == 0)
        {
            if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
            {
                g_timxchy_pwmin_hval = HAL_TIM_ReadCapturedValue(&g_timx_pwmin_chy_handle,TIM_CHANNEL_2)+1+1;
                g_timxchy_pwmin_cval = HAL_TIM_ReadCapturedValue(&g_timx_pwmin_chy_handle,TIM_CHANNEL_1)+1+1;
                g_timxchy_pwmin_sta = 1;
            }
        }
    }
}
