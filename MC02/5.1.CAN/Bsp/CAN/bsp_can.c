#include "bsp_can.h"
#include "DJI_Motor.h"

/* ���ͽṹ�� */
FDCAN_TxFrame_TypeDef DJIMotor_TxFrame = {
        .hcan = &hfdcan1,

        .Header.Identifier = 0x200,
        .Header.IdType = FDCAN_STANDARD_ID,
        .Header.TxFrameType = FDCAN_DATA_FRAME,
        .Header.DataLength = 8,
        .Header.ErrorStateIndicator =  FDCAN_ESI_ACTIVE,
        .Header.BitRateSwitch = FDCAN_BRS_OFF,
        .Header.FDFormat =  FDCAN_CLASSIC_CAN,
        .Header.TxEventFifoControl =  FDCAN_NO_TX_EVENTS,
        .Header.MessageMarker = 0,
};

/* ���սṹ�� */
FDCAN_RxFrame_TypeDef FDCAN1_RxFrame;


/* CAN�˲������� */
void FDCAN_FilterInit(void) {
    FDCAN_FilterTypeDef FDCAN1_FilterConfig;

    FDCAN1_FilterConfig.IdType = FDCAN_STANDARD_ID;
    FDCAN1_FilterConfig.FilterIndex = 0;
    FDCAN1_FilterConfig.FilterType = FDCAN_FILTER_MASK;
    FDCAN1_FilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    FDCAN1_FilterConfig.FilterID1 = 0x00000000;
    FDCAN1_FilterConfig.FilterID2 = 0x00000000;

    /* �����˲��� */
    if (HAL_FDCAN_ConfigFilter(&hfdcan1, &FDCAN1_FilterConfig) != HAL_OK) {
        Error_Handler();
    }

    /* ȫ�ֹ������� */
    /* ���յ���ϢID���׼ID���˲�ƥ�䣬������ */
    /* ���յ���ϢID����չID���˲�ƥ�䣬������ */
    /* ���˱�׼IDԶ��֡ */
    /* ������չIDԶ��֡ */
    if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan1, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) !=
        HAL_OK) {
        Error_Handler();
    }

    /* ����RX FIFO0���������ж� */
    if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK) {
        Error_Handler();
    }

    /* ����FDCAN */
    if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK) {
        Error_Handler();
    }

}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs) {
    HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &FDCAN1_RxFrame.Header, FDCAN1_RxFrame.Data);

    if (FDCAN1_RxFrame.Header.Identifier == 0x201) {
        DJI_Motor_Update_Data(&dji_motor, FDCAN1_RxFrame.Data);
        DJI_Round_Count(&dji_motor);
    }
}