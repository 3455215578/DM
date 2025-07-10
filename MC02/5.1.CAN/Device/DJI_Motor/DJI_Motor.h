#ifndef _DJI_MOTOR_H
#define _DJI_MOTOR_H

#include <stdint-gcc.h>
#include "bsp_can.h"

// �������ֵ�����Ӧ�Ƕ�
#define ECD360 8192
#define ECD180 4096
#define ECD90 2048
#define ECD45 1024

//���������
typedef struct {
    /* ʵ�ʵ���������� */
    int16_t last_ecd;       //��һ�εĵ������������ֵ
    uint16_t ecd;           //ת�ӻ�е�Ƕ�, �������������ֵ
    int16_t speed_rpm;      //ת��ת��, ���ת�٣�ÿ����ת����RPM��
    int16_t feedback_current;  //ʵ��Ť�ص���
    uint8_t temperate;      //����¶�

    /* �Զ������� */
    int32_t total_ecd;      //�����ת���ܱ�������ֵ
    uint16_t offset_ecd;    //�����У׼����ֵ

    int32_t round_cnt;      //�������������ת����Ȧ��
    int32_t out_round_cnt;  //����������ת����Ȧ��

} DJI_Motor_t;

void DJI_Round_Count(DJI_Motor_t *motor);

void DJI_Motor_Update_Data(DJI_Motor_t *motor, uint8_t *data);

void DJIMotor_Current_Set(FDCAN_TxFrame_TypeDef *DJIMotor_TxFrame, int16_t motor1, int16_t motor2, int16_t motor3,
                          int16_t motor4);

extern DJI_Motor_t dji_motor;

#endif