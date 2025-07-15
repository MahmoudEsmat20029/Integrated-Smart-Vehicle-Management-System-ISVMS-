/******************************************************************************
 * Module       : GPIO
 * File Name    : gpio.h
 * Author       : A7la Team :)
 * Created on   : 10/10/2024
 * Description  : Header file for the GPIO AVR driver
 *******************************************************************************/
#ifndef MCAL_GPIO_H_
#define MCAL_GPIO_H_

#include "../../LIB/std_types.h"  /* Include standard types header file */

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUM_OF_PORTS           4  /* Number of ports (PORTA, PORTB, PORTC, PORTD) */
#define NUM_OF_PINS_PER_PORT   8  /* Number of pins per port (Pins 0 to 7) */

#define PORTA_ID               0  /* Port A ID */
#define PORTB_ID               1  /* Port B ID */
#define PORTC_ID               2  /* Port C ID */
#define PORTD_ID               3  /* Port D ID */

#define PIN0_ID                0  /* Pin 0 ID */
#define PIN1_ID                1  /* Pin 1 ID */
#define PIN2_ID                2  /* Pin 2 ID */
#define PIN3_ID                3  /* Pin 3 ID */
#define PIN4_ID                4  /* Pin 4 ID */
#define PIN5_ID                5  /* Pin 5 ID */
#define PIN6_ID                6  /* Pin 6 ID */
#define PIN7_ID                7  /* Pin 7 ID */

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/* Enum to define pin direction types */
typedef enum
{
    PIN_INPUT,  /* Pin is configured as input */
    PIN_OUTPUT  /* Pin is configured as output */
} GPIO_PinDirectionType;

/* Enum to define port direction types */
typedef enum
{
    PORT_INPUT,      /* All pins in the port are configured as input */
    PORT_OUTPUT = 0xFF  /* All pins in the port are configured as output */
} GPIO_PortDirectionType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Setup the direction of the required pin as input or output.
 * If the input port number or pin number is invalid, the function will not handle the request.
 * Parameters  :
 * - port_num: The port number (PORTA_ID, PORTB_ID, PORTC_ID, PORTD_ID).
 * - pin_num: The pin number (PIN0_ID to PIN7_ID).
 * - direction: The direction of the pin (PIN_INPUT or PIN_OUTPUT).
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);

/*
 * Description :
 * Write a value (Logic High or Logic Low) on the required pin.
 * If the input port number or pin number is invalid, the function will not handle the request.
 * If the pin is configured as input, this function will enable/disable the internal pull-up resistor.
 * Parameters  :
 * - port_num: The port number (PORTA_ID, PORTB_ID, PORTC_ID, PORTD_ID).
 * - pin_num: The pin number (PIN0_ID to PIN7_ID).
 * - value: The value to write (Logic High or Logic Low).
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/*
 * Description :
 * Read and return the value of the required pin (Logic High or Logic Low).
 * If the input port number or pin number is invalid, the function will return Logic Low.
 * Parameters  :
 * - port_num: The port number (PORTA_ID, PORTB_ID, PORTC_ID, PORTD_ID).
 * - pin_num: The pin number (PIN0_ID to PIN7_ID).
 * Returns     :
 * - The value of the pin (Logic High or Logic Low).
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

/*
 * Description :
 * Setup the direction of all pins in the required port as input or output.
 * If the direction is PORT_INPUT, all pins in the port are configured as input.
 * If the direction is PORT_OUTPUT, all pins in the port are configured as output.
 * If the input port number is invalid, the function will not handle the request.
 * Parameters  :
 * - port_num: The port number (PORTA_ID, PORTB_ID, PORTC_ID, PORTD_ID).
 * - direction: The direction of the port (PORT_INPUT or PORT_OUTPUT).
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction);

/*
 * Description :
 * Write a value on the required port.
 * If any pin in the port is configured as output, the value will be written.
 * If any pin in the port is configured as input, this will activate/deactivate the internal pull-up resistor.
 * If the input port number is invalid, the function will not handle the request.
 * Parameters  :
 * - port_num: The port number (PORTA_ID, PORTB_ID, PORTC_ID, PORTD_ID).
 * - value: The value to write on the port.
 */
void GPIO_writePort(uint8 port_num, uint8 value);

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is invalid, the function will return ZERO.
 * Parameters  :
 * - port_num: The port number (PORTA_ID, PORTB_ID, PORTC_ID, PORTD_ID).
 * Returns     :
 * - The value of the port.
 */
uint8 GPIO_readPort(uint8 port_num);

#endif /* MCAL_GPIO_H_ */
