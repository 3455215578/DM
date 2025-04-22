#ifndef __BSP_CAN_H
#define __BSP_CAN_H

#include "fdcan.h"

typedef struct {
	
	FDCAN_HandleTypeDef 	*hcan;
    FDCAN_TxHeaderTypeDef   Header;
    uint8_t				    Data[8];
	
}FDCAN_TxFrame_TypeDef;

typedef struct {
	
	FDCAN_HandleTypeDef     *hcan;
    FDCAN_RxHeaderTypeDef   Header;
    uint8_t 			    Data[8];
	
} FDCAN_RxFrame_TypeDef;

void FDCAN1_FilterInit(void);

#endif
