#include "Key.h"
#include "WS2812.h"

bool Key_Press(void) {
    /** ��ԭ��ͼ���������֪������δ����ʱĬ��Ϊ�ߵ�ƽ **/
    if (HAL_GPIO_ReadPin(KEY_EXTI_GPIO_Port, KEY_EXTI_Pin) == GPIO_PIN_SET) {
        return false;
    } else {
        HAL_Delay(20);
        return true;
    }
}

/** ����״̬ Ĭ��Ϊδ���� **/
bool key_state = false;

bool keep_flag = false;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == KEY_EXTI_Pin) {

        int r = 1;
        int g = 1;
        int b = 1;

        /** ��ȡ����״̬ **/
        key_state = Key_Press();

        if (key_state == true) {
            /** �ȴ������ͷţ������δ���keep_flag�ж� **/
            while (Key_Press() == true);

            // �л� keep_flag ��״̬
            keep_flag = !keep_flag;
        }

        if (keep_flag == true) {
            r = g = b = 1;
        } else {
            r = g = b = 0;
        }

        /** ���ͺ����������ͨ���ı�������� **/
        WS2812_Ctrl(r, g, b);
    }
}
