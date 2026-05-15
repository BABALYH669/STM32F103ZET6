#include "./BSP/KEY/KEY.h"
#include "./SYSTEM/delay/delay.h"//延时函数的头文件
void key_init(void)
{
    GPIO_InitTypeDef gpio_init_struct; //初始化GPIO结构体
    
    KEY_GPIO_CLK_ENABLE();//时钟使能
    
    gpio_init_struct.Pin = GPIO_PIN_3;//PE3引脚
    gpio_init_struct.Mode = GPIO_MODE_INPUT;//输入模式
    gpio_init_struct.Pull = GPIO_PULLUP;//上拉电阻
    
    HAL_GPIO_Init(GPIOE,&gpio_init_struct);

}

//按键消抖函数(扫描)
uint8_t key_scan01(void)
{
    if(KEY1 == 0) //检测按键是否按下(低电平有效)
    {
        delay_ms(10);//延迟10ms为了给按键消抖
        if(KEY1 == 0)//再次确认是否按下
        {
            //while(KEY1 == 0);//等待按键按下松开加上按下按键会有明显延迟
            delay_ms(10);//延迟10ms为了给按键消抖
            return 1;//确认按下返回1
        }
    }
    return 0;//无效按键返回0
}

//按键消抖函数(扫描)
uint8_t key_scan00(void)
{
    if(KEY0 == 0) //检测按键是否按下(低电平有效)
    {
        delay_ms(10);//延迟10ms为了给按键消抖
        if(KEY0 == 0)//再次确认是否按下
        {
            //while(KEY0 == 0);//等待按键按下松开
            delay_ms(10);//延迟10ms为了给按键消抖
            return 1;//确认按下返回1
        }
    }
    return 0;//无效按键返回0
}

