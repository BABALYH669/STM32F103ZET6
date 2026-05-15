#include "./BSP/LED/led.h"

void led_init(void){
    //定义GPIO初始化结构体变量
    GPIO_InitTypeDef gpio_init_struct;
    //端口时钟使能
    LED0_GPIO_CLK_ENABLE();
    LED1_GPIO_CLK_ENABLE();
    //设置模式,引脚 模式 电阻(上下) 翻转速度
    gpio_init_struct.Pin = LED0_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    //使用HAL库初始化GPIO
    HAL_GPIO_Init(LED0_GPIO_PORT,&gpio_init_struct);
    
    gpio_init_struct.Pin = LED1_GPIO_PIN;
    HAL_GPIO_Init(LED1_GPIO_PORT,&gpio_init_struct);

    LED0(1);
    LED1(1);
}


