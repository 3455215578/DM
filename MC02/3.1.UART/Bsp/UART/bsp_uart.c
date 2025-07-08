#include "bsp_uart.h"

// 不要include "stm32h7xx_hal_uart.h"
#include "usart.h"


/** 帧头帧尾定义 **/
uint8_t format[] = {0xAA, 0xCC, 0xEE, 0xFF};

Check_State receive_state = Init;

uint8_t Data_Buffer[8];

uint8_t Data[4] = {0};

/** 0xAA 0xCC 数据字节1 数据字节2 数据字节3 数据字节4（默认0x00） 0xEE 0xFF **/
// 数据字节1、2、3分别用于控制红绿蓝灯，0x00灭，0x01亮

void UART_Data_Check(void) {

    /** 检测帧头 **/
    if (receive_state == Init) {
        if (Data_Buffer[Head_1] == 0xAA) {
            if (Data_Buffer[Head_2] == 0xCC) {
                receive_state = Head_Success;
            }
        } else {

        }
    }

    /** 过帧头检测后再检测帧尾 **/
    if (receive_state == Head_Success) {
        if (Data_Buffer[End_1] == 0xEE) {
            if (Data_Buffer[End_2] == 0xFF) {
                receive_state = Tail_Success;
            }
        } else {

        }
    }

    /** 检测数据 **/
    if (receive_state == Tail_Success) {
        Data[0] = Data_Buffer[2];
        Data[1] = Data_Buffer[3];
        Data[2] = Data_Buffer[4];
        Data[3] = Data_Buffer[5];

        receive_state = Init;
    }


}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

    if (huart == &huart1) {

        UART_Data_Check();

        HAL_UART_Receive_IT(&huart1, Data_Buffer, sizeof(Data_Buffer));
    }

}