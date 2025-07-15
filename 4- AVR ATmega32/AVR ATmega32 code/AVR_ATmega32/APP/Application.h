/******************************************************************************
 * Module       : Application
 * File Name    : Application.h
 * Author       : A7la Team :)
 * Created on   : 22/11/2024
 * Description  : Header file for the Application layer
 *******************************************************************************/
#ifndef APP_APPLICATION_H_
#define APP_APPLICATION_H_

/*********************** MCAL Layer includes ***********************/
#include "../MCAL/EXT_INT/EXT_INT.h"	/* Include external interrupt driver */
#include "../MCAL/UART/UART.h"

/*********************** HAL Layer includes  ***********************/
#include "../HAL/Ultrasonic/ultrasonic_sensor.h"	/* ultrasonic sensor driver */
#include "../HAL/BUZZER/buzzer.h"					/* Buzzer sensor driver */
#include "../HAL/3 Leds/leds.h"						/* LEDs driver */
#include "../HAL/MOTOR/motor.h"						/* motor control driver */
#include "../HAL/LCD/lcd.h"							/* LCD driver */
#include "../HAL/PIR/pir.h"							/* PIR sensor driver */

/*********************** LIB Layer includes  ***********************/
#include "../LIB/std_types.h"						/* Standard types */
#include <util/delay.h>								/* delay utility */

/*********************** Configuration  ***********************/
/* UART configuration structure */
UART_ConfigType config = {
	.baudRate = 9600,
	.dataBits = 8	,
	.parity   = 0	,
	.stopBits = 1 	};

/*********************** Functions Prototypes ***********************/

/*
 * Description : Function to set the motor speed based on the input value.
 * Returns     : The actual speed set for the motor.
 */
uint8 motorSpeed(uint8 speed);

/*
 * Description :
 * 	- Function to handle the auto-parking functionality.
 * 	- This function controls the car's movement to park automatically.
 */
void autoParking(void);

/*
 * Description :
 * 	- Function to read the distance from the ultrasonic sensor.
 * 	- This function retrieves and processes the distance measurement.
 */
void readDistance(void);

void App_Receive(uint8 recievedMSG);

void collisionAvoidance(void);

#endif /* APP_APPLICATION_H_ */
