/******************************************************************************
 * Module       : Ultrasonic Sensor
 * File Name    : ultrasonic_sensor.h
 * Author       : A7la Team :)
 * Created on   : 28/01/2025 --> "Edited in 24/02/2025"
 * Description  : Header file for the Ultrasonic Sensor driver
 *******************************************************************************/
#ifndef HAL_ULTRASONIC_SENSOR_H_
#define HAL_ULTRASONIC_SENSOR_H_

#include "../../MCAL/EXT_INT/EXT_INT.h"
#include "../../MCAL/TIMER/timer.h"
#include "../../MCAL/GPIO/gpio.h"  	/* Include GPIO driver for trigger pin control */
#include "../../LIB/std_types.h"  	/* Include standard types */
#include <util/delay.h>  			/* Include delay utility for timing */

/*******************************************************************************
 *                                Configurations                               *
 *******************************************************************************/
/* Define the port and pin for the ultrasonic sensor's trigger pin */
#define TRIGGERS_PORT_CONNECTION   	PORTB_ID  /* Port connected to the trigger pin */
#define TRIGGER1_PIN            	PIN5_ID   /* Pin connected to the trigger pin */
#define TRIGGER2_PIN               	PIN6_ID   /* Pin connected to the trigger pin */
#define TRIGGER3_PIN               	PIN7_ID   /* Pin connected to the trigger pin */

typedef enum {
	U_forward, U_right, U_backward
}Ultrasonic;

/*******************************************************************************
 *                       Functions Prototypes                                  *
 *******************************************************************************/

/*
 * Description :
 * 	- Initialize the ultrasonic sensor:
 * 		1. Set up ICU configuration for echo pulse measurement.
 * 		2. Initialize the ICU driver.
 * 		3. Set the callback function for the ICU.
 */
void Ultrasonic_init(void);

/*
 * Description :
 * 	- Measure the distance using the ultrasonic sensor:
 * 		1. Send the trigger pulse to start the measurement.
 * 		2. Use the ICU driver to measure the echo pulse duration.
 * 		3. Calculate and return the distance in centimeters.
 * Returns     :
 * 	- The measured distance in centimeters.
 */
uint16 Ultrasonic_readDistance(Ultrasonic ultrasonic);

#endif /* HAL_ULTRASONIC_SENSOR_H_ */
