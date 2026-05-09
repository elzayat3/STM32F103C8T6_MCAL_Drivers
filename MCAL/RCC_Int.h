#ifndef RCC_INT_H_
#define RCC_INT_H_

/**
 * @file RCC_Int.h
 * @brief Reset and Clock Control (RCC) driver interface for STM32F103C8T6.
 *
 * This file contains the public types and APIs used to control:
 * - Clock source status.
 * - System clock source selection.
 * - Peripheral clock enable/disable on AHB, APB1, and APB2 buses.
 *
 * It also contains the configuration types used by RCC_Cfg.c for:
 * - HSE divider configuration.
 * - PLL source and multiplication factor.
 *
 * @note This driver is written specifically for STM32F103C8T6 Blue Pill.
 *
 * @author Abdelrahman Elzayat
 */

#include "Std_Types.h"

/*========================================================================================
 * Clock Source Types
 *========================================================================================*/

/**
 * @enum Clock_t
 * @brief Defines the available clock sources.
 */
typedef enum
{
	HSIk = 0u, /**< High Speed Internal oscillator */
	HSEk,      /**< High Speed External oscillator */
	PLLk       /**< Phase Locked Loop clock */
} Clock_t;

/**
 * @enum Status_t
 * @brief Defines clock source status.
 */
typedef enum
{
	OFF = 0u, /**< Disable clock source */
	ON        /**< Enable clock source */
} Status_t;


/*========================================================================================
 * AHB Peripheral Clock Types
 *========================================================================================*/

/**
 * @enum AHB_Peripheral_t
 * @brief Defines AHB peripheral clock enable bit positions in RCC_AHBENR.
 */
typedef enum
{
	pDMA1  = 0u, /**< DMA1 clock enable bit */
	pFLITF = 4u, /**< Flash interface clock enable bit */
	pCRC   = 6u  /**< CRC clock enable bit */
} AHB_Peripheral_t;


/*========================================================================================
 * APB1 Peripheral Clock Types
 *========================================================================================*/

/**
 * @enum APB1_Peripheral_t
 * @brief Defines APB1 peripheral clock enable bit positions in RCC_APB1ENR.
 *
 * @note APB1 clock must not exceed 36 MHz.
 */
typedef enum
{
	pTIM2   = 0u,  /**< TIM2 clock enable bit */
	pTIM3   = 1u,  /**< TIM3 clock enable bit */
	pTIM4   = 2u,  /**< TIM4 clock enable bit */

	pWWDG   = 11u, /**< Window Watchdog clock enable bit */
	pSPI2   = 14u, /**< SPI2 clock enable bit */

	pUSART2 = 17u, /**< USART2 clock enable bit */
	pUSART3 = 18u, /**< USART3 clock enable bit */

	pI2C1   = 21u, /**< I2C1 clock enable bit */
	pI2C2   = 22u, /**< I2C2 clock enable bit */
	pUSB    = 23u, /**< USB clock enable bit */
	pCAN    = 25u, /**< CAN clock enable bit */

	pBKP    = 27u, /**< Backup interface clock enable bit */
	pPWR    = 28u  /**< Power interface clock enable bit */
} APB1_Peripheral_t;


/*========================================================================================
 * APB2 Peripheral Clock Types
 *========================================================================================*/

/**
 * @enum APB2_Peripheral_t
 * @brief Defines APB2 peripheral clock enable bit positions in RCC_APB2ENR.
 */
typedef enum
{
	pAFIO   = 0u,  /**< Alternate Function I/O clock enable bit */

	pGPIOA  = 2u,  /**< GPIOA clock enable bit */
	pGPIOB  = 3u,  /**< GPIOB clock enable bit */
	pGPIOC  = 4u,  /**< GPIOC clock enable bit */
	pGPIOD  = 5u,  /**< GPIOD clock enable bit */

	pADC1   = 9u,  /**< ADC1 clock enable bit */
	pADC2   = 10u, /**< ADC2 clock enable bit */
	pTIM1   = 11u, /**< TIM1 clock enable bit */
	pSPI1   = 12u, /**< SPI1 clock enable bit */
	pUSART1 = 14u  /**< USART1 clock enable bit */
} APB2_Peripheral_t;


/*========================================================================================
 * PLL Configuration Types
 *========================================================================================*/

/**
 * @enum PLL_Mul_t
 * @brief Defines PLL multiplication factors.
 *
 * These values map directly to PLLMUL bits in RCC_CFGR.
 *
 * @note PLL output frequency must not exceed 72 MHz.
 */
