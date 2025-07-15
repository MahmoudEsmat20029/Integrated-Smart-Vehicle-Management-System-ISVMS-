/******************************************************************************
 * Module       : GPIO
 * File Name    : gpio.c
 * Author       : A7la Team :)
 * Created on   : 10/10/2024
 * Description  : Source file for the GPIO AVR driver
 *******************************************************************************/

#include "gpio.h"  /* Include GPIO header file */
#include <avr/io.h>  /* Include AVR I/O header file */
#include "../../LIB/common_macros.h"  /* Include common macros header file */

/*******************************************************************************
 *                       Functions Definitions                                 *
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
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction)
{
    /*
     * Check if the input port number or pin number is invalid.
     * If invalid, do nothing.
     */
    if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
    {
        /* Do Nothing */
    }
    else
    {
        /* Setup the pin direction as required */
        switch (port_num)
        {
        case PORTA_ID:
            if (direction == PIN_OUTPUT)
            {
                SET_BIT(DDRA, pin_num);  /* Set pin as output */
            }
            else
            {
                CLEAR_BIT(DDRA, pin_num);  /* Set pin as input */
            }
            break;
        case PORTB_ID:
            if (direction == PIN_OUTPUT)
            {
                SET_BIT(DDRB, pin_num);  /* Set pin as output */
            }
            else
            {
                CLEAR_BIT(DDRB, pin_num);  /* Set pin as input */
            }
            break;
        case PORTC_ID:
            if (direction == PIN_OUTPUT)
            {
                SET_BIT(DDRC, pin_num);  /* Set pin as output */
            }
            else
            {
                CLEAR_BIT(DDRC, pin_num);  /* Set pin as input */
            }
            break;
        case PORTD_ID:
            if (direction == PIN_OUTPUT)
            {
                SET_BIT(DDRD, pin_num);  /* Set pin as output */
            }
            else
            {
                CLEAR_BIT(DDRD, pin_num);  /* Set pin as input */
            }
            break;
        }
    }
}

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
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
    /*
     * Check if the input port number or pin number is invalid.
     * If invalid, do nothing.
     */
    if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
    {
        /* Do Nothing */
    }
    else
    {
        /* Write the pin value as required */
        switch (port_num)
        {
        case PORTA_ID:
            if (value == LOGIC_HIGH)
            {
                SET_BIT(PORTA, pin_num);  /* Set pin to Logic High */
            }
            else
            {
                CLEAR_BIT(PORTA, pin_num);  /* Set pin to Logic Low */
            }
            break;
        case PORTB_ID:
            if (value == LOGIC_HIGH)
            {
                SET_BIT(PORTB, pin_num);  /* Set pin to Logic High */
            }
            else
            {
                CLEAR_BIT(PORTB, pin_num);  /* Set pin to Logic Low */
            }
            break;
        case PORTC_ID:
            if (value == LOGIC_HIGH)
            {
                SET_BIT(PORTC, pin_num);  /* Set pin to Logic High */
            }
            else
            {
                CLEAR_BIT(PORTC, pin_num);  /* Set pin to Logic Low */
            }
            break;
        case PORTD_ID:
            if (value == LOGIC_HIGH)
            {
                SET_BIT(PORTD, pin_num);  /* Set pin to Logic High */
            }
            else
            {
                CLEAR_BIT(PORTD, pin_num);  /* Set pin to Logic Low */
            }
            break;
        }
    }
}

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
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
    uint8 pin_value = LOGIC_LOW;

    /*
     * Check if the input port number or pin number is invalid.
     * If invalid, return Logic Low.
     */
    if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
    {
        /* Do Nothing */
    }
    else
    {
        /* Read the pin value as required */
        switch (port_num)
        {
        case PORTA_ID:
            if (BIT_IS_SET(PINA, pin_num))  /* Check if the pin is Logic High */
            {
                pin_value = LOGIC_HIGH;
            }
            else
            {
                pin_value = LOGIC_LOW;
            }
            break;
        case PORTB_ID:
            if (BIT_IS_SET(PINB, pin_num))  /* Check if the pin is Logic High */
            {
                pin_value = LOGIC_HIGH;
            }
            else
            {
                pin_value = LOGIC_LOW;
            }
            break;
        case PORTC_ID:
            if (BIT_IS_SET(PINC, pin_num))  /* Check if the pin is Logic High */
            {
                pin_value = LOGIC_HIGH;
            }
            else
            {
                pin_value = LOGIC_LOW;
            }
            break;
        case PORTD_ID:
            if (BIT_IS_SET(PIND, pin_num))  /* Check if the pin is Logic High */
            {
                pin_value = LOGIC_HIGH;
            }
            else
            {
                pin_value = LOGIC_LOW;
            }
            break;
        }
    }

    return pin_value;
}

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
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
    /*
     * Check if the input port number is invalid.
     * If invalid, do nothing.
     */
    if (port_num >= NUM_OF_PORTS)
    {
        /* Do Nothing */
    }
    else
    {
        /* Setup the port direction as required */
        switch (port_num)
        {
        case PORTA_ID:
            DDRA = direction;  /* Set port A direction */
            break;
        case PORTB_ID:
            DDRB = direction;  /* Set port B direction */
            break;
        case PORTC_ID:
            DDRC = direction;  /* Set port C direction */
            break;
        case PORTD_ID:
            DDRD = direction;  /* Set port D direction */
            break;
        }
    }
}

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
void GPIO_writePort(uint8 port_num, uint8 value)
{
    /*
     * Check if the input port number is invalid.
     * If invalid, do nothing.
     */
    if (port_num >= NUM_OF_PORTS)
    {
        /* Do Nothing */
    }
    else
    {
        /* Write the port value as required */
        switch (port_num)
        {
        case PORTA_ID:
            PORTA = value;  /* Write value to port A */
            break;
        case PORTB_ID:
            PORTB = value;  /* Write value to port B */
            break;
        case PORTC_ID:
            PORTC = value;  /* Write value to port C */
            break;
        case PORTD_ID:
            PORTD = value;  /* Write value to port D */
            break;
        }
    }
}

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is invalid, the function will return ZERO.
 * Parameters  :
 * - port_num: The port number (PORTA_ID, PORTB_ID, PORTC_ID, PORTD_ID).
 * Returns     :
 * - The value of the port.
 */
uint8 GPIO_readPort(uint8 port_num)
{
    uint8 value = LOGIC_LOW;

    /*
     * Check if the input port number is invalid.
     * If invalid, return ZERO.
     */
    if (port_num >= NUM_OF_PORTS)
    {
        /* Do Nothing */
    }
    else
    {
        /* Read the port value as required */
        switch (port_num)
        {
        case PORTA_ID:
            value = PINA;  /* Read value from port A */
            break;
        case PORTB_ID:
            value = PINB;  /* Read value from port B */
            break;
        case PORTC_ID:
            value = PINC;  /* Read value from port C */
            break;
        case PORTD_ID:
            value = PIND;  /* Read value from port D */
            break;
        }
    }

    return value;
}
