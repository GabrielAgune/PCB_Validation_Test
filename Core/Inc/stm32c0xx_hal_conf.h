/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32c0xx_hal_conf.h
  * @author  MCD Application Team
  * @brief   HAL configuration template file.
  *          This file should be copied to the application folder and renamed
  *          to stm32c0xx_hal_conf.h.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32C0xx_HAL_CONF_H
#define STM32C0xx_HAL_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* ########################## Module Selection ############################## */
/**
  * @brief This is the list of modules to be used in the HAL driver
  */
#define HAL_MODULE_ENABLED
#define HAL_ADC_MODULE_ENABLED
/* #define HAL_CRC_MODULE_ENABLED   */
/* #define HAL_CRYP_MODULE_ENABLED   */
/* #define HAL_I2C_MODULE_ENABLED   */
/* #define HAL_I2S_MODULE_ENABLED   */
/* #define HAL_IWDG_MODULE_ENABLED   */
/* #define HAL_IRDA_MODULE_ENABLED   */
/* #define HAL_PCD_MODULE_ENABLED   */
/* #define HAL_HCD_MODULE_ENABLED   */
/* #define HAL_RNG_MODULE_ENABLED   */
/* #define HAL_RTC_MODULE_ENABLED   */
/* #define HAL_SMARTCARD_MODULE_ENABLED   */
/* #define HAL_SMBUS_MODULE_ENABLED   */
/* #define HAL_SPI_MODULE_ENABLED   */
#define HAL_TIM_MODULE_ENABLED
#define HAL_UART_MODULE_ENABLED
/* #define HAL_USART_MODULE_ENABLED   */
/* #define HAL_WWDG_MODULE_ENABLED   */
#define HAL_GPIO_MODULE_ENABLED
#define HAL_EXTI_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
/* ########################## Register Callbacks selection ############################## */
/**
  * @brief Set below the peripheral configuration  to "1U" to add the support
  *        of HAL callback registration/unregistration feature for the HAL
  *        driver(s). This allows user application to provide specific callback
  *        functions thanks to HAL_PPP_RegisterCallback() rather than overwriting
  *        the default weak callback functions (see each stm32c0xx_hal_ppp.h file
  *        for possible callback identifiers defined in HAL_PPP_CallbackIDTypeDef
  *        for each PPP peripheral).
  */
#define USE_HAL_ADC_REGISTER_CALLBACKS         0U  /* ADC register callback disabled      */
#define USE_HAL_I2C_REGISTER_CALLBACKS         0U  /* I2C register callback disabled      */
#define USE_HAL_IRDA_REGISTER_CALLBACKS        0U  /* IRDA register callback disabled     */
#define USE_HAL_I2S_REGISTER_CALLBACKS         0U  /* I2S register callback disabled      */
#define USE_HAL_IWDG_REGISTER_CALLBACKS        0U  /* IWDG register callback disabled     */
#define USE_HAL_RTC_REGISTER_CALLBACKS         0U /* RTC register callback disabled       */
#define USE_HAL_SMARTCARD_REGISTER_CALLBACKS   0U /* SMARTCARD register callback disabled */
#define USE_HAL_SMBUS_REGISTER_CALLBACKS       0U /* SMBUS register callback disabled     */
#define USE_HAL_SPI_REGISTER_CALLBACKS         0U /* SPI register callback disabled       */
#define USE_HAL_TIM_REGISTER_CALLBACKS         0U /* TIM register callback disabled       */
#define USE_HAL_UART_REGISTER_CALLBACKS        0U /* UART register callback disabled      */
#define USE_HAL_USART_REGISTER_CALLBACKS       0U /* USART register callback disabled     */
#define USE_HAL_WWDG_REGISTER_CALLBACKS        0U /* WWDG register callback disabled      */

/* ########################## Oscillator Values adaptation ####################*/
/**
  * @brief Adjust the value of External High Speed oscillator (HSE) used in your application.
  *        This value is used by the RCC HAL module to compute the system frequency
  *        (when HSE is used as system clock source, directly or through the PLL).
  */
#if !defined  (HSE_VALUE)
#define HSE_VALUE    (8000000U)         /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSE_STARTUP_TIMEOUT)
#define HSE_STARTUP_TIMEOUT    (100UL)         /*!< Time out for HSE start up, in ms */
#endif /* HSE_STARTUP_TIMEOUT */

/**
  * @brief Internal High Speed oscillator (HSI) value.
  *        This value is used by the RCC HAL module to compute the system frequency
  *        (when HSI is used as system clock source, directly or through the PLL).
  */
#if !defined  (HSI_VALUE)
#define HSI_VALUE    (48000000UL)            /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

/**
  * @brief Internal Low Speed oscillator (LSI) value.
  */
#if !defined  (LSI_VALUE)
#define LSI_VALUE  (32000UL)                /*!< LSI Typical Value in Hz*/
#endif /* LSI_VALUE */                      /*!< Value of the Internal Low Speed oscillator in Hz
The real value may vary depending on the variations
in voltage and temperature.*/
#if !defined  (LSI_STARTUP_TIME)
#define LSI_STARTUP_TIME    130UL      /*!< Time out for LSI start up, in ms */
#endif /* LSI_STARTUP_TIME */
/**
  * @brief External Low Speed oscillator (LSE) value.
  *        This value is used by the UART, RTC HAL module to compute the system frequency
  */
#if !defined  (LSE_VALUE)
#define LSE_VALUE    (32768UL)               /*!< Value of the External oscillator in Hz*/
#endif /* LSE_VALUE */