typedef enum
{
	PLL_mul_by_2 = 0u, /**< PLL input clock multiplied by 2 */
	PLL_mul_by_3,     /**< PLL input clock multiplied by 3 */
	PLL_mul_by_4,     /**< PLL input clock multiplied by 4 */
	PLL_mul_by_5,     /**< PLL input clock multiplied by 5 */
	PLL_mul_by_6,     /**< PLL input clock multiplied by 6 */
	PLL_mul_by_7,     /**< PLL input clock multiplied by 7 */
	PLL_mul_by_8,     /**< PLL input clock multiplied by 8 */
	PLL_mul_by_9,     /**< PLL input clock multiplied by 9 */
	PLL_mul_by_10,    /**< PLL input clock multiplied by 10 */
	PLL_mul_by_11,    /**< PLL input clock multiplied by 11 */
	PLL_mul_by_12,    /**< PLL input clock multiplied by 12 */
	PLL_mul_by_13,    /**< PLL input clock multiplied by 13 */
	PLL_mul_by_14,    /**< PLL input clock multiplied by 14 */
	PLL_mul_by_15,    /**< PLL input clock multiplied by 15 */
	PLL_mul_by_16     /**< PLL input clock multiplied by 16 */
} PLL_Mul_t;

/**
 * @enum PLL_Source_t
 * @brief Defines PLL input clock source.
 */
typedef enum
{
	HSI = 0u, /**< HSI oscillator divided by 2 selected as PLL input */
	HSE       /**< HSE oscillator selected as PLL input */
} PLL_Source_t;

/**
 * @enum HSE_divider_t
 * @brief Defines HSE divider when HSE is used as PLL input.
 */
typedef enum
{
	not_divided = 0u, /**< HSE clock is not divided before PLL input */
	divided_by_2     /**< HSE clock is divided by 2 before PLL input */
} HSE_divider_t;

/**
 * @struct HSE_Config_t
 * @brief HSE configuration structure.
 *
 * This structure is used by RCC_Cfg.c to configure the HSE divider
 * when HSE is selected as PLL input source.
 */
typedef struct
{
	HSE_divider_t divider_factor; /**< HSE divider factor for PLL input */
} HSE_Config_t;

/**
 * @struct PLL_Config_t
 * @brief PLL configuration structure.
 *
 * This structure is used by RCC_Cfg.c to configure PLL source and
 * multiplication factor.
 */
typedef struct
{
	PLL_Source_t source; /**< PLL input clock source */
	PLL_Mul_t    mul;    /**< PLL multiplication factor */
} PLL_Config_t;


/*========================================================================================
 * RCC APIs
 *========================================================================================*/

/**
 * @brief Initializes RCC based on predefined configuration.
 *
 * This function initializes the RCC module using the configuration objects
 * defined in RCC_Cfg.c.
 *
 * Initialization sequence:
 * - Enables HSI as a safe temporary system clock.
 * - Switches system clock temporarily to HSI.
 * - Disables PLL before changing PLL configuration.
 * - Enables the selected PLL source clock.
 * - Configures HSE divider and PLL settings.
 * - Enables PLL.
 * - Switches system clock to PLL.
 *
 * @retval OK RCC initialized successfully.
 * @retval TIMEOUT A clock source or system clock switch did not complete.
 * @retval OUT_OF_RANGE Invalid clock source or status was detected.
 */
error_t RCC_Init(void);

/**
 * @brief Enables or disables a specific clock source.
 *
 * @param clk Clock source selected from @ref Clock_t.
 * @param status Required clock status selected from @ref Status_t.
 *
 * @retval OK Clock source status changed successfully.
 * @retval TIMEOUT Clock source did not reach the requested state.
 * @retval OUT_OF_RANGE Invalid clock source or status.
 */
error_t RCC_SetClockStatus(Clock_t clk, Status_t status);

/**
 * @brief Selects the system clock source.
 *
 * @param clk System clock source selected from @ref Clock_t.
 *
 * @retval OK System clock source selected successfully.
 * @retval TIMEOUT System clock switch did not complete.
 * @retval OUT_OF_RANGE Invalid clock source.
 */
error_t RCC_SetSystemClock(Clock_t clk);

/**
 * @brief Enables clock for an AHB peripheral.
 *
 * @param periph AHB peripheral selected from @ref AHB_Peripheral_t.
 *
 * @return void
 */
void RCC_AHB_EnableClock(AHB_Peripheral_t periph);

/**
 * @brief Disables clock for an AHB peripheral.
 *
 * @param periph AHB peripheral selected from @ref AHB_Peripheral_t.
 *
 * @return void
 */
void RCC_AHB_DisableClock(AHB_Peripheral_t periph);

/**
 * @brief Enables clock for an APB1 peripheral.
 *
 * @param periph APB1 peripheral selected from @ref APB1_Peripheral_t.
 *
 * @return void
 */
void RCC_APB1_EnableClock(APB1_Peripheral_t periph);

/**
 * @brief Disables clock for an APB1 peripheral.
 *
 * @param periph APB1 peripheral selected from @ref APB1_Peripheral_t.
 *
 * @return void
 */
void RCC_APB1_DisableClock(APB1_Peripheral_t periph);

/**
 * @brief Enables clock for an APB2 peripheral.
 *
 * @param periph APB2 peripheral selected from @ref APB2_Peripheral_t.
 *
 * @return void
 */
void RCC_APB2_EnableClock(APB2_Peripheral_t periph);

/**
 * @brief Disables clock for an APB2 peripheral.
 *
 * @param periph APB2 peripheral selected from @ref APB2_Peripheral_t.
 *
 * @return void
 */
void RCC_APB2_DisableClock(APB2_Peripheral_t periph);

#endif /* RCC_INT_H_ */
