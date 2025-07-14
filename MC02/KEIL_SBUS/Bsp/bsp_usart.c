#include "stm32h7xx.h"                  // Device header
#include "usart.h"
#include "bsp_usart.h"
#include "remote_control.h"

uint8_t SBUS_MultiRx_Buf[2][RC_FRAME_LENGTH];

uint32_t DataLength = 36;

void USART_DMAEx_MultiBuffer_Init(UART_HandleTypeDef *huart, uint32_t *DstAddress, uint32_t *SecondMemAddress, uint32_t DataLength)
{
	huart->ReceptionType = HAL_UART_RECEPTION_TOIDLE;

	huart->RxEventType = HAL_UART_RXEVENT_IDLE;

	huart->RxXferSize    = DataLength;

	SET_BIT(huart->Instance->CR3,USART_CR3_DMAR);

	__HAL_UART_ENABLE_IT(huart, UART_IT_IDLE); 
 
	do{
		__HAL_DMA_DISABLE(huart->hdmarx);
	}while(((DMA_Stream_TypeDef  *)huart->hdmarx->Instance)->CR & DMA_SxCR_EN);

	((DMA_Stream_TypeDef  *)huart->hdmarx->Instance)->PAR = (uint32_t)&huart->Instance->RDR;

	((DMA_Stream_TypeDef  *)huart->hdmarx->Instance)->M0AR = (uint32_t)DstAddress;

	((DMA_Stream_TypeDef  *)huart->hdmarx->Instance)->M1AR = (uint32_t)SecondMemAddress;

	((DMA_Stream_TypeDef  *)huart->hdmarx->Instance)->NDTR = DataLength;

	SET_BIT(((DMA_Stream_TypeDef  *)huart->hdmarx->Instance)->CR, DMA_SxCR_DBM);

	__HAL_DMA_ENABLE(huart->hdmarx);	
}

static void USER_USART5_RxHandler(UART_HandleTypeDef *huart,uint16_t Size){ 

 if(((((DMA_Stream_TypeDef  *)huart->hdmarx->Instance)->CR) & DMA_SxCR_CT ) == RESET) 
 { 
	  __HAL_DMA_DISABLE(huart->hdmarx); 

	  ((DMA_Stream_TypeDef  *)huart->hdmarx->Instance)->CR |= DMA_SxCR_CT; 
 
	  __HAL_DMA_SET_COUNTER(huart->hdmarx,SBUS_RX_BUF_NUM); 

	  if(Size == RC_FRAME_LENGTH) 
	  { 
		SBUS_TO_RC(SBUS_MultiRx_Buf[0],&remote_ctrl); 
	  } 
 
 }else{ 
	 __HAL_DMA_DISABLE(huart->hdmarx); 

	  ((DMA_Stream_TypeDef  *)huart->hdmarx->Instance)->CR &= ~(DMA_SxCR_CT); 
 
	  __HAL_DMA_SET_COUNTER(huart->hdmarx,SBUS_RX_BUF_NUM); 

	  if(Size == RC_FRAME_LENGTH) 
	  { 
		SBUS_TO_RC(SBUS_MultiRx_Buf[1],&remote_ctrl); 
	  }			 
 } 
		 __HAL_DMA_ENABLE(huart->hdmarx);				 
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if(huart == &huart5)
	{
		USER_USART5_RxHandler(huart,Size);
	}
	
}
