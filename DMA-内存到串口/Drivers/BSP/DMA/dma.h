#ifndef __DMA_H
#define __DMA_H

#include "./SYSTEM/sys/sys.h"

void dma_init(void);          /* 初始化 USART1 TX DMA */
void dma_send_data(void);     /* 触发一次 DMA 发送 */
extern DMA_HandleTypeDef  g_dma_handle;
#endif
