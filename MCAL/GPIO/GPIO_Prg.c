#include <stdint.h>

#include "Std_Types.h"
#include "Mem_Map.h"
#include "GPIO_Int.h"
#include "GPIO_Private.h"
#include "GPIO_Cfg.h"


static GPIO_RegDef_t * const GPIO_Ports[GPIO_PORTS] =
{
	GPIOA,
	GPIOB,
	GPIOC,
	GPIOD
};


static error_t GPIO_ValidatePortPin(GPIO_Port_t Port, GPIO_Pin_t Pin);
static error_t GPIO_ValidateConfig(const GPIO_Config_t *Config);
static uint32_t GPIO_GetPinConfigValue(const GPIO_Config_t *Config);


error_t GPIO_Pin_Init(const GPIO_Config_t *Config)
{
	error_t Local_Status = OK;
	GPIO_RegDef_t *Local_Port = NULLPTR;
	volatile uint32_t *Local_Reg = NULLPTR;
	uint32_t Local_Shift = 0u;
	uint32_t Local_ConfigValue = 0u;

	Local_Status = GPIO_ValidateConfig(Config);

	if (Local_Status == OK)
	{
		Local_Port = GPIO_Ports[Config->Port];

		if (Config->Pin <= GPIO_CRL_MAX_PIN)
		{
			Local_Reg = &(Local_Port->CRL);
			Local_Shift = ((uint32_t)Config->Pin * GPIO_PIN_CONFIG_BITS);
		}
		else
		{
			Local_Reg = &(Local_Port->CRH);
			Local_Shift = (((uint32_t)Config->Pin - GPIO_CRH_PIN_OFFSET) * GPIO_PIN_CONFIG_BITS);
		}

		Local_ConfigValue = GPIO_GetPinConfigValue(Config);

		(*Local_Reg) &= ~(GPIO_PIN_CONFIG_MASK << Local_Shift);
		(*Local_Reg) |=  (Local_ConfigValue << Local_Shift);

		if (Config->Mode == GPIO_MODE_INPUT)
		{
			if (Config->Pull == GPIO_PULL_UP)
			{
				SET_BIT(Local_Port->ODR, Config->Pin);
			}
			else if (Config->Pull == GPIO_PULL_DOWN)
			{
				CLR_BIT(Local_Port->ODR, Config->Pin);
			}
			else
			{
				/* Do nothing */
			}
		}
		else
		{
			/* Do nothing */
		}
	}

	return Local_Status;
}


error_t GPIO_Pin_SetValue(GPIO_Port_t Port, GPIO_Pin_t Pin, GPIO_State_t State)
{
	error_t Local_Status = OK;

	Local_Status = GPIO_ValidatePortPin(Port, Pin);

	if (Local_Status == OK)
	{
		if (State > HIGH)
		{
			Local_Status = OUT_OF_RANGE;
		}
		else if (State == LOW)
		{
			GPIO_Ports[Port]->BRR = (1UL << Pin);
		}
		else
		{
			GPIO_Ports[Port]->BSRR = (1UL << Pin);
		}
	}

	return Local_Status;
}


error_t GPIO_Pin_GetValue(GPIO_Port_t Port, GPIO_Pin_t Pin, GPIO_State_t *State)
{
	error_t Local_Status = OK;

	if (State == NULLPTR)
	{
		Local_Status = NULL_PTR;
	}
	else
	{
		Local_Status = GPIO_ValidatePortPin(Port, Pin);

		if (Local_Status == OK)
		{
			if (GET_BIT(GPIO_Ports[Port]->IDR, Pin) == 0UL)
			{
				*State = LOW;
			}
			else
			{
				*State = HIGH;
			}
		}
	}

	return Local_Status;
}


error_t GPIO_Pin_ToggleValue(GPIO_Port_t Port, GPIO_Pin_t Pin)
{
	error_t Local_Status = OK;

	Local_Status = GPIO_ValidatePortPin(Port, Pin);

	if (Local_Status == OK)
	{
		TOG_BIT(GPIO_Ports[Port]->ODR, Pin);
	}

	return Local_Status;
}


static error_t GPIO_ValidatePortPin(GPIO_Port_t Port, GPIO_Pin_t Pin)
{
	error_t Local_Status = OK;

	if ((Port >= GPIO_PORTS) || (Pin >= GPIO_MAX_PIN))
	{
		Local_Status = OUT_OF_RANGE;
	}

	return Local_Status;
}


static error_t GPIO_ValidateConfig(const GPIO_Config_t *Config)
{
	error_t Local_Status = OK;

	if (Config == NULLPTR)
	{
		Local_Status = NULL_PTR;
	}
	else if ((Config->Port >= GPIO_PORTS) ||
	         (Config->Pin >= GPIO_MAX_PIN) ||
	         (Config->Mode > GPIO_MODE_ALTERNATE) ||
	         ((Config->Speed != GPIO_SPEED_10MHZ) &&
	          (Config->Speed != GPIO_SPEED_2MHZ)  &&
	          (Config->Speed != GPIO_SPEED_50MHZ)) ||
	         (Config->OutputType > GPIO_OPEN_DRAIN) ||
	         (Config->Pull > GPIO_PULL_DOWN))
	{
		Local_Status = OUT_OF_RANGE;
	}

	return Local_Status;
}


static uint32_t GPIO_GetPinConfigValue(const GPIO_Config_t *Config)
{
	uint32_t Local_ConfigValue = 0u;
	uint32_t Local_ModeBits = 0u;
	uint32_t Local_CnfBits = 0u;

	switch (Config->Mode)
	{
		case GPIO_MODE_ANALOG:
			Local_ModeBits = GPIO_MODE_BITS_INPUT;
			Local_CnfBits  = GPIO_CNF_INPUT_ANALOG;
			break;

		case GPIO_MODE_INPUT:
			Local_ModeBits = GPIO_MODE_BITS_INPUT;

			if (Config->Pull == GPIO_NO_PULL)
			{
				Local_CnfBits = GPIO_CNF_INPUT_FLOATING;
			}
			else
			{
				Local_CnfBits = GPIO_CNF_INPUT_PULL;
			}
			break;

		case GPIO_MODE_OUTPUT:
			Local_ModeBits = (uint32_t)Config->Speed;

			if (Config->OutputType == GPIO_PUSH_PULL)
			{
				Local_CnfBits = GPIO_CNF_OUTPUT_PUSH_PULL;
			}
			else
			{
				Local_CnfBits = GPIO_CNF_OUTPUT_OPEN_DRAIN;
			}
			break;

		case GPIO_MODE_ALTERNATE:
			Local_ModeBits = (uint32_t)Config->Speed;

			if (Config->OutputType == GPIO_PUSH_PULL)
			{
				Local_CnfBits = GPIO_CNF_AF_PUSH_PULL;
			}
			else
			{
				Local_CnfBits = GPIO_CNF_AF_OPEN_DRAIN;
			}
			break;

		default:
			Local_ModeBits = GPIO_MODE_BITS_INPUT;
			Local_CnfBits  = GPIO_CNF_INPUT_FLOATING;
			break;
	}

	Local_ConfigValue = Local_ModeBits | (Local_CnfBits << GPIO_CNF_SHIFT);

	return Local_ConfigValue;
}
