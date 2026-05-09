/**
 * @file RCC_Program.c
 * @brief RCC driver implementation for STM32F103C8T6.
 *
 * This file contains the implementation of RCC APIs used to control
 * clock sources, system clock selection, PLL configuration, HSE divider,
 * and peripheral clock enable/disable.
 *
 * @author Abdelrahman Elzayat
 */

#include <stdint.h>

#include "Std_Types.h"
#include "Mem_Map.h"
#include "RCC_Int.h"
#include "RCC_Private.h"
#include "RCC_Cfg.h"


/*========================================================================================
 * Private Function Prototypes
 *========================================================================================*/

/**
 * @brief Configures the HSE divider used as PLL input.
 *
 * This function reads the HSE configuration from the global constant
 * configuration object hseConfig.
 *
 * @return void
 *
 * @note PLL must be disabled before calling this function.
 */
static void RCC_HSE_Config(void);

/**
 * @brief Configures PLL source and multiplication factor.
 *
 * This function reads the PLL configuration from the global constant
 * configuration object pllConfig.
 *
 * @return void
 *
 * @note PLL must be disabled before calling this function.
 */
static void RCC_PLL_Config(void);


/*========================================================================================
 * Public Function Implementations
 *========================================================================================*/


error_t RCC_Init(void)
{
	error_t Local_Status = OK;

	Local_Status = RCC_SetClockStatus(HSIk, ON);

	if (Local_Status == OK)
	{
		Local_Status = RCC_SetSystemClock(HSIk);
	}
	else
	{
		/* Do nothing */
	}

	if (Local_Status == OK)
	{
		Local_Status = RCC_SetClockStatus(PLLk, OFF);
	}
	else
	{
		/* Do nothing */
	}

	if (Local_Status == OK)
	{
		if (pllConfig.source == HSE)
		{
			Local_Status = RCC_SetClockStatus(HSEk, ON);
		}
		else
		{
			Local_Status = RCC_SetClockStatus(HSIk, ON);
		}
	}
	else
	{
		/* Do nothing */
	}

	if (Local_Status == OK)
	{
		RCC_HSE_Config();

		RCC_PLL_Config();

		Local_Status = RCC_SetClockStatus(PLLk, ON);
	}
	else
	{
		/* Do nothing */
	}

	if (Local_Status == OK)
	{
		Local_Status = RCC_SetSystemClock(PLLk);
	}
	else
	{
		/* Do nothing */
	}

	return Local_Status;
}


error_t RCC_SetClockStatus(Clock_t clk, Status_t status)
{
	error_t Local_Status = OK;
	uint32_t Local_EnableBit = 0u;
	uint32_t Local_ReadyBit = 0u;
	uint32_t Local_Timeout = RCC_TIMEOUT;
	uint32_t Local_ExpectedReadyValue = RCC_READY_FLAG_CLEAR;

	if ((clk > PLLk) || (status > ON))
	{
		Local_Status = OUT_OF_RANGE;
	}
	else
	{
		switch (clk)
		{
			case HSIk:
				Local_EnableBit = RCC_CR_HSION_BIT;
				Local_ReadyBit  = RCC_CR_HSIRDY_BIT;
				break;

			case HSEk:
				Local_EnableBit = RCC_CR_HSEON_BIT;
				Local_ReadyBit  = RCC_CR_HSERDY_BIT;
				break;

			case PLLk:
				Local_EnableBit = RCC_CR_PLLON_BIT;
				Local_ReadyBit  = RCC_CR_PLLRDY_BIT;
				break;

			default:
				Local_Status = OUT_OF_RANGE;
				break;
		}

		if (Local_Status == OK)
		{
			if (status == ON)
			{
				SET_BIT(RCC->CR, Local_EnableBit);
				Local_ExpectedReadyValue = RCC_READY_FLAG_SET;
			}
			else
			{
				CLR_BIT(RCC->CR, Local_EnableBit);
				Local_ExpectedReadyValue = RCC_READY_FLAG_CLEAR;
			}

			while ((GET_BIT(RCC->CR, Local_ReadyBit) != Local_ExpectedReadyValue) && (Local_Timeout > 0u))
			{
				Local_Timeout--;
			}

			if (Local_Timeout == 0u)
			{
				Local_Status = TIMEOUT;
			}
			else
			{
				Local_Status = OK;
			}
		}
	}

	return Local_Status;
}



error_t RCC_SetSystemClock(Clock_t clk)
{
	error_t Local_Status = OK;
	uint32_t Local_ClockValue = 0u;
	uint32_t Local_Timeout = RCC_TIMEOUT;

	if (clk > PLLk)
	{
		Local_Status = OUT_OF_RANGE;
	}
	else
	{
		switch (clk)
		{
			case HSIk:
				Local_ClockValue = RCC_SYSCLK_HSI;
				break;

			case HSEk:
				Local_ClockValue = RCC_SYSCLK_HSE;
				break;

			case PLLk:
				Local_ClockValue = RCC_SYSCLK_PLL;
				break;

			default:
				Local_Status = OUT_OF_RANGE;
				break;
		}

		if (Local_Status == OK)
		{
			RCC->CFGR &= ~RCC_CFGR_SW_MASK;
			RCC->CFGR |=  (Local_ClockValue << RCC_CFGR_SW_SHIFT);

			while ((((RCC->CFGR & RCC_CFGR_SWS_MASK) >> RCC_CFGR_SWS_SHIFT) != Local_ClockValue) &&(Local_Timeout > 0u))
			{
				Local_Timeout--;
			}

			if (Local_Timeout == 0u)
			{
				Local_Status = TIMEOUT;
			}
			else
			{
				Local_Status = OK;
			}
		}
	}

	return Local_Status;
}



void RCC_AHB_EnableClock(AHB_Peripheral_t periph)
{
	SET_BIT(RCC->AHBENR, periph);
}



void RCC_AHB_DisableClock(AHB_Peripheral_t periph)
{
	CLR_BIT(RCC->AHBENR, periph);
}


void RCC_APB1_EnableClock(APB1_Peripheral_t periph)
{
	SET_BIT(RCC->APB1ENR, periph);
}


void RCC_APB1_DisableClock(APB1_Peripheral_t periph)
{
	CLR_BIT(RCC->APB1ENR, periph);
}



void RCC_APB2_EnableClock(APB2_Peripheral_t periph)
{
	SET_BIT(RCC->APB2ENR, periph);
}



void RCC_APB2_DisableClock(APB2_Peripheral_t periph)
{
	CLR_BIT(RCC->APB2ENR, periph);
}


/*========================================================================================
 * Private Function Implementations
 *========================================================================================*/


static void RCC_HSE_Config(void)
{
	if (hseConfig.divider_factor == divided_by_2)
	{
		SET_BIT(RCC->CFGR, RCC_CFGR_PLLXTPRE_BIT);
	}
	else
	{
		CLR_BIT(RCC->CFGR, RCC_CFGR_PLLXTPRE_BIT);
	}
}



static void RCC_PLL_Config(void)
{
	RCC->CFGR &= ~RCC_CFGR_PLLMUL_MASK;
	RCC->CFGR |=  ((uint32_t)pllConfig.mul << RCC_CFGR_PLLMUL_SHIFT);

	if (pllConfig.source == HSE)
	{
		SET_BIT(RCC->CFGR, RCC_CFGR_PLLSRC_BIT);
	}
	else
	{
		CLR_BIT(RCC->CFGR, RCC_CFGR_PLLSRC_BIT);
	}
}
