#ifndef __KEY_H
#define __KEY_H

#include "./SYSTEM/sys/sys.h"
//函数声明
void key_init(void);
uint8_t key_scan01(void);
uint8_t key_scan00(void);
//引脚定义,key1的引脚是PE3
#define     KEY1_GPIO_PORT  GPIOE
#define     KEY1_GPIO_PIN   GPIO_PIN_3

#define     KEY0_GPIO_PORT  GPIOE
#define     KEY0_GPIO_PIN   GPIO_PIN_4
//PE口时钟使能
#define KEY_GPIO_CLK_ENABLE()   do{__HAL_RCC_GPIOE_CLK_ENABLE();}while(0)

#define KEY1 HAL_GPIO_ReadPin(KEY1_GPIO_PORT,KEY1_GPIO_PIN)
#define KEY0 HAL_GPIO_ReadPin(KEY0_GPIO_PORT,KEY0_GPIO_PIN)
#endif

