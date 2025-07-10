#ifndef _PID_H
#define _PID_H

#include <stdint-gcc.h>
#include "bsp_dwt.h"

typedef struct {

    /* P��I��D���� */
    float Kp;
    float Ki;
    float Kd;

    /* Ŀ��ֵ������ֵ�����ֵ */
    float Set;
    float Get;
    float Err;
    float Last_Err;

    /* P��I��D���ڵ���� */
    float Pout;
    float Iout;
    float Dout;


    /* PID����� */
    float Output;

    /* ����޷� */
    float MaxOut;

    /* ����������޷� */
    float IntegralLimit;


    uint32_t DWT_CNT;
    float dt;

} PID_t;

void PID_Init(PID_t *pid, float max_out, float intergral_limit, float kp, float Ki, float Kd);

float PID_Calculate(PID_t *pid, float get, float set);


#endif
