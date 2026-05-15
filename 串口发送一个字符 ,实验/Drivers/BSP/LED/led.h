#ifndef _LED_H
#define _LED_H
#include "./SYSTEM/sys/sys.h"
void led_init(void);
/*引脚定义*/
#define     LED0_GPIO_PORT   GPIOB
#define     LED0_GPIO_PIN    GPIO_PIN_5
//PB口时钟使能
//其中do while(0) 等价于 __HAL_RCC_GPIOB_CLK_ENABLE(); 只是套了一个壳子,表示只执行一次
#define LED0_GPIO_CLK_ENABLE()  do{__HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

//引脚定义
#define     LED1_GPIO_PORT  GPIOE
#define     LED1_GPIO_PIN   GPIO_PIN_5
//PE口时钟使能
#define LED1_GPIO_CLK_ENABLE()  do{__HAL_RCC_GPIOE_CLK_ENABLE();}while(0)
/*
    do while(0)里是一个三目运算符,其中'\'是宏定义中表示换行的
    以下两个参数是在第一行第二行定义了的
    LED0_GPIO_PORT
    LED0_GPIO_PIN
    以下的参数代表输出高电平  = 1
    GPIO_PIN_SET
*/
//LED端口定义
//这一段在主函数main.c文件中使用,x = 1 执行亮 x = 0执行灭
#define LED0(x) do{ x ? \
    HAL_GPIO_WritePin(LED0_GPIO_PORT,LED0_GPIO_PIN,GPIO_PIN_SET) :\
    HAL_GPIO_WritePin(LED0_GPIO_PORT,LED0_GPIO_PIN,GPIO_PIN_RESET);\
                   }while(0)

#define LED1(x) do{ x ? \
    HAL_GPIO_WritePin(LED1_GPIO_PORT,LED1_GPIO_PIN,GPIO_PIN_SET) :\
    HAL_GPIO_WritePin(LED1_GPIO_PORT,LED1_GPIO_PIN,GPIO_PIN_RESET);\
                   }while(0)

//LED取反定义
#define LED0_TOGGLE()  do{ HAL_GPIO_TogglePin(LED0_GPIO_PORT,LED0_GPIO_PIN);}while(0)
#define LED1_TOGGLE()  do{ HAL_GPIO_TogglePin(LED1_GPIO_PORT,LED1_GPIO_PIN);}while(0)
#endif
