#ifndef GPIO_INT_H_
#define GPIO_INT_H_

/**
 * @file GPIO_Int.h
 * @brief GPIO driver public interface for STM32F103C8T6 Blue Pill.
 *
 * @details
 * This file contains the public data types and APIs used to configure
 * and control GPIO pins on STM32F103C8T6.
 *
 * The driver supports:
 * - GPIO input mode.
 * - GPIO output mode.
 * - Analog input mode.
 * - Alternate function output mode.
 * - Output speed selection.
 * - Push-pull and open-drain output types.
 * - Floating, pull-up, and pull-down input configurations.
 * - Pin set, read, and toggle operations.
 *
 * @note
 * This GPIO interface is written specifically for STM32F103C8T6 Blue Pill.
 *
 * @note
 * STM32F103 GPIO configuration is based on CRL and CRH registers.
 * It does not use MODER, OTYPER, PUPDR, or AFR registers like STM32F4.
 *
 * @warning
 * Before using any GPIO port, its clock must be enabled first using
 * the RCC driver.
 *
 * @author Abdelrahman Elzayat
 */

#include "Std_Types.h"

/*========================================================================================
 * GPIO Port Types
 *========================================================================================*/

/**
 * @enum GPIO_Port_t
 * @brief Available GPIO ports for STM32F103C8T6.
 *
 * @details
 * This enum is used to select the GPIO port passed to GPIO APIs.
 *
 * Available ports:
 * - GPIO_PORTA
 * - GPIO_PORTB
 * - GPIO_PORTC
 * - GPIO_PORTD
 *
 * @note
 * The enum values are intentionally named GPIO_PORTx instead of GPIOx
 * to avoid conflict with GPIO peripheral pointer macros in Mem_Map.h.
 */
typedef enum
{
	GPIO_PORTA = 0u, /**< GPIO Port A. */
	GPIO_PORTB,      /**< GPIO Port B. */
	GPIO_PORTC,      /**< GPIO Port C. */
	GPIO_PORTD       /**< GPIO Port D. */
} GPIO_Port_t;


/*========================================================================================
 * GPIO Pin Types
 *========================================================================================*/

/**
 * @enum GPIO_Pin_t
 * @brief GPIO pin numbers.
 *
 * @details
 * This enum is used to select a GPIO pin number from GPIO_PIN0 to GPIO_PIN15.
 *
 * STM32F103 GPIO configuration registers:
 * - GPIO_PIN0 to GPIO_PIN7  are configured through GPIOx_CRL.
 * - GPIO_PIN8 to GPIO_PIN15 are configured through GPIOx_CRH.
 *
 * @note
 * GPIO_MAX_PIN is not a real pin. It is used only as a boundary value
 * for validation.
 *
 * Example:
 * @code
 * if (Pin >= GPIO_MAX_PIN)
 * {
 *     status = OUT_OF_RANGE;
 * }
 * @endcode
 */
typedef enum
{
	GPIO_PIN0 = 0u, /**< GPIO pin 0. */
	GPIO_PIN1,      /**< GPIO pin 1. */
	GPIO_PIN2,      /**< GPIO pin 2. */
	GPIO_PIN3,      /**< GPIO pin 3. */
	GPIO_PIN4,      /**< GPIO pin 4. */
	GPIO_PIN5,      /**< GPIO pin 5. */
	GPIO_PIN6,      /**< GPIO pin 6. */
	GPIO_PIN7,      /**< GPIO pin 7. */
	GPIO_PIN8,      /**< GPIO pin 8. */
	GPIO_PIN9,      /**< GPIO pin 9. */
	GPIO_PIN10,     /**< GPIO pin 10. */
	GPIO_PIN11,     /**< GPIO pin 11. */
	GPIO_PIN12,     /**< GPIO pin 12. */
	GPIO_PIN13,     /**< GPIO pin 13. */
	GPIO_PIN14,     /**< GPIO pin 14. */
	GPIO_PIN15,     /**< GPIO pin 15. */

	GPIO_MAX_PIN    /**< Boundary value used for pin validation. Not a real GPIO pin. */
} GPIO_Pin_t;


