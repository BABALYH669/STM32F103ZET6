#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/LED.h"
#include "./BSP/KEY/KEY.h"
int main(void)
{
    HAL_Init();                                 /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);         /* 设置时钟,72M */
    delay_init(72);                             /* 初始化延时函数 */
    led_init();                                 /* 初始化LED */
    key_init();
    while(1)
    {
        if(key_scan01())
        {
            int num = 10;
            while(num)
            {
                LED1(1);
                delay_ms(200);
                LED0(1);
                delay_ms(200);
                LED1(0);
                delay_ms(200);
                LED0(0);
                delay_ms(200);
                num--;
            }
            LED1(0);
            LED0(0);
        }
        else if(key_scan00())
        {
            LED1(1);
            LED0(1);
        }
    }
}

