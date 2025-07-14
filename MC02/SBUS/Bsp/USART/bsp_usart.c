#include "bsp_usart.h"


extern UART_HandleTypeDef huart5;
extern DMA_HandleTypeDef hdma_uart5_rx;

uint8_t SBUS_MultiRx_Buf[2][RC_FRAME_LENGTH];

uint32_t DataLength = 2 * RC_FRAME_LENGTH;

void USART_RxDMA_DoubleBuffer_Init(UART_HandleTypeDef *huart, uint32_t *DstAddress, uint32_t *SecondMemAddress,
                                   uint32_t DataLength) {

    huart->ReceptionType = HAL_UART_RECEPTION_TOIDLE;

    huart->RxEventType = HAL_UART_RXEVENT_IDLE;

    huart->RxXferSize = DataLength;

    SET_BIT(huart->Instance->CR3, USART_CR3_DMAR);

    __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);

    HAL_DMAEx_MultiBufferStart(huart->hdmarx, (uint32_t) &huart->Instance->RDR, (uint32_t) DstAddress,
                               (uint32_t) SecondMemAddress, DataLength);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {

    if (huart->Instance == UART5) {

        if (Size == RC_FRAME_LENGTH) {

        }
    }
}
