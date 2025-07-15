/******************************************************************************
 * Module       : PIR Sensor
 * File Name    : pir.h
 * Author       : A7la Team :)
 * Created on   : 21/11/2024
 * Description  : Header file for the PIR Sensor AVR driver
 *******************************************************************************/

#ifndef HAL_PIR_SENSOR_H_
#define HAL_PIR_SENSOR_H_

#include "../../MCAL/GPIO/gpio.h"  /* Include GPIO driver for pin control */
#include "../../LIB/std_types.h"   /* Include standard types */
#include <avr/io.h>                /* Include AVR I/O header file */

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* PIR sensor port and pin definitions */
#define PIR_PORT      PORTD_ID  /* Port where the PIR sensors are connected */
#define PIR0_PIN      PIN2_ID   /* Pin for PIR sensor 0 */
#define PIR1_PIN      PIN3_ID   /* Pin for PIR sensor 1 */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to read the value from PIR sensor 0.
 * Returns     :
 * - The value read from the PIR sensor pin (0 or 1).
 */
uint8 PIR_ReadValue1(void);

/*
 * Description :
 * Function to read the value from PIR sensor 1.
 * Returns     :
 * - The value read from the PIR sensor pin (0 or 1).
 */
uint8 PIR_ReadValue2(void);

/*
 * Description :
 * Function to initialize the PIR sensor.
 * This function sets up the necessary pin directions for the PIR sensor.
 */
void PIR_init(void);

#endif /* HAL_PIR_SENSOR_H_ */
