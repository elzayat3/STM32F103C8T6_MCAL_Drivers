#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

/**
 * @file RCC_Private.h
 * @brief Private definitions for RCC driver on STM32F103C8T6.
 *
 * This file contains private bit positions, masks, and register field
 * definitions used internally by RCC_Program.c.
 *
 * @note This file must not be included by application files.
 *
 * @author Abdelrahman Elzayat
 */

/*========================================================================================
 * RCC_CR Register Bit Positions
 *========================================================================================*/

/**
 * @def RCC_CR_HSION_BIT
 * @brief HSI oscillator enable bit position.
 */
#define RCC_CR_HSION_BIT        0u

/**
 * @def RCC_CR_HSIRDY_BIT
 * @brief HSI oscillator ready flag bit position.
 */
#define RCC_CR_HSIRDY_BIT       1u

/**
 * @def RCC_CR_HSEON_BIT
 * @brief HSE oscillator enable bit position.
 */
#define RCC_CR_HSEON_BIT        16u

/**
 * @def RCC_CR_HSERDY_BIT
 * @brief HSE oscillator ready flag bit position.
 */
#define RCC_CR_HSERDY_BIT       17u

/**
 * @def RCC_CR_PLLON_BIT
 * @brief PLL enable bit position.
 */
#define RCC_CR_PLLON_BIT        24u

/**
 * @def RCC_CR_PLLRDY_BIT
 * @brief PLL ready flag bit position.
 */
#define RCC_CR_PLLRDY_BIT       25u


/*========================================================================================
 * RCC_CFGR Register Field Positions
 *========================================================================================*/

/**
 * @def RCC_CFGR_SW_SHIFT
 * @brief System clock switch field start bit.
 */
#define RCC_CFGR_SW_SHIFT       0u

/**
 * @def RCC_CFGR_SWS_SHIFT
 * @brief System clock switch status field start bit.
 */
#define RCC_CFGR_SWS_SHIFT      2u

/**
 * @def RCC_CFGR_PLLSRC_BIT
 * @brief PLL source selection bit position.
 */
#define RCC_CFGR_PLLSRC_BIT     16u

/**
 * @def RCC_CFGR_PLLXTPRE_BIT
 * @brief HSE divider for PLL input bit position.
 */
#define RCC_CFGR_PLLXTPRE_BIT   17u

/**
 * @def RCC_CFGR_PLLMUL_SHIFT
 * @brief PLL multiplication factor field start bit.
 */
#define RCC_CFGR_PLLMUL_SHIFT   18u


/*========================================================================================
 * RCC_CFGR Register Masks
 *========================================================================================*/

/**
 * @def RCC_CFGR_SW_MASK
 * @brief Mask for system clock switch field.
 */
#define RCC_CFGR_SW_MASK        (0x3UL << RCC_CFGR_SW_SHIFT)

/**
 * @def RCC_CFGR_SWS_MASK
 * @brief Mask for system clock switch status field.
 */
#define RCC_CFGR_SWS_MASK       (0x3UL << RCC_CFGR_SWS_SHIFT)

/**
 * @def RCC_CFGR_PLLMUL_MASK
 * @brief Mask for PLL multiplication factor field.
 */
#define RCC_CFGR_PLLMUL_MASK    (0xFUL << RCC_CFGR_PLLMUL_SHIFT)


/*========================================================================================
 * RCC_CFGR System Clock Selection Values
 *========================================================================================*/

/**
 * @def RCC_SYSCLK_HSI
 * @brief HSI selected as system clock.
 */
#define RCC_SYSCLK_HSI          0u

/**
 * @def RCC_SYSCLK_HSE
 * @brief HSE selected as system clock.
 */
#define RCC_SYSCLK_HSE          1u

/**
 * @def RCC_SYSCLK_PLL
 * @brief PLL selected as system clock.
 */
#define RCC_SYSCLK_PLL          2u


/*========================================================================================
 * RCC_CFGR PLL Source Values
 *========================================================================================*/

/**
 * @def RCC_PLL_SOURCE_HSI
 * @brief HSI divided by 2 selected as PLL input.
 */
#define RCC_PLL_SOURCE_HSI      0u

/**
 * @def RCC_PLL_SOURCE_HSE
 * @brief HSE selected as PLL input.
 */
#define RCC_PLL_SOURCE_HSE      1u


/*========================================================================================
 * Common Private Values
 *========================================================================================*/

/**
 * @def RCC_READY_FLAG_SET
 * @brief Expected value when a ready flag is set.
 */
#define RCC_READY_FLAG_SET      1u

/**
 * @def RCC_READY_FLAG_CLEAR
 * @brief Expected value when a ready flag is cleared.
 */
#define RCC_READY_FLAG_CLEAR    0u

#endif /* RCC_PRIVATE_H_ */
