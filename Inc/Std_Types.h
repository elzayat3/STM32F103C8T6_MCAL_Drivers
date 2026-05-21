#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/**
 * @file STD_TYPES.h
 * @brief Standard type definitions and bit manipulation macros.
 *
 * This file contains common data types and utility macros used across
 * the project drivers.
 *
 * It defines:
 * - Boolean type.
 * - Standard error status type.
 * - Bit manipulation macros.
 *
 * @author Abdelrahman Elzayat
 */

/**
 * @enum bool_t
 * @brief Boolean status type.
 *
 * This enum is used to represent boolean states in the project.
 *
 * @note FALSE is defined as 0x55 and TRUE is defined as 0xAA.
 *       Therefore, do not use this type directly in normal C conditions
 *       like `if(flag)`. Prefer explicit comparison such as:
 *       `if(flag == TRUE)`.
 */
typedef enum
{
	FALSE=0X55, /**< Boolean false value */
	TRUE=0XAA  /**< Boolean true value  */
}bool_t;

/**
 * @enum error_t
 * @brief Standard error status type.
 *
 * This enum is used as a return type for driver APIs to indicate
 * whether the operation completed successfully or failed due to
 * a specific reason.
 */
typedef enum
{
	OK,           /**< Operation completed successfully */
	NOK,          /**< Operation failed */
	NULL_PTR,     /**< Null pointer was passed */
	OUT_OF_RANGE, /**< Input parameter is outside the valid range */
	IN_PROGRESS,  /**< Operation is currently in progress */
	TIMEOUT       /**< Operation timed out */
}error_t;

/**
 * @def SET_BIT(REG,BIT)
 * @brief Sets a specific bit in a register or variable.
 *
 * @param REG Register or variable to modify.
 * @param BIT Bit position to set.
 */
#define SET_BIT(REG,BIT) (REG|=( 1UL <<BIT))

/**
 * @def CLR_BIT(REG,BIT)
 * @brief Clears a specific bit in a register or variable.
 *
 * @param REG Register or variable to modify.
 * @param BIT Bit position to clear.
 */
#define CLR_BIT(REG,BIT) (REG&=(~( 1UL <<BIT)))

/**
 * @def TOG_BIT(REG,BIT)
 * @brief Toggles a specific bit in a register or variable.
 *
 * @param REG Register or variable to modify.
 * @param BIT Bit position to toggle.
 */
#define TOG_BIT(REG,BIT) (REG^=( 1UL <<BIT))

/**
 * @def GET_BIT(REG,BIT)
 * @brief Reads a specific bit from a register or variable.
 *
 * @param REG Register or variable to read from.
 * @param BIT Bit position to read.
 *
 * @return 1 if the bit is set, 0 if the bit is cleared.
 */
#define GET_BIT(REG,BIT) (((REG>>BIT)& 1UL))



#define NULLPTR          ((void*)0)


#endif /* STD_TYPES_H_ */
