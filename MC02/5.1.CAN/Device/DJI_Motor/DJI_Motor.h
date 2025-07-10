#ifndef _DJI_MOTOR_H
#define _DJI_MOTOR_H

#include <stdint-gcc.h>
#include "bsp_can.h"

// 电机编码值与其对应角度
#define ECD360 8192
#define ECD180 4096
#define ECD90 2048
#define ECD45 1024

//电机的数据
typedef struct {
    /* 实际电机反馈数据 */
    int16_t last_ecd;       //上一次的电机编码器计数值
    uint16_t ecd;           //转子机械角度, 电机编码器计数值
    int16_t speed_rpm;      //转子转速, 电机转速（每分钟转数，RPM）
    int16_t feedback_current;  //实际扭矩电流
    uint8_t temperate;      //电机温度

    /* 自定义数据 */
    int32_t total_ecd;      //电机旋转的总编码器数值
    uint16_t offset_ecd;    //电机的校准编码值

    int32_t round_cnt;      //电机编码器端旋转的总圈数
    int32_t out_round_cnt;  //电机输出端旋转的总圈数

} DJI_Motor_t;

void DJI_Round_Count(DJI_Motor_t *motor);

void DJI_Motor_Update_Data(DJI_Motor_t *motor, uint8_t *data);

void DJIMotor_Current_Set(FDCAN_TxFrame_TypeDef *DJIMotor_TxFrame, int16_t motor1, int16_t motor2, int16_t motor3,
                          int16_t motor4);

extern DJI_Motor_t dji_motor;

#endif