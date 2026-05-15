#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/TIME/gtim.h"

extern g_timxchy_cap_sta = 0;    /* ?????? */
extern g_timxchy_cap_val = 0;   /* ????? */


int main(void)
{
    uint32_t temp = 0;
    uint8_t t = 0;

    HAL_Init();
    sys_stm32_clock_init(RCC_PLL_MUL9);
    delay_init(72);
    usart_init(115200);
    led_init();
    //ARR = 0xFFFF = 65535
    gtim_timx_cap_chy_init(0xFFFF,72-1);

    while(1)
    {
        if(g_timxchy_cap_sta & 0x80)
        {
            temp = g_timxchy_cap_sta & 0x3F;
            temp *= 65536;
            temp += g_timxchy_cap_val;
            printf("HIGH:%d  us\r\n",temp);
            g_timxchy_cap_sta = 0;
        }

        t++;

        if(t > 20)
        {
            t = 0;
            LED0_TOGGLE();
        }
        delay_ms(10);

    }
}
