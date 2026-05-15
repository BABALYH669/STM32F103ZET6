#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/LED.h"

int main(void)
{
    HAL_Init();                                 /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);         /* 设置时钟,72M */
    delay_init(72);                             /* 初始化延时函数 */
    led_init();                                 /* 初始化LED */
    
    while(1)
    {
        LED0(0);                                /* LED0 亮 */
        LED1(1);                                /* LED1 灭 */
        delay_ms(5000);
        LED0(1);                                /* LED0 灭 */
        LED1(0);                                /* LED1 亮 */
        delay_ms(5000);
    }
}

