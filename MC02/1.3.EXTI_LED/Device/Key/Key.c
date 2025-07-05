#include "Key.h"
#include "WS2812.h"

bool Key_Press(void) {
    /** 由原理图上拉电阻可知，按键未按下时默认为高电平 **/
    if (HAL_GPIO_ReadPin(KEY_EXTI_GPIO_Port, KEY_EXTI_Pin) == GPIO_PIN_SET) {
        return false;
    } else {
        HAL_Delay(20);
        return true;
    }
}

/** 按键状态 默认为未按下 **/
bool key_state = false;

bool keep_flag = false;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == KEY_EXTI_Pin) {

        int r = 1;
        int g = 1;
        int b = 1;

        /** 获取按键状态 **/
        key_state = Key_Press();

        if (key_state == true) {
            /** 等待按键释放，避免多次触发keep_flag判断 **/
            while (Key_Press() == true);

            // 切换 keep_flag 的状态
            keep_flag = !keep_flag;
        }

        if (keep_flag == true) {
            r = g = b = 1;
        } else {
            r = g = b = 0;
        }

        /** 发送函数放在最后，通过改变参数发送 **/
        WS2812_Ctrl(r, g, b);
    }
}
