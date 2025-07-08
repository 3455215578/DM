#include "bsp_uart.h"

// ��Ҫinclude "stm32h7xx_hal_uart.h"
#include "usart.h"


/** ֡ͷ֡β���� **/
uint8_t format[] = {0xAA, 0xCC, 0xEE, 0xFF};

Check_State receive_state = Init;

uint8_t Data_Buffer[8];

uint8_t Data[4] = {0};

/** 0xAA 0xCC �����ֽ�1 �����ֽ�2 �����ֽ�3 �����ֽ�4��Ĭ��0x00�� 0xEE 0xFF **/
// �����ֽ�1��2��3�ֱ����ڿ��ƺ������ƣ�0x00��0x01��

void UART_Data_Check(void) {

    /** ���֡ͷ **/
    if (receive_state == Init) {
        if (Data_Buffer[Head_1] == 0xAA) {
            if (Data_Buffer[Head_2] == 0xCC) {
                receive_state = Head_Success;
            }
        } else {

        }
    }

    /** ��֡ͷ�����ټ��֡β **/
    if (receive_state == Head_Success) {
        if (Data_Buffer[End_1] == 0xEE) {
            if (Data_Buffer[End_2] == 0xFF) {
                receive_state = Tail_Success;
            }
        } else {

        }
    }

    /** ������� **/
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