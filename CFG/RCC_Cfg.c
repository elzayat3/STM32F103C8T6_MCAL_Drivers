#include "RCC_Cfg.h"

/**
 * @file RCC_Cfg.c
 * @brief RCC driver configuration source file for STM32F103C8T6.
 *
 * This file contains the RCC configuration objects used by RCC_Init().
 *
 * @author Abdelrahman Elzayat
 */

/**
 * @brief HSE configuration object.
 */
const HSE_Config_t hseConfig =
{
	.divider_factor = divided_by_2
};

/**
 * @brief PLL configuration object.
 */
const PLL_Config_t pllConfig =
{
	.source = HSE,
	.mul    = PLL_mul_by_4
};
