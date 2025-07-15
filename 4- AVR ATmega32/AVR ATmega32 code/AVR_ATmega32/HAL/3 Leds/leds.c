/******************************************************************************
 * Module       : LEDs
 * File Name    : led.c
 * Author       : A7la Team :)
 * Created on   : 10/10/2024
 * Description  : Source file for the LEDs driver
 *******************************************************************************/

#include "leds.h"  /* Include LEDs header file */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize LEDs:
 * 1. Set up the LED pins as output pins.
 * 2. Set the initial state of the LEDs based on the connection logic.
 */
void LEDS_init(void)
{
    /* Configure the LED pins as output pins */
    GPIO_setupPinDirection(LEDS_PORT_CONNECTION, RED_LED, PIN_OUTPUT);
    GPIO_setupPinDirection(LEDS_PORT_CONNECTION, GREEN_LED, PIN_OUTPUT);
    GPIO_setupPinDirection(LEDS_PORT_CONNECTION, BLUE_LED, PIN_OUTPUT);

#ifdef CONNECTION_POSITIVE_LOGIC
    /* Initialize LEDs to OFF state for positive logic */
    GPIO_writePin(LEDS_PORT_CONNECTION, RED_LED, LOGIC_LOW);
    GPIO_writePin(LEDS_PORT_CONNECTION, GREEN_LED, LOGIC_LOW);
    GPIO_writePin(LEDS_PORT_CONNECTION, BLUE_LED, LOGIC_LOW);
#else
    /* Initialize LEDs to OFF state for negative logic */
    GPIO_writePin(LEDS_PORT_CONNECTION, RED_LED, LOGIC_HIGH);
    GPIO_writePin(LEDS_PORT_CONNECTION, GREEN_LED, LOGIC_HIGH);
    GPIO_writePin(LEDS_PORT_CONNECTION, BLUE_LED, LOGIC_HIGH);
#endif
}

/*
 * Description :
 * Function to turn on a specific LED.
 * If the connection is POSITIVE LOGIC, put LOGIC HIGH to turn it on.
 * Else, put LOGIC LOW (NEGATIVE LOGIC CONNECTION).
 * Parameters  :
 * - id: The ID of the LED to turn on (red, green, blue).
 */
void LED_on(LED_ID id)
{
#ifdef CONNECTION_POSITIVE_LOGIC
    /* Turn on the LED for positive logic */
    switch (id)
    {
    case red:
        GPIO_writePin(LEDS_PORT_CONNECTION, RED_LED, LOGIC_HIGH);
        break;
    case green:
        GPIO_writePin(LEDS_PORT_CONNECTION, GREEN_LED, LOGIC_HIGH);
        break;
    case blue:
        GPIO_writePin(LEDS_PORT_CONNECTION, BLUE_LED, LOGIC_HIGH);
        break;
    }
#else
    /* Turn on the LED for negative logic */
    switch (id)
    {
    case red:
        GPIO_writePin(LEDS_PORT_CONNECTION, RED_LED, LOGIC_LOW);
        break;
    case green:
        GPIO_writePin(LEDS_PORT_CONNECTION, GREEN_LED, LOGIC_LOW);
        break;
    case blue:
        GPIO_writePin(LEDS_PORT_CONNECTION, BLUE_LED, LOGIC_LOW);
        break;
    }
#endif
}

/*
 * Description :
 * Function to turn off a specific LED.
 * If the connection is POSITIVE LOGIC, put LOGIC LOW to turn it off.
 * Else, put LOGIC HIGH (NEGATIVE LOGIC CONNECTION).
 * Parameters  :
 * - id: The ID of the LED to turn off (red, green, blue).
 */
void LED_off(LED_ID id)
{
#ifdef CONNECTION_POSITIVE_LOGIC
    /* Turn off the LED for positive logic */
    switch (id)
    {
    case red:
        GPIO_writePin(LEDS_PORT_CONNECTION, RED_LED, LOGIC_LOW);
        break;
    case green:
        GPIO_writePin(LEDS_PORT_CONNECTION, GREEN_LED, LOGIC_LOW);
        break;
    case blue:
        GPIO_writePin(LEDS_PORT_CONNECTION, BLUE_LED, LOGIC_LOW);
        break;
    }
#else
    /* Turn off the LED for negative logic */
    switch (id)
    {
    case red:
        GPIO_writePin(LEDS_PORT_CONNECTION, RED_LED, LOGIC_HIGH);
        break;
    case green:
        GPIO_writePin(LEDS_PORT_CONNECTION, GREEN_LED, LOGIC_HIGH);
        break;
    case blue:
        GPIO_writePin(LEDS_PORT_CONNECTION, BLUE_LED, LOGIC_HIGH);
        break;
    }
#endif
}