/*========================================================================================
 * GPIO State Types
 *========================================================================================*/

/**
 * @enum GPIO_State_t
 * @brief GPIO pin logic state.
 *
 * @details
 * This enum is used with GPIO pin write and read APIs.
 *
 * - LOW  : Logic 0.
 * - HIGH : Logic 1.
 */
typedef enum
{
	LOW = 0u, /**< GPIO logic low state. */
	HIGH      /**< GPIO logic high state. */
} GPIO_State_t;


/*========================================================================================
 * GPIO Mode Types
 *========================================================================================*/

/**
 * @enum GPIO_Mode_t
 * @brief GPIO pin operating mode.
 *
 * @details
 * This enum defines the high-level operating mode of a GPIO pin.
 *
 * The selected mode will be translated internally into MODE[1:0]
 * and CNF[1:0] bits inside GPIOx_CRL or GPIOx_CRH.
 */
typedef enum
{
	GPIO_MODE_INPUT = 0u, /**< Input mode. */
	GPIO_MODE_OUTPUT,    /**< General purpose output mode. */
	GPIO_MODE_ANALOG,    /**< Analog input mode. */
	GPIO_MODE_ALTERNATE  /**< Alternate function output mode. */
} GPIO_Mode_t;


/**
 * @enum GPIO_Speed_t
 * @brief GPIO output speed options.
 *
 * @details
 * These values map directly to MODE[1:0] bits in GPIOx_CRL/GPIOx_CRH
 * when the pin is configured as output or alternate function output.
 *
 * STM32F103 MODE[1:0] encoding:
 * - 01: Output mode, max speed 10 MHz.
 * - 10: Output mode, max speed 2 MHz.
 * - 11: Output mode, max speed 50 MHz.
 *
 * @note
 * There is no output speed value equal to 0 because MODE = 00 means input mode.
 */
typedef enum
{
	GPIO_SPEED_10MHZ = 1u, /**< Output speed up to 10 MHz. */
	GPIO_SPEED_2MHZ  = 2u, /**< Output speed up to 2 MHz. */
	GPIO_SPEED_50MHZ = 3u  /**< Output speed up to 50 MHz. */
} GPIO_Speed_t;


/**
 * @enum GPIO_OutputType_t
 * @brief GPIO output driver type.
 *
 * @details
 * This enum selects the output electrical type when the pin is configured as:
 * - General purpose output.
 * - Alternate function output.
 *
 * Supported output types:
 * - Push-pull.
 * - Open-drain.
 *
 * @note
 * This setting has no effect when the pin is configured as input
 * or analog mode.
 */
typedef enum
{
	GPIO_PUSH_PULL = 0u, /**< Push-pull output. */
	GPIO_OPEN_DRAIN     /**< Open-drain output. */
} GPIO_OutputType_t;


/**
 * @enum GPIO_Pull_t
 * @brief GPIO input pull configuration.
 *
 * @details
 * This enum selects the input pull configuration.
 *
 * On STM32F103:
 * - Floating input is configured using CNF bits.
 * - Pull-up and pull-down use the same CNF configuration.
 * - Pull direction is selected through the corresponding ODR bit.
 *
 * @note
 * This setting is mainly used when the pin mode is GPIO_MODE_INPUT.
 */
typedef enum
{
	GPIO_NO_PULL = 0u, /**< Floating input, no internal pull-up or pull-down. */
	GPIO_PULL_UP,     /**< Input with internal pull-up resistor. */
	GPIO_PULL_DOWN    /**< Input with internal pull-down resistor. */
} GPIO_Pull_t;


/*========================================================================================
 * GPIO Configuration Structure
 *========================================================================================*/

