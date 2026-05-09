#ifndef RCC_CFG_H_
#define RCC_CFG_H_

/**
 * @file RCC_Cfg.h
 * @brief RCC driver configuration file for STM32F103C8T6.
 *
 * This file contains user-configurable parameters and external
 * configuration objects used by the RCC driver.
 *
 * @author Abdelrahman Elzayat
 */

#include "RCC_Int.h"

/**
 * @def RCC_TIMEOUT
 * @brief Timeout value used while waiting for RCC ready flags.
 *
 * This value is used to prevent infinite blocking while waiting for
 * clock sources such as HSI, HSE, or PLL to become ready.
 *
 * @note Increase this value if the external oscillator needs more time
 *       to stabilize.
 */
#define RCC_TIMEOUT    1000UL

/**
 * @brief External HSE configuration object.
 *
 * This object contains the HSE divider configuration used when HSE
 * is selected as PLL input source.
 */
extern const HSE_Config_t hseConfig;

/**
 * @brief External PLL configuration object.
 *
 * This object contains the PLL source and multiplication factor
 * configuration used by RCC_Init().
 */
extern const PLL_Config_t pllConfig;

#endif /* RCC_CFG_H_ */
