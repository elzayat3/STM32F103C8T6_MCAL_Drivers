# STM32F103C8T6 Blue Pill Bare-Metal Drivers

Bare-metal C drivers for the **STM32F103C8T6 Blue Pill** microcontroller.

Currently included:

- RCC Driver
- GPIO Driver

The drivers use direct register access through memory-mapped register structures.

---

## Target

- MCU: STM32F103C8T6
- Board: Blue Pill
- Core: ARM Cortex-M3
- GPIO model: STM32F1 `CRL` / `CRH`
- RCC model: Direct RCC register control

---

## Project Structure

```text
F103/
├── CFG/
│   ├── GPIO_Cfg.c
│   ├── GPIO_Cfg.h
│   ├── RCC_Cfg.c
│   └── RCC_Cfg.h
│
├── Inc/
│   ├── Mem_Map.h
│   └── Std_Types.h
│
├── MCAL/
│   ├── GPIO_Int.h
│   ├── GPIO_Prg.c
│   ├── GPIO_Private.h
│   ├── RCC_Int.h
│   ├── RCC_Prg.c
│   └── RCC_Private.h
│
├── Src/
├── Startup/
└── Debug/
```

---

# Common Files

## `Std_Types.h`

Contains standard project types and bit manipulation macros.

Common return type:

```c
typedef enum
{
    OK,
    NOK,
    NULL_PTR,
    OUT_OF_RANGE,
    IN_PROGRESS,
    TIMEOUT
} error_t;
```

Common macros:

```c
SET_BIT(REG, BIT)
CLR_BIT(REG, BIT)
TOG_BIT(REG, BIT)
GET_BIT(REG, BIT)
```

The project also uses:

```c
#define NULLPTR    ((void *)0)
```

---

## `Mem_Map.h`

Contains memory base addresses, peripheral base addresses, and register definition structures.

Currently mapped peripherals:

- RCC
- GPIOA
- GPIOB
- GPIOC
- GPIOD

GPIO register structure:

```c
typedef struct
{
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_RegDef_t;
```

RCC register structure:

```c
typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
} RCC_RegDef_t;
```

---

# RCC Driver

## Overview

The RCC driver controls the Reset and Clock Control peripheral.

It supports:

- Enabling and disabling clock sources
- Selecting the system clock source
- Configuring PLL source and multiplication factor
- Configuring HSE divider before PLL input
- Enabling and disabling peripheral clocks
- Peripheral validation for AHB, APB1, and APB2 buses

---

## RCC Files

| File | Description |
|---|---|
| `MCAL/RCC_Int.h` | Public interface, types, enums, and APIs |
| `MCAL/RCC_Private.h` | Private bit definitions, masks, and validation maps |
| `MCAL/RCC_Prg.c` | RCC function implementations |
| `CFG/RCC_Cfg.h` | RCC configuration declarations and timeout value |
| `CFG/RCC_Cfg.c` | RCC configuration objects |

---

## RCC Public APIs

```c
error_t RCC_Init(void);

error_t RCC_SetClockStatus(Clock_t clk, Status_t status);

error_t RCC_SetSystemClock(Clock_t clk);

error_t RCC_AHB_EnableClock(AHB_Peripheral_t periph);
error_t RCC_AHB_DisableClock(AHB_Peripheral_t periph);

error_t RCC_APB1_EnableClock(APB1_Peripheral_t periph);
error_t RCC_APB1_DisableClock(APB1_Peripheral_t periph);

error_t RCC_APB2_EnableClock(APB2_Peripheral_t periph);
error_t RCC_APB2_DisableClock(APB2_Peripheral_t periph);
```

---

## RCC Clock Sources

```c
typedef enum
{
    HSIk = 0u,
    HSEk,
    PLLk
} Clock_t;
```

```c
typedef enum
{
    OFF = 0u,
    ON
} Status_t;
```

---

## RCC PLL Configuration

