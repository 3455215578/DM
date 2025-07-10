#include "DJI_Motor.h"

DJI_Motor_t motor;

/**
 * @brief DJI�������
 * @param[in] motor  ����ṹ��ָ��
 * @param[in] data   ���յ������ݵ�ָ��
 */
void DJI_Motor_Update_Data(DJI_Motor_t *motor, uint8_t *data) {
    motor->last_ecd = motor->ecd;
    /* ת�ӻ�е�Ƕ� */
    motor->ecd = (uint16_t) (data[0] << 8 | data[1]);
    /* ת��ת�� */
    motor->speed_rpm = (int16_t) (data[2] << 8 | data[3]);
    /* ʵ��Ť�ص��� */
    motor->feedback_current = (int16_t) (data[4] << 8 | data[5]);
    /* ����¶� */
    motor->temperate = data[6];
}

/**
 * @brief ͨ��CAN����DJI����ĵ���
 * @param[in] can      CANͨ��
 * @param[in] can_id   ����֡ID
 * @param[in] data     ���͵�����
 */
void DJIMotor_Current_Set(FDCAN_TxFrame_TypeDef *DJIMotor_TxFrame, int16_t motor1, int16_t motor2, int16_t motor3,
                          int16_t motor4) {
    DJIMotor_TxFrame->Data[0] = motor1 >> 8;
    DJIMotor_TxFrame->Data[1] = motor1;
    DJIMotor_TxFrame->Data[2] = motor2 >> 8;
    DJIMotor_TxFrame->Data[3] = motor2;
    DJIMotor_TxFrame->Data[4] = motor3 >> 8;
    DJIMotor_TxFrame->Data[5] = motor3;
    DJIMotor_TxFrame->Data[6] = motor4 >> 8;
    DJIMotor_TxFrame->Data[7] = motor4;

    HAL_FDCAN_AddMessageToTxFifoQ(DJIMotor_TxFrame->hcan, &DJIMotor_TxFrame->Header, DJIMotor_TxFrame->Data);
}