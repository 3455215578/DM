#include "Key.h"

bool Key_Press(void) {
    /** 由原理图上拉电阻可知，按键未按下时默认为高电平 **/
    if (HAL_GPIO_ReadPin(USER_KEY_GPIO_Port, USER_KEY_Pin) == GPIO_PIN_SET) {
        return false;
    } else {
        /** 软件消抖 **/
        HAL_Delay(20);
        return true;
    }
}
