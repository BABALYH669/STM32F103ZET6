#include "./BSP/TIME/gtim.h"
//cap是输入的简写
TIM_HandleTypeDef g_timx_cap_chy_handle;
void gtim_timx_cap_chy_init(uint16_t arr,uint16_t psc)
{
    //设置为0,是因为这个初始化结构体内有很多变量,如果不赋值会匹配内存中的垃圾值
    TIM_IC_InitTypeDef timx_ic_cap_chy  = {0};
    g_timx_cap_chy_handle.Instance = TIM5;
    g_timx_cap_chy_handle.Init.Prescaler = psc;
    g_timx_cap_chy_handle.Init.Period = arr;
    g_timx_cap_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_IC_Init(&g_timx_cap_chy_handle);
    /*TI1上,通道1,因为TIM5通用定时器有TI1和TI2,
    分别分为TI1_通道1/通道2和TI2_通道1/通道2*/
    timx_ic_cap_chy.ICFilter = 0;
    timx_ic_cap_chy.ICPolarity = TIM_ICPOLARITY_RISING;
    timx_ic_cap_chy.ICPrescaler = TIM_ICPSC_DIV1;
    timx_ic_cap_chy.ICSelection = TIM_ICSELECTION_DIRECTTI;
    HAL_TIM_IC_ConfigChannel(&g_timx_cap_chy_handle,&timx_ic_cap_chy,TIM_CHANNEL_1);

    __HAL_TIM_ENABLE_IT(&g_timx_cap_chy_handle,TIM_IT_UPDATE);
    HAL_TIM_IC_Start_IT(&g_timx_cap_chy_handle,TIM_CHANNEL_1);
}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM5)
    {
        GPIO_InitTypeDef gpio_init_struct;
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_TIM5_CLK_ENABLE();

        gpio_init_struct.Pin = GPIO_PIN_0;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLDOWN;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA,&gpio_init_struct);

        HAL_NVIC_SetPriority(TIM5_IRQn,1,3);
        HAL_NVIC_EnableIRQ(TIM5_IRQn);
    }
}

uint8_t g_timxchy_cap_sta = 0;    /* 输入捕获状态 */
uint16_t g_timxchy_cap_val = 0;   /* 输入捕获值 */

void TIM5_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_cap_chy_handle);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM5)
    {
        if((g_timxchy_cap_sta & 0x80) == 0)
        {
            if(g_timxchy_cap_sta & 0x40)
            {
                g_timxchy_cap_sta |= 0x80;
                g_timxchy_cap_val = HAL_TIM_ReadCapturedValue(&g_timx_cap_chy_handle,TIM_CHANNEL_1);
                TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1);
                TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);
            }
            else
            {
                g_timxchy_cap_sta = 0;
                g_timxchy_cap_val = 0;
                g_timxchy_cap_sta |= 0x40; //把第四位置1,标记捕获到了上升沿
                __HAL_TIM_DISABLE(&g_timx_cap_chy_handle);//关闭定时器5
                __HAL_TIM_SET_COUNTER(&g_timx_cap_chy_handle,0);//关闭定时器5,并且清零,记录数据要从头开始
                TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1);//把 TIM 通道的1“输入捕获极性”设置寄存器清零到默认状态
                TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);
                __HAL_TIM_ENABLE(&g_timx_cap_chy_handle);
            }
        }
    }
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM5)
    {
        if((g_timxchy_cap_sta & 0x80)==0)
        {
            if(g_timxchy_cap_sta & 0x40)
            {
                if((g_timxchy_cap_sta & 0x3F) == 0x3F)
                {
                    TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1);
                    TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);
                    g_timxchy_cap_sta |= 0x80;
                    g_timxchy_cap_val = 0xFFFF;
                }
                else
                {
                    g_timxchy_cap_sta++;
                }
            }
        }
    }
}

