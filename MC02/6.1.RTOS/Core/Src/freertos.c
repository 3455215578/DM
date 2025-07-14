/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "WS2812.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

int r = 0;
int g = 0;
int b = 0;

float Sin_Sign;

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId FlashHandle;
osThreadId BreathHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const *argument);

void StartFlashTask(void const *argument);

void StartBreathTask(void const *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize);

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize) {
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
    /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* definition and creation of defaultTask */
    osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
    defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

    /* definition and creation of Flash */
    osThreadDef(Flash, StartFlashTask, osPriorityNormal, 0, 128);
    FlashHandle = osThreadCreate(osThread(Flash), NULL);

    /* definition and creation of Breath */
    osThreadDef(Breath, StartBreathTask, osPriorityNormal, 0, 128);
    BreathHandle = osThreadCreate(osThread(Breath), NULL);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const *argument) {
    /* USER CODE BEGIN StartDefaultTask */
    /* Infinite loop */
    for (;;) {
        osDelay(1);
    }
    /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartFlashTask */
/**
* @brief Function implementing the Flash thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartFlashTask */
void StartFlashTask(void const *argument) {
    /* USER CODE BEGIN StartFlashTask */

    static int i = 0;

    /* Infinite loop */
    for (;;) {

        if (i % 2 == 0) {
            r = 10;
        } else if (i % 2 == 1) {
            r = 0;
        }

        i++;

        WS2812_Ctrl(r, g, b);
        osDelay(500); // 500ms
    }
    /* USER CODE END StartFlashTask */
}

/* USER CODE BEGIN Header_StartBreathTask */
/**
* @brief Function implementing the Breath thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartBreathTask */
void StartBreathTask(void const *argument) {
    /* USER CODE BEGIN StartBreathTask */

    static float i = 0.0f;

    /* Infinite loop */
    for (;;) {

        Sin_Sign = sin(i);

        if (Sin_Sign < 0) {
            Sin_Sign = 0;
        }

        i += 0.01f;

        if (i > 360.0f) {
            i = 0.0f;
        }

        g = 10 * Sin_Sign;

        WS2812_Ctrl(r, g, b);

        osDelay(5);
    }
    /* USER CODE END StartBreathTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
