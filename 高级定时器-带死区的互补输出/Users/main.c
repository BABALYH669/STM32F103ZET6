#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/TIME/atime.h"

int main(void)
{
    uint8_t t = 0;
    HAL_Init();
    sys_stm32_clock_init(RCC_PLL_MUL9);
    delay_init(72);
    usart_init(115200);
    led_init();
    key_init();
    atim_timx_cplm_pwm_init(1000-1,72-1);
    atim_timx_cplm_pwm_set(700-1,250);//占空比70%

    while (1)
    {
        delay_ms(10);
        t++;

        if(t>=20)
        {
            LED0_TOGGLE();
            t = 0;
        }
        
    }
    
}
