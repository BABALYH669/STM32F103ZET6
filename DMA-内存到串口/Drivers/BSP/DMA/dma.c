#include "./BSP/DMA/dma.h"
#include "./SYSTEM/delay/delay.h"

extern UART_HandleTypeDef g_uart1_handle;      /* 串口句柄（来自usart.c） */

static uint8_t my_buffer[] = "Hello ALIENTEK DMA!\r\n";  /* 待发送数据 */

/**
 * @brief  初始化 USART1 TX DMA
 * @note   通道固定为 DMA1_Channel4
 */
void dma_init(void)
{
    /* 使能 DMA1 时钟 */
    __HAL_RCC_DMA1_CLK_ENABLE();

    /* 将 DMA 句柄与串口链接（发送方向） */
    __HAL_LINKDMA(&g_uart1_handle, hdmatx, g_dma_handle);

    /* 配置 DMA 通道参数 */
    g_dma_handle.Instance                 = DMA1_Channel4;            /* USART1_TX 使用 DMA1_Channel4 */
    g_dma_handle.Init.Direction           = DMA_MEMORY_TO_PERIPH;     /* 存储器到外设 */
    g_dma_handle.Init.PeriphInc           = DMA_PINC_DISABLE;         /* 外设地址不递增 */
    g_dma_handle.Init.MemInc              = DMA_MINC_ENABLE;          /* 存储器地址递增 */
    g_dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;      /* 8位数据宽度 */
    g_dma_handle.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;      /* 8位数据宽度 */
    g_dma_handle.Init.Mode                = DMA_NORMAL;               /* 普通模式（一次传输） */
    g_dma_handle.Init.Priority            = DMA_PRIORITY_MEDIUM;      /* 中等优先级 */

    HAL_DMA_Init(&g_dma_handle);
}

/**
 * @brief  启动一次 DMA 发送（将 my_buffer 的数据发到串口）
 */
void dma_send_data(void)
{
    /* 长度 = 字符串有效字符数（不含结束符） */
    HAL_UART_Transmit_DMA(&g_uart1_handle, my_buffer, sizeof(my_buffer) - 1);
}