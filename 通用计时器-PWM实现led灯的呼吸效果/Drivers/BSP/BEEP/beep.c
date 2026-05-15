#include "./BSP/BEEP/beep.h"

void beep_init(void){
    //定义结构体变量
    GPIO_InitTypeDef gpio_init_struct;
    //时钟使能
    BEEP_GPIO_CLK_ENABLE();
    //设置模式
    gpio_init_struct.Pin = BEEP_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    //使用HAL库初始化
    HAL_GPIO_Init(BEEP_GPIO_PORT,&gpio_init_struct);
    
    //蜂鸣器不响
    BEEP(0);
}

