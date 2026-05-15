#ifndef __BEEP_H
#define __BEEP_H
#include "./SYSTEM/sys/sys.h"
//BEEP原理图PB8
#define BEEP_GPIO_PORT  GPIOB
#define BEEP_GPIO_PIN   GPIO_PIN_8
//时钟使能
#define BEEP_GPIO_CLK_ENABLE() do{__HAL_RCC_GPIOB_CLK_ENABLE();}while(0)

//使用BEEP(0) BEEP(1) 控制蜂鸣器的响与不响
#define BEEP(x) do{x?\
        HAL_GPIO_WritePin(BEEP_GPIO_PORT,BEEP_GPIO_PIN,GPIO_PIN_SET) :\
        HAL_GPIO_WritePin(BEEP_GPIO_PORT,BEEP_GPIO_PIN,GPIO_PIN_RESET); }while(0)
//BEEP引脚电平翻转
#define BEEP_TOGGLE() do{HAL_GPIO_TogglePin(BEEP_GPIO_PORT,BEEP_GPIO_PIN);}while(0)

void beep_init(void);
#endif
        
