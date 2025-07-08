#ifndef _BSP_UART_H
#define _BSP_UART_H

#include <stdint-gcc.h>
#include <stdbool.h>

/** 帧头帧尾 **/
typedef enum {
    Head_1 = 0,
    Head_2 = 1,
    End_1 = 6,
    End_2 = 7
} Data_Format;

typedef enum {
    Init,
    Head_Success,
    Tail_Success,
    Check_Data
} Check_State;

extern uint8_t Data_Buffer[8];
extern uint8_t Data[4];

#endif
