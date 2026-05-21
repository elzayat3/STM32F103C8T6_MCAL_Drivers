#ifndef MEM_MAP_H
#define MEM_MAP_H

#include <stdint.h>

/*********************** MEMORY BASE ADDRESSES ********************************************/

#define FLASH_BASE_ADDRESS      0x08000000UL
#define SRAM_BASE_ADDRESS       0x20000000UL
#define ROM_BASE_ADDRESS        0x1FFFF000UL


/*********************** AHB PERIPHERAL ADDRESSES ****************************************/

#define RCC_BASE_ADDRESS        0x40021000UL


/*********************** APB1 PERIPHERAL ADDRESSES ***************************************/



/*********************** APB2 PERIPHERAL ADDRESSES ***************************************/

#define GPIOA_BASE_ADDRESS      0x40010800UL
#define GPIOB_BASE_ADDRESS      0x40010C00UL
#define GPIOC_BASE_ADDRESS      0x40011000UL
#define GPIOD_BASE_ADDRESS      0x40011400UL


/*********************** GPIO REGISTERS DEFINITION STRUCTURE *****************************/

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


/*********************** GPIO PERIPHERAL DEFINITION **************************************/

#define GPIOA                   ((GPIO_RegDef_t *)GPIOA_BASE_ADDRESS)
#define GPIOB                   ((GPIO_RegDef_t *)GPIOB_BASE_ADDRESS)
#define GPIOC                   ((GPIO_RegDef_t *)GPIOC_BASE_ADDRESS)
#define GPIOD                   ((GPIO_RegDef_t *)GPIOD_BASE_ADDRESS)


/*********************** RCC REGISTERS DEFINITION STRUCTURE ******************************/

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


/*********************** RCC PERIPHERAL DEFINITION ***************************************/

#define RCC                     ((RCC_RegDef_t *)RCC_BASE_ADDRESS)

#endif /* MEM_MAP_H */
