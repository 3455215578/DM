#ifndef _BSP_USART_H
#define _BSP_USART_H

#include "usart.h"

#define RC_FRAME_LENGTH 18
#define SBUS_RX_BUF_NUM 36

void USART_RxDMA_DoubleBuffer_Init(UART_HandleTypeDef *huart, uint32_t *DstAddress, uint32_t *SecondMemAddress,
                                   uint32_t DataLength);

extern uint32_t DataLength;
extern uint8_t SBUS_MultiRx_Buf[2][RC_FRAME_LENGTH];

#endif
