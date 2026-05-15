#ifndef __DMA_H
#define __DMA_H

#include "./SYSTEM/sys/sys.h"
void dma_init(void);
void dma_enable_transmit(uint16_t cndtr);
extern uint8_t src_buf[10];
extern uint8_t dest_buf[10];

extern DMA_HandleTypeDef g_dma_handle;
#endif
