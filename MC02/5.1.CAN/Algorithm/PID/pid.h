#ifndef _PID_H
#define _PID_H

#include <stdint-gcc.h>
#include "bsp_dwt.h"

typedef struct {

    /* P、I、D参数 */
    float Kp;
    float Ki;
    float Kd;

    /* 目标值、反馈值、误差值 */
    float Set;
    float Get;
    float Err;
    float Last_Err;

    /* P、I、D环节的输出 */
    float Pout;
    float Iout;
    float Dout;


    /* PID总输出 */
    float Output;

    /* 输出限幅 */
    float MaxOut;

    /* 积分项输出限幅 */
    float IntegralLimit;


    uint32_t DWT_CNT;
    float dt;

} PID_t;

void PID_Init(PID_t *pid, float max_out, float intergral_limit, float kp, float Ki, float Kd);

float PID_Calculate(PID_t *pid, float get, float set);


#endif
