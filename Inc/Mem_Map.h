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



/*********************** GPIO REGISTERS DEFINITION STRUCTURE *****************************/



/*********************** GPIO PERIPHERAL DEFINITION **************************************/



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

#define RCC         ((RCC_RegDef_t *)RCC_BASE_ADDRESS)

#endif /* MEM_MAP_H */
