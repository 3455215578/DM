#include "Key.h"

bool Key_Press(void) {
    /** ��ԭ��ͼ���������֪������δ����ʱĬ��Ϊ�ߵ�ƽ **/
    if (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == GPIO_PIN_SET) {
        return false;
    } else {
        HAL_Delay(20);
        return true;
    }
}
