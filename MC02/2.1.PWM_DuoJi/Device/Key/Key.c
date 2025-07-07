#include "Key.h"

bool Key_Press(void) {
    /** 由原理图上拉电阻可知，按键未按下时默认为高电平 **/
    if (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == GPIO_PIN_SET) {
        return false;
    } else {
        HAL_Delay(20);
        return true;
    }
}
