#include "./BSP/KEY/key.h"
#include "./SYSTEM/delay/delay.h"

void key_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    KEY1_GPIO_CLK_ENABLE();
    KEY0_GPIO_CLK_ENABLE();
    KEY_UP_GPIO_CLK_ENABLE();
    
    gpio_init_struct.Pin = KEY1_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(KEY1_GPIO_PORT,&gpio_init_struct);
    
    gpio_init_struct.Pin = KEY0_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(KEY0_GPIO_PORT,&gpio_init_struct);
    
    gpio_init_struct.Pin = KEY_UP_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_PULLDOWN;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(KEY_UP_GPIO_PORT,&gpio_init_struct);
    
    
    
}


uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_release = 1;
    uint8_t keyval = 0;

    if (mode) key_release = 1;

    if (key_release && (KEY0 == 0 || KEY1 == 0 || KEY_UP == 1))
    {
        delay_ms(10);
        key_release = 0;

        if (KEY0 == 0)  keyval = KEY0_PRES;
        if (KEY1 == 0)  keyval = KEY1_PRES;
        if (KEY_UP == 1) keyval = KEY_UP_PRES;
    }
    else if (KEY0 == 1 && KEY1 == 1 && KEY_UP == 0)
    {
        key_release = 1;
    }

    return keyval;
}

