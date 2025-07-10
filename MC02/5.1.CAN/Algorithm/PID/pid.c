#include "pid.h"

/** 绝对值限幅 **/
static void abs_limit(float *a, float ABS_MAX) {
    if (*a > ABS_MAX)
        *a = ABS_MAX;
    if (*a < -ABS_MAX)
        *a = -ABS_MAX;
}

/**
 * @brief          PID初始化   PID initialize
 * @param[in]      PID结构体   PID structure
 * @param[in]      略
 * @retval         返回空      null
 */
void PID_Init(PID_t *pid, float max_out, float intergral_limit,
              float kp, float Ki, float Kd) {
    pid->IntegralLimit = intergral_limit;
    pid->MaxOut = max_out;

    pid->Kp = kp;
    pid->Ki = Ki;
    pid->Kd = Kd;

    pid->Err = 0;
    pid->Last_Err = 0;

    pid->Set = 0;
    pid->Get = 0;

    pid->Pout = 0;
    pid->Iout = 0;
    pid->Dout = 0;
    pid->Output = 0;

    // DWT定时器计数变量清零
    pid->DWT_CNT = 0;


}

/**
 * @brief          PID计算
 * @param[in]      PID结构体
 * @param[in]      测量值
 * @param[in]      期望值
 * @retval         返回空
 */
float PID_Calculate(PID_t *pid, float get, float set) {

    pid->dt = DWT_GetDeltaT((void *) &pid->DWT_CNT);

    pid->Get = get;
    pid->Set = set;
    pid->Err = pid->Set - pid->Get;

    pid->Pout = pid->Kp * pid->Err;
    pid->Iout += pid->Ki * pid->Err;
    pid->Dout = pid->Kd * (pid->Err - pid->Last_Err) / pid->dt;

    abs_limit(&(pid->Iout), pid->IntegralLimit);

    pid->Output = pid->Pout + pid->Iout + pid->Dout;

    abs_limit(&(pid->Output), pid->MaxOut);

    pid->Last_Err = pid->Err;

    return pid->Output;
}
