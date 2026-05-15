//包含LED驱动的头文件
#include "./BSP/LED/LED.h"
//初始化led_init函数
void led_init(void){
    //定义GPIO初始化结构体变量,起名为gpio_init_struct
    GPIO_InitTypeDef gpio_init_struct;
    LED0_GPIO_CLK_ENABLE();//使能LED0   GPIO端口时钟
    LED1_GPIO_CLK_ENABLE();//使能LED1   GPIO端口时钟
    
    gpio_init_struct.Pin = LED0_GPIO_PIN;//初始化引脚编号
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;//推挽输出
    gpio_init_struct.Pull = GPIO_PULLUP;//开启上拉电阻,提供高电平
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH; //GPIO反转速度为高速
    HAL_GPIO_Init(LED0_GPIO_PORT,&gpio_init_struct);//调用HAL库函数HAL_GPIO_Init
    
    gpio_init_struct.Pin = LED1_GPIO_PIN;
    HAL_GPIO_Init(LED1_GPIO_PORT,&gpio_init_struct);
    
    LED0(1);
    LED1(1);
    
}

