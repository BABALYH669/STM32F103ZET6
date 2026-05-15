#include "./BSP/DMA/dma.h"

DMA_HandleTypeDef g_dma_handle;

void dma_init(void)
{
    __HAL_RCC_DMA1_CLK_ENABLE();

    g_dma_handle.Instance = DMA1_Channel1;
    g_dma_handle.Init.Direction = DMA_MEMORY_TO_MEMORY;
    g_dma_handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    g_dma_handle.Init.MemInc = DMA_MINC_ENABLE;
    g_dma_handle.Init.Mode = DMA_NORMAL;
    g_dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    g_dma_handle.Init.PeriphInc = DMA_PINC_ENABLE;
    g_dma_handle.Init.Priority = DMA_PRIORITY_HIGH;

    HAL_DMA_Init(&g_dma_handle);
    HAL_DMA_Start(&g_dma_handle,(uint32_t)src_buf,(uint32_t)dest_buf,0);
}

void dma_enable_transmit(uint16_t cndtr)
{
    __HAL_DMA_DISABLE(&g_dma_handle);
    g_dma_handle.Instance->CNDTR = cndtr;
    __HAL_DMA_ENABLE(&g_dma_handle);
}