```c
typedef enum
{
    PLL_mul_by_2 = 0u,
    PLL_mul_by_3,
    PLL_mul_by_4,
    PLL_mul_by_5,
    PLL_mul_by_6,
    PLL_mul_by_7,
    PLL_mul_by_8,
    PLL_mul_by_9,
    PLL_mul_by_10,
    PLL_mul_by_11,
    PLL_mul_by_12,
    PLL_mul_by_13,
    PLL_mul_by_14,
    PLL_mul_by_15,
    PLL_mul_by_16
} PLL_Mul_t;
```

```c
typedef enum
{
    HSI = 0u,
    HSE
} PLL_Source_t;
```

```c
typedef enum
{
    not_divided = 0u,
    divided_by_2
} HSE_divider_t;
```

---

## RCC Supported Peripherals

### AHB

```c
pDMA1
pSRAM
pFLITF
pCRC
```

### APB1

```c
pTIM2
pTIM3
pTIM4
pWWDG
pSPI2
pUSART2
pUSART3
pI2C1
pI2C2
pUSB
pCAN
pBKP
pPWR
```

### APB2

```c
pAFIO
pGPIOA
pGPIOB
pGPIOC
pGPIOD
pADC1
pADC2
pTIM1
pSPI1
pUSART1
```

---

## RCC Configuration Example

Safe PLL configuration using 8 MHz HSE:

```c
const HSE_Config_t hseConfig =
{
    .divider_factor = divided_by_2
};

const PLL_Config_t pllConfig =
{
    .source = HSE,
    .mul    = PLL_mul_by_4
};
```

If HSE = 8 MHz:

```text
PLL input  = 8 MHz / 2 = 4 MHz
PLL output = 4 MHz * 4 = 16 MHz
SYSCLK     = 16 MHz
```

---

## RCC Notes

- APB1 maximum frequency is 36 MHz.
- PLL output must not exceed 72 MHz.
- For 72 MHz operation, Flash latency and bus prescalers must be configured first.
- Current RCC driver does not yet configure:
  - Flash latency
  - Flash prefetch
  - AHB prescaler
  - APB1 prescaler
  - APB2 prescaler
  - ADC prescaler
  - USB prescaler

---

# GPIO Driver

## Overview

The GPIO driver controls STM32F103 GPIO pins using the STM32F1 GPIO register model.

STM32F103 GPIO uses:

- `GPIOx_CRL` for pins 0 to 7
- `GPIOx_CRH` for pins 8 to 15
- `GPIOx_IDR` for reading input values
- `GPIOx_ODR` for output data and toggle
- `GPIOx_BSRR` for atomic set
- `GPIOx_BRR` for atomic reset

---

## GPIO Files

| File | Description |
|---|---|
| `MCAL/GPIO_Int.h` | Public interface, enums, config struct, and APIs |
| `MCAL/GPIO_Private.h` | Private macros for CRL/CRH configuration |
| `MCAL/GPIO_Prg.c` | GPIO function implementations |
| `CFG/GPIO_Cfg.h` | Reserved for future static GPIO configuration |
| `CFG/GPIO_Cfg.c` | Reserved for future static GPIO configuration |

> Current GPIO configuration is dynamic through `GPIO_Config_t`, so `GPIO_Cfg.h` and `GPIO_Cfg.c` are placeholders for now.

---

## GPIO Supported Features

- Input mode
- Output mode
- Analog input mode
- Alternate function output mode
- Output speed selection
- Push-pull output
- Open-drain output
- Floating input
- Pull-up input
- Pull-down input
- Pin set
- Pin read
- Pin toggle

---

## GPIO Public APIs

```c
error_t GPIO_Pin_Init(const GPIO_Config_t *Config);

error_t GPIO_Pin_SetValue(GPIO_Port_t Port, GPIO_Pin_t Pin, GPIO_State_t State);

error_t GPIO_Pin_GetValue(GPIO_Port_t Port, GPIO_Pin_t Pin, GPIO_State_t *State);

error_t GPIO_Pin_ToggleValue(GPIO_Port_t Port, GPIO_Pin_t Pin);
```

---

## GPIO Ports

```c
typedef enum
{
    GPIO_PORTA = 0u,
    GPIO_PORTB,
    GPIO_PORTC,
    GPIO_PORTD
} GPIO_Port_t;
```

---

## GPIO Pins

