#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/DMA/dma.h"
#include <string.h>
int main(void)
{
    uint8_t key;

    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);     /* 系统时钟 72MHz */
    delay_init(72);                         /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化（会配置 g_uart1_handle） */
    led_init();
    key_init();
    dma_init();                             /* DMA 初始化（必须放在 usart_init 之后） */

    while (1)
    {
        key = key_scan(0);
        if (key == KEY0_PRES)
        {
            printf("\r\nStart DMA send...\r\n");
            dma_send_data();                /* 启动DMA发送 */

            /* 等待 DMA1_Channel4 传输完成 */
            while (!__HAL_DMA_GET_FLAG(&g_dma_handle, DMA_FLAG_TC4));

            /* 清除完成标志 */
            __HAL_DMA_CLEAR_FLAG(&g_dma_handle, DMA_FLAG_TC4);

            printf("OVER\r\n");             /* 发完提示 */
        }

        delay_ms(200);
        LED0_TOGGLE();                      /* 闪烁表示系统运行 */
    }
}
