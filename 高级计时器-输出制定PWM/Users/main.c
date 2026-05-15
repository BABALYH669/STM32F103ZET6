#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/TIME/atime.h"

int main(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    uint8_t key;
    uint8_t t = 0;
    
    HAL_Init();
    sys_stm32_clock_init(RCC_PLL_MUL9);
    delay_init(72);
    usart_init(115200);
    led_init();
    key_init();
    

    __HAL_RCC_GPIOE_CLK_ENABLE();
    
    gpio_init_struct.Pin = GPIO_PIN_5;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOE, &gpio_init_struct);

    atim_timx_npwm_chy_init(5000-1,7200-1);

    atim_timx_npwm_chy_set(5);

    while (1)
    {
        key = key_scan(0);
        if(key == KEY0_PRES)
        {
            atim_timx_npwm_chy_set(6);
        }
 
        t++;
        delay_ms(10);

        if (t > 50)                    /* 控制LED0闪烁, 提示程序运行状态 */
        {
            t = 0;
            LED0_TOGGLE();
        }
    }
}