/**
 * @struct GPIO_Config_t
 * @brief GPIO pin configuration structure.
 *
 * @details
 * This structure contains all user configuration options needed to
 * initialize one GPIO pin.
 *
 * Usage notes:
 * - Port and Pin must always be configured.
 * - Mode selects input, output, analog, or alternate function.
 * - Speed is used only with output and alternate output modes.
 * - OutputType is used only with output and alternate output modes.
 * - Pull is used mainly with input mode.
 */
typedef struct
{
	GPIO_Port_t       Port;       /**< Selected GPIO port. */
	GPIO_Pin_t        Pin;        /**< Selected GPIO pin. */
	GPIO_Mode_t       Mode;       /**< Selected GPIO mode. */
	GPIO_Speed_t      Speed;      /**< Output speed. Used only in output or alternate mode. */
	GPIO_OutputType_t OutputType; /**< Output type. Used only in output or alternate mode. */
	GPIO_Pull_t       Pull;       /**< Pull configuration. Used mainly in input mode. */
} GPIO_Config_t;


/*========================================================================================
 * GPIO Public APIs
 *========================================================================================*/

/**
 * @brief Initializes a specific GPIO pin according to user configuration.
 *
 * @param[in] Config Pointer to GPIO configuration structure.
 *
 * @retval OK GPIO pin initialized successfully.
 * @retval NULL_PTR Config pointer is NULL.
 * @retval OUT_OF_RANGE Invalid port, pin, mode, speed, output type, or pull configuration.
 *
 * @note
 * The corresponding GPIO port clock must be enabled before calling this function.
 *
 * @warning
 * For STM32F103, pins 0 to 7 are configured through CRL,
 * while pins 8 to 15 are configured through CRH.
 */
error_t GPIO_Pin_Init(const GPIO_Config_t *Config);


/**
 * @brief Sets the output state of a GPIO pin.
 *
 * @param[in] Port  GPIO port selected from @ref GPIO_Port_t.
 * @param[in] Pin   GPIO pin selected from @ref GPIO_Pin_t.
 * @param[in] State Required output state selected from @ref GPIO_State_t.
 *
 * @retval OK Pin state changed successfully.
 * @retval OUT_OF_RANGE Invalid port, pin, or state.
 *
 * @note
 * This function writes to BSRR or BRR register depending on the required state.
 */
error_t GPIO_Pin_SetValue(GPIO_Port_t Port, GPIO_Pin_t Pin, GPIO_State_t State);


/**
 * @brief Reads the current input state of a GPIO pin.
 *
 * @param[in]  Port  GPIO port selected from @ref GPIO_Port_t.
 * @param[in]  Pin   GPIO pin selected from @ref GPIO_Pin_t.
 * @param[out] State Pointer to variable that will store the pin state.
 *                   - LOW  : Pin is logic low.
 *                   - HIGH : Pin is logic high.
 *
 * @retval OK Pin state read successfully.
 * @retval NULL_PTR State pointer is NULL.
 * @retval OUT_OF_RANGE Invalid port or pin.
 *
 * @note
 * This function reads from the IDR register of the selected GPIO port.
 */
error_t GPIO_Pin_GetValue(GPIO_Port_t Port, GPIO_Pin_t Pin, GPIO_State_t *State);


/**
 * @brief Toggles the output state of a GPIO pin.
 *
 * @param[in] Port GPIO port selected from @ref GPIO_Port_t.
 * @param[in] Pin  GPIO pin selected from @ref GPIO_Pin_t.
 *
 * @retval OK Pin state toggled successfully.
 * @retval OUT_OF_RANGE Invalid port or pin.
 *
 * @note
 * This function toggles the corresponding bit in the ODR register.
 */
error_t GPIO_Pin_ToggleValue(GPIO_Port_t Port, GPIO_Pin_t Pin);

#endif /* GPIO_INT_H_ */
