/******************************************************************************
 * Module       : LEDs
 * File Name    : led.h
 * Author       : A7la Team :)
 * Created on   : 10/10/2024
 * Description  : Header file for the LEDs driver
 *******************************************************************************/

#ifndef HAL_LEDS_H_
#define HAL_LEDS_H_

#include "../../MCAL/GPIO/gpio.h"  /* Include GPIO driver for pin control */

/*******************************************************************************
 *                                Configurations                               *
 *******************************************************************************/

/* Define the connection logic for LEDs (POSITIVE or NEGATIVE logic) */
#define CONNECTION_POSITIVE_LOGIC

/* Define the port and pins for LED connections */
#define LEDS_PORT_CONNECTION        PORTC_ID  /* Port for LEDs */
#define RED_LED                     PIN0_ID   /* Pin for Red LED */
#define GREEN_LED                   PIN1_ID   /* Pin for Green LED */
#define BLUE_LED                    PIN2_ID   /* Pin for Blue LED */

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/* Enum to define the LED IDs */
typedef enum
{
    red,    /* Red LED */
    green,  /* Green LED */
    blue    /* Blue LED */
} LED_ID;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize LEDs:
 * 1. Set up the LED pins as output pins.
 * 2. Set the initial state of the LEDs based on the connection logic.
 */
void LEDS_init(void);

/*
 * Description :
 * Function to turn on a specific LED.
 * Parameters  :
 * - id: The ID of the LED to turn on (red, green, blue).
 */
void LED_on(LED_ID id);

/*
 * Description :
 * Function to turn off a specific LED.
 * Parameters  :
 * - id: The ID of the LED to turn off (red, green, blue).
 */
void LED_off(LED_ID id);

#endif /* HAL_LEDS_H_ */
