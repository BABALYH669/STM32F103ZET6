#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/TIME/gtim.h"

int main(void)
{
    uint16_t curcnt;
    uint16_t oldcnt;
    uint8_t key;
    uint8_t t = 0;

    HAL_Init();
    sys_stm32_clock_init(RCC_PLL_MUL9);
    delay_init(72);
    usart_init(115200);
    key_init();
    led_init();
    gtim_timx_cnt_chy_init(0);

    while (1)
    {
        key = key_scan(0);
        if(key == KEY0_PRES)
        {
            __HAL_TIM_SET_COUNTER(&g_tim_cnt_chy_handle,0);
        }

        curcnt = __HAL_TIM_GET_COUNTER(&g_tim_cnt_chy_handle);
        if(oldcnt != curcnt)
        {
            oldcnt = curcnt;
            printf("CNT:%d \r\n",oldcnt);
        }

        t++;

        if(t>20)
        {
            t = 0;
            LED0_TOGGLE();
        }
        delay_ms(10);
    }
    
}

