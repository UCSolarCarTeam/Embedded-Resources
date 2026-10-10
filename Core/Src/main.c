/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gpio_training.h"
#include "i2c_training.h"
#include "spi_training.h"

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
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_ICACHE_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

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
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_ICACHE_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */



  uint8_t xyz_data[6] = {0};

  volatile int16_t accel_x = 0;
  volatile int16_t accel_y = 0;
  volatile int16_t accel_z = 0;

  volatile HAL_StatusTypeDef xyz_status = HAL_ERROR;

  /*
   * I2C TRAINING - EXERCISE 1
   *
   * Goal:
   * Check whether the STM32 can communicate with the
   * MC3479 accelerometer using I2C.
   *
   * I2C_Training_DeviceReady() checks whether a device
   * acknowledges its address on the I2C bus.
   *
   * The function returns:
   * HAL_OK      -> Device responded successfully.
   * HAL_ERROR   -> Communication failed.
   * HAL_BUSY    -> I2C peripheral is busy.
   * HAL_TIMEOUT -> Communication timed out.
   *
   * TODO:
   * 1. Locate the MC3479 in the board schematic.
   * 2. Identify its SDA and SCL connections.
   * 3. Find the device's I2C address in the datasheet.
   * 4. Shift the 7-bit address left by one for STM32 HAL.
   * 5. Call I2C_Training_DeviceReady() with that address.
   * 6. Use the debugger to inspect i2c_status.
   */

  volatile HAL_StatusTypeDef i2c_status = HAL_ERROR;

  // TODO: Call I2C_Training_DeviceReady()
  // and store the return value in i2c_status.





  /*
   * I2C TRAINING - EXERCISE 2
   *
   * Goal:
   * Read the Chip ID register of the MC3479 accelerometer.
   *
   * Every I2C device has an address that allows the STM32
   * to communicate with it.
   *
   * Many I2C devices also contain internal registers that
   * store configuration settings, measurements, and status.
   *
   * I2C_Training_ReadRegister() reads one byte from a
   * specified register inside an I2C device.
   *
   * Parameters:
   * device_address   -> I2C address shifted left by 1.
   * register_address -> Address of the register to read.
   * data             -> Pointer to store the received byte.
   *
   * TODO:
   * 1. Find the MC3479 Chip ID register in its datasheet.
   * 2. Identify its register address.
   * 3. Find the expected value stored in this register.
   * 4. Call I2C_Training_ReadRegister() using the
   *    correct device address and register address.
   * 5. Store the received byte in chip_id.
   * 6. Use the debugger to inspect read_status and chip_id.
   * 7. Compare the received value with the datasheet.
   */

  uint8_t chip_id = 0;
  HAL_StatusTypeDef read_status = HAL_ERROR;

  if (i2c_status == HAL_OK)
  {
      // TODO: Read the Chip ID register and store
      // the return status in read_status.
  }

  // Place a breakpoint here to inspect the results.
  __NOP();





  /*
   * I2C TRAINING - EXERCISE 3
   *
   * Goal:
   * Configure the MC3479 accelerometer to begin
   * measuring acceleration.
   *
   * I2C_Training_WriteRegister() writes one byte
   * of data to a register inside an I2C device.
   *
   * The MC3479 starts in a low-power state.
   * Before reading acceleration measurements,
   * we must enable its WAKE mode.
   *
   * Parameters:
   * device_address   -> I2C device address (shifted left by 1).
   * register_address -> Address of the register to write.
   * value            -> Byte to store in that register.
   *
   * TODO:
   * 1. Find the MODE register in the MC3479 datasheet.
   * 2. Identify its register address.
   * 3. Determine which value enables WAKE mode.
   * 4. Call I2C_Training_WriteRegister() using the
   *    correct device address, register, and value.
   * 5. Store the returned HAL status in write_status.
   * 6. Use the debugger to check if the write succeeded.
   *
   * NOTE:
   * HAL_OK means the I2C write completed successfully.
   * It does not independently prove the sensor entered
   * the requested operating mode.
   */

  HAL_StatusTypeDef write_status = HAL_ERROR;

  if (read_status == HAL_OK && chip_id == 0xA4)
  {
      // TODO: Write the value that enables WAKE mode.
  }

  // Place a breakpoint here.
  __NOP();







  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {



	  /*
	   * TODO:
	   * 1. Complete GPIO_Training_Toggle() in gpio_training.c.
	   * 2. Uncomment the two lines below.
	   * 3. Observe the LED blinking.
	   * 4. Change the delay to make it blink faster or slower.
	   *
	   * NOTE:
	   * Comment out GPIO Exercise 2 while testing this exercise.
	   */

	  // GPIO_Training_Toggle();
	  // HAL_Delay(500);





      /*
       * GPIO TRAINING - EXERCISE 2
       *
       * Goal: Use a GPIO input to control the green LED.
       *
       * GPIO_Training_ReadInput() returns:
       * GPIO_PIN_SET   -> HIGH
       * GPIO_PIN_RESET -> LOW
       *
       * TODO:
       * 1. Complete GPIO_Training_ReadInput().
       * 2. Read the input and store its state.
       * 3. Complete the if/else statement using the
       *    SetHigh() and SetLow() training functions.
       * 4. Test the LED by changing the input state.
       *
       * NOTE:
       * Comment out Exercise 1 before running this exercise.
       */


	  GPIO_PinState input_state = GPIO_PIN_RESET;

	  // TODO: Read the GPIO input using GPIO_Training_ReadInput()
	  // and store the returned value in input_state.

	  if (input_state == GPIO_PIN_SET)
	  {
	      // TODO: Turn the LED ON using the appropriate function.
	  }
	  else
	  {
	      // TODO: Turn the LED OFF using the appropriate function.
	  }

	  HAL_Delay(10);








      /*
       * I2C TRAINING - EXERCISE 4
       *
       * Goal:
       * Read X, Y, and Z acceleration data from the MC3479.
       *
       * The MC3479 stores each measurement as a signed
       * 16-bit number across two consecutive registers.
       *
       * I2C_Training_ReadBytes() allows multiple register
       * values to be read in one I2C transaction.
       *
       * The six bytes are stored in xyz_data[]:
       *
       * xyz_data[0] -> X-axis LSB
       * xyz_data[1] -> X-axis MSB
       * xyz_data[2] -> Y-axis LSB
       * xyz_data[3] -> Y-axis MSB
       * xyz_data[4] -> Z-axis LSB
       * xyz_data[5] -> Z-axis MSB
       *
       * TODO:
       * 1. Make sure the MC3479 has entered WAKE mode.
       * 2. Identify the first acceleration data register.
       * 3. Read all six bytes using I2C_Training_ReadBytes().
       * 4. Combine the LSB and MSB for each axis.
       * 5. Store the results in accel_x, accel_y and accel_z.
       * 6. Use the debugger to observe the measurements.
       * 7. Move the board and observe how the values change.
       *
       * NOTE:
       * Only process the received data if the I2C read
       * returned HAL_OK.
       *
       * /*
       * IMPORTANT:
       * Exercises 1, 2, and 3 must be completed before this
       * exercise can work.
       *
       * The accelerometer must first be detected, its
       * Chip ID verified, and WAKE mode enabled.
       */

      if (write_status == HAL_OK)
      {
          // TODO: Read the six acceleration bytes.

          if (xyz_status == HAL_OK)
          {
              // TODO: Combine bytes into accel_x, accel_y, accel_z.
          }
      }

      HAL_Delay(100);







      /*
       * SPI TRAINING - EXERCISE 1
       *
       * Goal:
       * Read the IODIRA register from the MCP23S17
       * I/O expander using SPI.
       *
       * IODIRA determines whether each GPA pin
       * operates as an input or an output.
       *
       * A bit value of 1 configures the pin as input.
       * A bit value of 0 configures the pin as output.
       *
       * After a hardware reset, the IODIRA register
       * should contain 0xFF (all eight pins are inputs).
       *
       * TODO:
       * 1. Locate the MCP23S17 in the schematic.
       * 2. Identify its SPI and Chip Select connections.
       * 3. Find the IODIRA register address in the datasheet.
       * 4. Complete SPI_Training_ReadRegister().
       * 5. Call SPI_Training_ReadRegister() using the
       *    correct register address.
       * 6. Store the return status in spi_status.
       * 7. Use the debugger to inspect spi_status
       *    and iodira_value.
       * 8. Compare the received value with the datasheet.
       *
       * NOTE:
       * The expected value of 0xFF assumes the MCP23S17
       * has been reset and not configured previously.
       */

      uint8_t iodira_value = 0;
      HAL_StatusTypeDef spi_status = HAL_ERROR;

      // TODO: Read the IODIRA register.

      // Place a breakpoint here.
      __NOP();








    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_CSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV2;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.CSIState = RCC_CSI_ON;
  RCC_OscInitStruct.CSICalibrationValue = RCC_CSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLL1_SOURCE_CSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 32;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1_VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the programming delay
  */
  __HAL_FLASH_SET_PROGRAM_DELAY(FLASH_PROGRAMMING_DELAY_0);
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.SamplingMode = ADC_SAMPLING_MODE_NORMAL;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00707CBB;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief ICACHE Initialization Function
  * @param None
  * @retval None
  */
static void MX_ICACHE_Init(void)
{

  /* USER CODE BEGIN ICACHE_Init 0 */

  /* USER CODE END ICACHE_Init 0 */

  /* USER CODE BEGIN ICACHE_Init 1 */

  /* USER CODE END ICACHE_Init 1 */

  /** Enable instruction cache in 1-way (direct mapped cache)
  */
  if (HAL_ICACHE_ConfigAssociativityMode(ICACHE_1WAY) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_ICACHE_Enable() != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ICACHE_Init 2 */

  /* USER CODE END ICACHE_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_BYPASS;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 0x7;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  hspi2.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi2.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi2.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi2.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi2.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi2.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi2.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  hspi2.Init.ReadyMasterManagement = SPI_RDY_MASTER_MANAGEMENT_INTERNALLY;
  hspi2.Init.ReadyPolarity = SPI_RDY_POLARITY_HIGH;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Z_nRESET_Pin|Z_SPI_nCS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Z_nRESET_Pin Z_SPI_nCS_Pin */
  GPIO_InitStruct.Pin = Z_nRESET_Pin|Z_SPI_nCS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};
  MPU_Attributes_InitTypeDef MPU_AttributesInit = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region 0 and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x08FFF000;
  MPU_InitStruct.LimitAddress = 0x08FFFFFF;
  MPU_InitStruct.AttributesIndex = MPU_ATTRIBUTES_NUMBER0;
  MPU_InitStruct.AccessPermission = MPU_REGION_ALL_RO;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Attribute 0 and the memory to be protected
  */
  MPU_AttributesInit.Number = MPU_ATTRIBUTES_NUMBER0;
  MPU_AttributesInit.Attributes = INNER_OUTER(MPU_NOT_CACHEABLE);

  HAL_MPU_ConfigMemoryAttributes(&MPU_AttributesInit);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