```c
typedef enum
{
    GPIO_PIN0 = 0u,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,
    GPIO_PIN8,
    GPIO_PIN9,
    GPIO_PIN10,
    GPIO_PIN11,
    GPIO_PIN12,
    GPIO_PIN13,
    GPIO_PIN14,
    GPIO_PIN15,
    GPIO_MAX_PIN
} GPIO_Pin_t;
```

`GPIO_MAX_PIN` is not a real pin. It is used only as a boundary value for validation.

---

## GPIO States

```c
typedef enum
{
    LOW = 0u,
    HIGH
} GPIO_State_t;
```

---

## GPIO Modes

```c
typedef enum
{
    GPIO_MODE_INPUT = 0u,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_ANALOG,
    GPIO_MODE_ALTERNATE
} GPIO_Mode_t;
```

---

## GPIO Speeds

The speed enum values map directly to STM32F103 `MODE[1:0]` bits.

```c
typedef enum
{
    GPIO_SPEED_10MHZ = 1u,
    GPIO_SPEED_2MHZ  = 2u,
    GPIO_SPEED_50MHZ = 3u
} GPIO_Speed_t;
```

---

## GPIO Output Types

```c
typedef enum
{
    GPIO_PUSH_PULL = 0u,
    GPIO_OPEN_DRAIN
} GPIO_OutputType_t;
```

---

## GPIO Pull Options

```c
typedef enum
{
    GPIO_NO_PULL = 0u,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN
} GPIO_Pull_t;
```

---

## GPIO Configuration Structure

```c
typedef struct
{
    GPIO_Port_t       Port;
    GPIO_Pin_t        Pin;
    GPIO_Mode_t       Mode;
    GPIO_Speed_t      Speed;
    GPIO_OutputType_t OutputType;
    GPIO_Pull_t       Pull;
} GPIO_Config_t;
```

---

## GPIO Example: Blue Pill Onboard LED PC13

> On many Blue Pill boards, the onboard LED on PC13 is active-low.

```c
#include "Std_Types.h"
#include "RCC_Int.h"
#include "GPIO_Int.h"

int main(void)
{
    GPIO_Config_t Led =
    {
        .Port       = GPIO_PORTC,
        .Pin        = GPIO_PIN13,
        .Mode       = GPIO_MODE_OUTPUT,
        .Speed      = GPIO_SPEED_2MHZ,
        .OutputType = GPIO_PUSH_PULL,
        .Pull       = GPIO_NO_PULL
    };

    RCC_APB2_EnableClock(pGPIOC);

    GPIO_Pin_Init(&Led);

    while (1)
    {
        GPIO_Pin_SetValue(GPIO_PORTC, GPIO_PIN13, LOW);
        /* delay */

        GPIO_Pin_SetValue(GPIO_PORTC, GPIO_PIN13, HIGH);
        /* delay */
    }
}
```

---

## GPIO Example: Input Pull-up

```c
GPIO_Config_t Button =
{
    .Port       = GPIO_PORTA,
    .Pin        = GPIO_PIN0,
    .Mode       = GPIO_MODE_INPUT,
    .Speed      = GPIO_SPEED_2MHZ,
    .OutputType = GPIO_PUSH_PULL,
    .Pull       = GPIO_PULL_UP
};

GPIO_Pin_Init(&Button);
```

---

## GPIO Example: Read Pin

```c
GPIO_State_t ButtonState;

GPIO_Pin_GetValue(GPIO_PORTA, GPIO_PIN0, &ButtonState);

if (ButtonState == LOW)
{
    /* Button pressed if active-low */
}
else
{
    /* Button released */
}
```

---

## GPIO Example: Toggle Pin

```c
GPIO_Pin_ToggleValue(GPIO_PORTC, GPIO_PIN13);
```

---

# Current Limitations

## RCC

- No Flash latency configuration yet
- No AHB/APB prescaler configuration yet
- No ADC prescaler configuration yet
- No USB prescaler configuration yet

## GPIO

- No port-level initialization API yet
- No multi-pin write API yet
- No EXTI support yet
- No AFIO remap support yet

---

# Suggested Next Drivers

- NVIC
- EXTI
- AFIO
- SysTick
- USART
- SPI
- I2C
- TIM
- ADC
