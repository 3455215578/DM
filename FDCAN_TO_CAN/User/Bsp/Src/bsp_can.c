#include "stm32h7xx.h"                  // Device header
#include "bsp_can.h"
#include "dm_imu.h"

//extern FDCAN_HandleTypeDef hfdcan1;
//extern FDCAN_HandleTypeDef hfdcan2;
extern FDCAN_HandleTypeDef hfdcan3;

FDCAN_RxFrame_TypeDef FDCAN3_RxFrame;

/* ���ͽṹ�� */
FDCAN_TxFrame_TypeDef ImuTxFrame = {
  .hcan = &hfdcan3,
  .Header.Identifier = 0x6FF, // ��Ϊimuֻ��һ����������ֱ��ָ��id
  .Header.IdType = FDCAN_STANDARD_ID, 
  .Header.TxFrameType = FDCAN_DATA_FRAME,
  .Header.DataLength = 4,
  .Header.ErrorStateIndicator =  FDCAN_ESI_ACTIVE,
  .Header.BitRateSwitch = FDCAN_BRS_OFF,
  .Header.FDFormat =  FDCAN_CLASSIC_CAN,           
  .Header.TxEventFifoControl =  FDCAN_NO_TX_EVENTS,  
  .Header.MessageMarker = 0,
};

void FDCAN_FilterInit(void)
{
//	/**********************************  FDCAN1  *********************************************/
//	FDCAN_FilterTypeDef FDCAN1_FilterConfig;
//	
//	FDCAN1_FilterConfig.IdType = FDCAN_STANDARD_ID;
//	FDCAN1_FilterConfig.FilterIndex = 0;
//	FDCAN1_FilterConfig.FilterType = FDCAN_FILTER_MASK;
//	FDCAN1_FilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
//	FDCAN1_FilterConfig.FilterID1 = 0x00000000; 
//	FDCAN1_FilterConfig.FilterID2 = 0x00000000; 
//  
//	/* �����˲��� */
//	if(HAL_FDCAN_ConfigFilter(&hfdcan1, &FDCAN1_FilterConfig) != HAL_OK)
//	{
//		Error_Handler();
//	}
//		
//	/* ȫ�ֹ������� */
//	/* ���յ���ϢID���׼ID���˲�ƥ�䣬������ */
//	/* ���յ���ϢID����չID���˲�ƥ�䣬������ */
//	/* ���˱�׼IDԶ��֡ */ 
//	/* ������չIDԶ��֡ */ 
//	if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan1, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK)
//	{
//		Error_Handler();
//	}

//	/* ����RX FIFO0���������ж� */
//	if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
//	{
//		Error_Handler();
//	}
// 
//	if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK)
//	{
//		Error_Handler();
//	}
//	
//	
//	/**********************************  FDCAN2  *********************************************/
//	FDCAN_FilterTypeDef FDCAN2_FilterConfig;
//	
//	FDCAN2_FilterConfig.IdType = FDCAN_STANDARD_ID;
//	FDCAN2_FilterConfig.FilterIndex = 0;
//	FDCAN2_FilterConfig.FilterType = FDCAN_FILTER_MASK;
//	FDCAN2_FilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
//	FDCAN2_FilterConfig.FilterID1 = 0x00000000; 
//	FDCAN2_FilterConfig.FilterID2 = 0x00000000; 
//  
//	/* �����˲��� */
//	if(HAL_FDCAN_ConfigFilter(&hfdcan2, &FDCAN2_FilterConfig) != HAL_OK)
//	{
//		Error_Handler();
//	}
//		
//	/* ȫ�ֹ������� */
//	/* ���յ���ϢID���׼ID���˲�ƥ�䣬������ */
//	/* ���յ���ϢID����չID���˲�ƥ�䣬������ */
//	/* ���˱�׼IDԶ��֡ */ 
//	/* ������չIDԶ��֡ */ 
//	if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan2, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK)
//	{
//		Error_Handler();
//	}

//	/* ����RX FIFO0���������ж� */
//	if (HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
//	{
//		Error_Handler();
//	}
// 
//	if (HAL_FDCAN_Start(&hfdcan2) != HAL_OK)
//	{
//		Error_Handler();
//	}
	
	/**********************************  FDCAN3  *********************************************/
	FDCAN_FilterTypeDef FDCAN3_FilterConfig;
	
	FDCAN3_FilterConfig.IdType = FDCAN_STANDARD_ID;
	FDCAN3_FilterConfig.FilterIndex = 0;
	FDCAN3_FilterConfig.FilterType = FDCAN_FILTER_MASK;
	FDCAN3_FilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
	FDCAN3_FilterConfig.FilterID1 = 0x00000000; 
	FDCAN3_FilterConfig.FilterID2 = 0x00000000; 
  
	/* �����˲��� */
	if(HAL_FDCAN_ConfigFilter(&hfdcan3, &FDCAN3_FilterConfig) != HAL_OK)
	{
		Error_Handler();
	}
		
	/* ȫ�ֹ������� */
	/* ���յ���ϢID���׼ID���˲�ƥ�䣬������ */
	/* ���յ���ϢID����չID���˲�ƥ�䣬������ */
	/* ���˱�׼IDԶ��֡ */ 
	/* ������չIDԶ��֡ */ 
//	if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan3, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK)
//	{
//		Error_Handler();
//	}

	/* ����RX FIFO0���������ж� */
	if (HAL_FDCAN_ActivateNotification(&hfdcan3, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
	{
		Error_Handler();
	}
 
	if (HAL_FDCAN_Start(&hfdcan3) != HAL_OK)
	{
		Error_Handler();
	}
	
}


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{ 
	HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &FDCAN3_RxFrame.Header, FDCAN3_RxFrame.Data);
		
	if(FDCAN3_RxFrame.Header.Identifier == 0x11)
	{
		IMU_UpdateData(FDCAN3_RxFrame.Data);
	}

}

