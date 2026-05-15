#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/WWDG/wwdg.h"


int main(void)
{
    HAL_Init();
    sys_stm32_clock_init(RCC_PLL_MUL9);
    delay_init(72);
    usart_init(115200);
    led_init();
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST) != RESET)
    {
        printf("看门狗已复位\r\n");
        __HAL_RCC_CLEAR_RESET_FLAGS();
    }
    else
    {
        printf("外部复位\r\n");
    }

    delay_ms(1000);
    printf("请在窗口期喂狗\r\n");
    wwdg_init(0x7F,0x5f,WWDG_PRESCALER_8);

    while(1)
    {
        delay_ms(90);
        LED0_TOGGLE();
    }

}

