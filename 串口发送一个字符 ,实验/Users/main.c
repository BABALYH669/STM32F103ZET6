#include "./stm32f1xx_it.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/LED.h"

int main(void)
{
    HAL_Init();
    sys_stm32_clock_init(RCC_PLL_MUL9);
    delay_ms(72);
    usart_init(115200);
    led_init();
     while(1)
    {
        if(g_usart1_rx_flag == 1)               // 检测到接收完成
        {
            // 回显接收的字节（使用HAL库，统一逻辑）
            HAL_UART_Transmit(&g_uart1_handle, g_rx_buffer, 2, 100);
            // 等待发送完成（可选，增强稳定性）
            while(__HAL_UART_GET_FLAG(&g_uart1_handle, UART_FLAG_TC) != 1);
            
            printf("\r\n");                     // 换行
            g_usart1_rx_flag = 0;               // 清除接收标志
        }
        delay_ms(10);                           // 降低轮询频率
    }
}