#if !defined (LSE_STARTUP_TIMEOUT)
#define LSE_STARTUP_TIMEOUT    (5000UL)      /*!< Time out for LSE start up, in ms */
#endif /* LSE_STARTUP_TIMEOUT */

/**
  * @brief External clock source for I2S1 peripheral
  *        This value is used by the RCC HAL module to compute the I2S1 clock source
  *        frequency.
  */
#if !defined  (EXTERNAL_I2S1_CLOCK_VALUE)
#define EXTERNAL_I2S1_CLOCK_VALUE    (12288000UL) /*!< Value of the I2S1 External clock source in Hz*/
#endif /* EXTERNAL_I2S1_CLOCK_VALUE */

/* Tip: To avoid modifying this file each time you need to use different HSE,
   ===  you can define the HSE value in your toolchain compiler preprocessor. */

/* ########################### System Configuration ######################### */
/**
  * @brief This is the HAL system configuration section
  */
#define  VDD_VALUE                    (3300UL)                                        /*!< Value of VDD in mv */
#define  TICK_INT_PRIORITY            3U /*!< tick interrupt priority */
#define  USE_RTOS                     0U
#define  PREFETCH_ENABLE              0U
#define  INSTRUCTION_CACHE_ENABLE     1U

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* Includes ------------------------------------------------------------------*/
/**
  * @brief Include modules header file
  */

#ifdef HAL_RCC_MODULE_ENABLED
  #include "stm32c0xx_hal_rcc.h"
#endif /* HAL_RCC_MODULE_ENABLED */

#ifdef HAL_GPIO_MODULE_ENABLED
  #include "stm32c0xx_hal_gpio.h"
#endif /* HAL_GPIO_MODULE_ENABLED */

#ifdef HAL_DMA_MODULE_ENABLED
  #include "stm32c0xx_hal_dma.h"
#endif /* HAL_DMA_MODULE_ENABLED */

#ifdef HAL_CORTEX_MODULE_ENABLED
  #include "stm32c0xx_hal_cortex.h"
#endif /* HAL_CORTEX_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
  #include "stm32c0xx_hal_adc.h"
  #include "stm32c0xx_hal_adc_ex.h"
#endif /* HAL_ADC_MODULE_ENABLED */

#ifdef HAL_CRC_MODULE_ENABLED
  #include "stm32c0xx_hal_crc.h"
#endif /* HAL_CRC_MODULE_ENABLED */

#ifdef HAL_EXTI_MODULE_ENABLED
#include "stm32c0xx_hal_exti.h"
#endif /* HAL_EXTI_MODULE_ENABLED */

#ifdef HAL_FLASH_MODULE_ENABLED
  #include "stm32c0xx_hal_flash.h"
#endif /* HAL_FLASH_MODULE_ENABLED */

#ifdef HAL_I2C_MODULE_ENABLED
 #include "stm32c0xx_hal_i2c.h"
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_I2S_MODULE_ENABLED
 #include "stm32c0xx_hal_i2s.h"
#endif /* HAL_I2S_MODULE_ENABLED */

#ifdef HAL_IRDA_MODULE_ENABLED
 #include "stm32c0xx_hal_irda.h"
#endif /* HAL_IRDA_MODULE_ENABLED */

#ifdef HAL_IWDG_MODULE_ENABLED
 #include "stm32c0xx_hal_iwdg.h"
#endif /* HAL_IWDG_MODULE_ENABLED */

#ifdef HAL_PWR_MODULE_ENABLED
 #include "stm32c0xx_hal_pwr.h"
#endif /* HAL_PWR_MODULE_ENABLED */

#ifdef HAL_RTC_MODULE_ENABLED
 #include "stm32c0xx_hal_rtc.h"
#endif /* HAL_RTC_MODULE_ENABLED */

#ifdef HAL_SMARTCARD_MODULE_ENABLED
 #include "stm32c0xx_hal_smartcard.h"
#endif /* HAL_SMARTCARD_MODULE_ENABLED */

#ifdef HAL_SMBUS_MODULE_ENABLED
 #include "stm32c0xx_hal_smbus.h"
#endif /* HAL_SMBUS_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
 #include "stm32c0xx_hal_spi.h"
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_TIM_MODULE_ENABLED
 #include "stm32c0xx_hal_tim.h"
#endif /* HAL_TIM_MODULE_ENABLED */

#ifdef HAL_UART_MODULE_ENABLED
 #include "stm32c0xx_hal_uart.h"
#endif /* HAL_UART_MODULE_ENABLED */

#ifdef HAL_USART_MODULE_ENABLED
 #include "stm32c0xx_hal_usart.h"
#endif /* HAL_USART_MODULE_ENABLED */

#ifdef HAL_WWDG_MODULE_ENABLED
 #include "stm32c0xx_hal_wwdg.h"
#endif /* HAL_WWDG_MODULE_ENABLED */

#ifdef HAL_PCD_MODULE_ENABLED
 #include "stm32c0xx_hal_pcd.h"
#endif /* HAL_PCD_MODULE_ENABLED */

#ifdef HAL_HCD_MODULE_ENABLED
 #include "stm32c0xx_hal_hcd.h"
#endif /* HAL_HCD_MODULE_ENABLED */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_param macro is used for functions parameters check.
  * @param  expr If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
#define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
void assert_failed(uint8_t *file, uint32_t line);
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif

#endif /* STM32C0xx_HAL_CONF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
