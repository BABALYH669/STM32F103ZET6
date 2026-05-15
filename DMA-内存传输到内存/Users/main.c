#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./BSP/DMA/dma.h"
#include "string.h"

uint8_t src_buf[10] = {0x0a, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
uint8_t dest_buf[10] = {0};

int main(void)
{
    uint8_t key;

    HAL_Init();
    sys_stm32_clock_init(RCC_PLL_MUL9);
    delay_init(72);
    usart_init(115200);
    led_init();
    key_init();
    dma_init();

    while (1)
    {
        key = key_scan(0);
        if(key == KEY0_PRES)
        {
            memset(dest_buf,0,10);
            dma_enable_transmit(10);
            while (1)
            {
                if(__HAL_DMA_GET_FLAG(&g_dma_handle,DMA_FLAG_TC1))
                {
                    __HAL_DMA_CLEAR_FLAG(&g_dma_handle,DMA_FLAG_TC1);
                    printf("传输完成\r\n");
                    break;
                }
            }
            
        }
        LED0_TOGGLE();
        delay_ms(200);
    }
    
}
