#ifndef _BSP_CAN_H
#define _BSP_CAN_H

#include <stdint-gcc.h>
#include "fdcan.h"

typedef struct {

    FDCAN_HandleTypeDef *hcan;
    FDCAN_TxHeaderTypeDef Header;
    uint8_t Data[8];

} FDCAN_TxFrame_TypeDef;

typedef struct {

    FDCAN_HandleTypeDef *hcan;
    FDCAN_RxHeaderTypeDef Header;
    uint8_t Data[8];

} FDCAN_RxFrame_TypeDef;

extern FDCAN_TxFrame_TypeDef DJIMotor_TxFrame;

extern FDCAN_RxFrame_TypeDef FDCAN1_RxFrame;


void FDCAN_FilterInit(void);

#endif
