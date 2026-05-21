#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

/**
 * @file GPIO_Private.h
 * @brief Private definitions for GPIO driver on STM32F103C8T6 Blue Pill.
 *
 * @details
 * This file contains private macros used internally by GPIO_Prg.c.
 *
 * STM32F103 GPIO pin configuration uses 4 bits per pin:
 * - MODE[1:0]
 * - CNF[1:0]
 *
 * Pins 0 to 7  are configured through GPIOx_CRL.
 * Pins 8 to 15 are configured through GPIOx_CRH.
 *
 * @note
 * This file must not be included by application files.
 */

/*========================================================================================
 * GPIO General Private Macros
 *========================================================================================*/

#define GPIO_PORTS                         4u

#define GPIO_CRL_MAX_PIN                   7u
#define GPIO_CRH_PIN_OFFSET                8u

#define GPIO_PIN_CONFIG_BITS               4u
#define GPIO_PIN_CONFIG_MASK               0xFUL

#define GPIO_CNF_SHIFT                     2u


/*========================================================================================
 * STM32F103 GPIO MODE Bit Encodings
 *========================================================================================*/

/*
 * MODE[1:0]
 *
 * 00: Input mode
 * 01: Output mode, max speed 10 MHz
 * 10: Output mode, max speed 2 MHz
 * 11: Output mode, max speed 50 MHz
 */
#define GPIO_MODE_BITS_INPUT               0x0UL
#define GPIO_MODE_BITS_OUTPUT_10MHZ        0x1UL
#define GPIO_MODE_BITS_OUTPUT_2MHZ         0x2UL
#define GPIO_MODE_BITS_OUTPUT_50MHZ        0x3UL


/*========================================================================================
 * STM32F103 GPIO CNF Bit Encodings
 *========================================================================================*/

/*
 * Input mode CNF[1:0]
 *
 * 00: Analog mode
 * 01: Floating input
 * 10: Input with pull-up / pull-down
 * 11: Reserved
 */
#define GPIO_CNF_INPUT_ANALOG              0x0UL
#define GPIO_CNF_INPUT_FLOATING            0x1UL
#define GPIO_CNF_INPUT_PULL                0x2UL


/*
 * Output mode CNF[1:0]
 *
 * 00: General purpose output push-pull
 * 01: General purpose output open-drain
 * 10: Alternate function output push-pull
 * 11: Alternate function output open-drain
 */
#define GPIO_CNF_OUTPUT_PUSH_PULL          0x0UL
#define GPIO_CNF_OUTPUT_OPEN_DRAIN         0x1UL
#define GPIO_CNF_AF_PUSH_PULL              0x2UL
#define GPIO_CNF_AF_OPEN_DRAIN             0x3UL

#endif /* GPIO_PRIVATE_H_ */
