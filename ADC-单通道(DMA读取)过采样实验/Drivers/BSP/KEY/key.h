#ifndef __KEY_H
#define __KEY_H

#include "./SYSTEM/sys/sys.h"
//KEY1的原理图PE3
#define KEY1_GPIO_PORT  GPIOE
#define KEY1_GPIO_PIN   GPIO_PIN_3
//时钟使能
#define KEY1_GPIO_CLK_ENABLE()  do{__HAL_RCC_GPIOE_CLK_ENABLE();}while(0)
//KEY0的原理图PE4
#define KEY0_GPIO_PORT  GPIOE
#define KEY0_GPIO_PIN   GPIO_PIN_4
//时钟使能
#define KEY0_GPIO_CLK_ENABLE()  do{__HAL_RCC_GPIOE_CLK_ENABLE();}while(0)
//KEY_UP的原理图 PA0
#define KEY_UP_GPIO_PORT  GPIOA
#define KEY_UP_GPIO_PIN   GPIO_PIN_0
//时钟使能
#define KEY_UP_GPIO_CLK_ENABLE()  do{__HAL_RCC_GPIOA_CLK_ENABLE();}while(0)
//读电平函数(端口号,引脚号)
#define KEY0   HAL_GPIO_ReadPin(KEY0_GPIO_PORT,KEY0_GPIO_PIN)
#define KEY1   HAL_GPIO_ReadPin(KEY1_GPIO_PORT,KEY1_GPIO_PIN)
#define KEY_UP HAL_GPIO_ReadPin(KEY_UP_GPIO_PORT,KEY_UP_GPIO_PIN)
//用来判断按键是否按下,按下返回数值
#define KEY0_PRES         1        /* KEY0按下 */
#define KEY1_PRES         2        /* KEY1按下 */
#define KEY_UP_PRES       3        /* KEY_UP按下 */ 
//key.c文件中的函数声明
void key_init(void);
uint8_t key_scan(uint8_t mode);
#endif

