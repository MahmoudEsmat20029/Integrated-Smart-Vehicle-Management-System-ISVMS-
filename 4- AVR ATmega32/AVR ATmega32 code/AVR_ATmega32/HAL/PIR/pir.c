/******************************************************************************
 * Module       : PIR Sensor
 * File Name    : pir.c
 * Author       : A7la Team :)
 * Created on   : 21/11/2024
 * Description  : Source file for the PIR Sensor AVR driver
 *******************************************************************************/

#include "pir.h"  /* Include PIR Sensor header file */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the PIR sensor.
 * This function sets up the necessary pin directions for the PIR sensor.
 */
void PIR_init(void)
{
    /* Configure PIR sensor 0 pin as input */
    GPIO_setupPinDirection(PIR_PORT, PIR0_PIN, PIN_INPUT);

    /* Configure PIR sensor 1 pin as input */
    GPIO_setupPinDirection(PIR_PORT, PIR1_PIN, PIN_INPUT);
}

/*
 * Description :
 * Function to read the value from PIR sensor 0.
 * Returns     :
 * - The value read from the PIR sensor pin (0 or 1).
 */
uint8 PIR_ReadValue1(void)
{
    /* Read and return the value from PIR sensor 0 */
    return GPIO_readPin(PIR_PORT, PIR0_PIN);
}

/*
 * Description :
 * Function to read the value from PIR sensor 1.
 * Returns     :
 * - The value read from the PIR sensor pin (0 or 1).
 */
uint8 PIR_ReadValue2(void)
{
    /* Read and return the value from PIR sensor 1 */
    return GPIO_readPin(PIR_PORT, PIR1_PIN);
}
