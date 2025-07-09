/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "memorymap.h"
#include "spi.h"
#include "gpio.h"

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

static void MPU_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//#define BMI088_ACCEL_3G_SEN 0.0008974358974f    //这个数字我也不知道哪来的
#define BMI088_ACCEL_3G_SEN 0.00009155f

float BMI088_ACCEL_SEN = BMI088_ACCEL_3G_SEN;

float accelerometer[3];

uint8_t i = 0;

uint8_t buf[6] = {0, 0, 0, 0, 0, 0};

uint8_t pTxData;

uint8_t pRxData;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {

    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MPU Configuration--------------------------------------------------------*/
    MPU_Config();

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_SPI2_Init();
    /* USER CODE BEGIN 2 */

    /** 向地址0x7E处写入0xB6值，加速度计软件复位，使加速度计各个寄存器恢复为默认值 **/
    // 1.ACC_CS引脚置低电平，片选加速度计
    HAL_GPIO_WritePin(ACC_CS_GPIO_Port, ACC_CS_Pin, GPIO_PIN_RESET);

    // 2.将加速度计0x7E寄存器配置为写操作（把0x7E最高位置0）
    pTxData = (0x7E & 0x7F);
    HAL_SPI_Transmit(&hspi2, &pTxData, 1, 1000);
    while (HAL_SPI_GetState(&hspi2) == HAL_SPI_STATE_BUSY_TX);// 等待SPI发送完成

    // 3.向加速度计0x7E寄存器写入0xB6，软件复位
    pTxData = 0xB6;
    HAL_SPI_Transmit(&hspi2, &pTxData, 1, 1000);
    while (HAL_SPI_GetState(&hspi2) == HAL_SPI_STATE_BUSY_TX);// 等待SPI发送完成

    //等待软件复位完成
    HAL_Delay(1);

    // 4.ACC_CS引脚置高电平，取消片选加速度计
    HAL_GPIO_WritePin(ACC_CS_GPIO_Port, ACC_CS_Pin, GPIO_PIN_SET);

    /** 加速度计复位后默认是暂停模式，向加速度计0x7D寄存器写入0x04，使加速度计进入正常模式 **/
    // 1.ACC_CS引脚置低电平，片选加速度计
    HAL_GPIO_WritePin(ACC_CS_GPIO_Port, ACC_CS_Pin, GPIO_PIN_RESET);

    // 2.将加速度计0x7D寄存器配置为写操作（把0x7D最高位置0）
    pTxData = (0x7D & 0x7F);
    HAL_SPI_Transmit(&hspi2, &pTxData, 1, 1000);
    while (HAL_SPI_GetState(&hspi2) == HAL_SPI_STATE_BUSY_TX);// 等待SPI发送完成

    // 3.向加速度计0x7D寄存器写入0x04，使加速度计进入正常模式
    pTxData = 0x04;
    HAL_SPI_Transmit(&hspi2, &pTxData, 1, 1000);
    while (HAL_SPI_GetState(&hspi2) == HAL_SPI_STATE_BUSY_TX);    //等待SPI发送完成

    // 等待配置完成
    HAL_Delay(1);

    // 4.ACC_CS引脚置高电平，取消片选加速度计
    HAL_GPIO_WritePin(ACC_CS_GPIO_Port, ACC_CS_Pin, GPIO_PIN_SET);

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        /** 1.ACC_CS引脚置低电平，片选加速度计 **/
        HAL_GPIO_WritePin(ACC_CS_GPIO_Port, ACC_CS_Pin, GPIO_PIN_RESET);

        /** 2.将加速度计0x12寄存器配置为读操作（把0x12最高位置1）**/
        pTxData = (0x12 | 0x80);
        HAL_SPI_Transmit(&hspi2, &pTxData, 1, 1000);
        while (HAL_SPI_GetState(&hspi2) == HAL_SPI_STATE_BUSY_TX);// 等待SPI发送完成

        /** 3.接收加速度计0x12 ~ 0x17寄存器的值 **/
        // （1）无效值
        HAL_SPI_Receive(&hspi2, &pRxData, 1, 1000);
        while (HAL_SPI_GetState(&hspi2) == HAL_SPI_STATE_BUSY_RX);    //等待SPI接收完成

        // （2）接收加速度计0x12 ~ 0x17寄存器的值
        i = 0;
        while (i < 6) {
            HAL_SPI_Receive(&hspi2, &pRxData, 1, 1000);    //Bit #16-23，寄存器0x12的值，然后是寄存器0x13、0x14、0x15、0x16、0x17的值
            while (HAL_SPI_GetState(&hspi2) == HAL_SPI_STATE_BUSY_RX);    //等待SPI接收完成
            buf[i] = pRxData;
            i++;
        }
        HAL_GPIO_WritePin(ACC_CS_GPIO_Port, ACC_CS_Pin, GPIO_PIN_SET);    //PA4置1，取消片选加速度计
        accelerometer[0] = ((int16_t) ((buf[1]) << 8) | buf[0]) * BMI088_ACCEL_SEN;
        accelerometer[1] = ((int16_t) ((buf[3]) << 8) | buf[2]) * BMI088_ACCEL_SEN;
        accelerometer[2] = ((int16_t) ((buf[5]) << 8) | buf[4]) * BMI088_ACCEL_SEN;
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Supply configuration update enable
    */
    HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

    /** Configure the main internal regulator output voltage
    */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

    while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 2;
    RCC_OscInitStruct.PLL.PLLN = 40;
    RCC_OscInitStruct.PLL.PLLP = 1;
    RCC_OscInitStruct.PLL.PLLQ = 2;
    RCC_OscInitStruct.PLL.PLLR = 2;
    RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
    RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
    RCC_OscInitStruct.PLL.PLLFRACN = 0;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2
                                  | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
    RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* MPU Configuration */

void MPU_Config(void) {
    MPU_Region_InitTypeDef MPU_InitStruct = {0};

    /* Disables the MPU */
    HAL_MPU_Disable();

    /** Initializes and configures the Region and the memory to be protected
    */
    MPU_InitStruct.Enable = MPU_REGION_ENABLE;
    MPU_InitStruct.Number = MPU_REGION_NUMBER0;
    MPU_InitStruct.BaseAddress = 0x0;
    MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
    MPU_InitStruct.SubRegionDisable = 0x87;
    MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
    MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
    MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
    MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
    MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
    MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);
    /* Enables the MPU */
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
