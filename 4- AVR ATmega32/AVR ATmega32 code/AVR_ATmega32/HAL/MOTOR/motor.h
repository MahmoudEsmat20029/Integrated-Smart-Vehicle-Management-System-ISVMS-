/******************************************************************************
 * Module       : DC Motor
 * File Name    : motor.h
 * Author       : A7la Team :)
 * Created on   : 11/11/2024
 * Description  : Header file for the DC Motor AVR driver
 *******************************************************************************/

#ifndef HAL_MOTOR_H_
#define HAL_MOTOR_H_

#include "../../LIB/std_types.h"  /* Include standard types header file */

/*******************************************************************************
 *                                Configurations                               *
 *******************************************************************************/

#define DELAY_MOTOR                 (0)      /* Delay for motor operations (if needed) */
#define MOTOR_STOP                  (0)      /* Motor stop speed */

#define MOTOR_SPEED_ONE             (70)     /* Motor first speed */
#define MOTOR_SPEED_TWO             (85)     /* Motor second speed */
#define MOTOR_MAX_SPEED             (100)    /* Motor maximum speed */

#define MOTOR_PORT_CONNECTION       PORTC_ID /* Motor port connection */
#define PIN_INT1                    PIN4_ID  /* Motor pin INT1 */
#define PIN_INT2                    PIN3_ID  /* Motor pin INT2 */
#define PIN_INT3                    PIN6_ID  /* Motor pin INT3 */
#define PIN_INT4                    PIN7_ID  /* Motor pin INT4 */

#define ENABLE1_PORT_CONNECTION     PORTB_ID /* Enable port connection for motor 1 */
#define ENABLE1_PIN                 PIN3_ID  /* Enable pin for motor 1 */

#define ENABLE2_PORT_CONNECTION     PORTD_ID /* Enable port connection for motor 2 */
#define ENABLE2_PIN                 PIN7_ID  /* Enable pin for motor 2 */

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/* Enum to define the motor states */
typedef enum
{
    STOP,  /* Motor is stopped */
    CW,    /* Motor rotates clockwise */
    CCW    /* Motor rotates counter-clockwise */
} DcMotor_State;

/*******************************************************************************
 *                        Functions Prototypes                                 *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the DC motor.
 * Parameters  :
 * - MAXSPEED: The maximum speed of the motor (0 to 100).
 */
void DcMotor_Init(uint8 MAXSPEED);

/*
 * Description :
 * Function to rotate the motor in a specific direction and speed.
 * Parameters  :
 * - state: The motor state (STOP, CW, CCW).
 * - speed: The motor speed (0 to 100).
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

/*
 * Description :
 * Function to move the car forward.
 */
void Forward(void);

/*
 * Description :
 * Function to move the car backward.
 */
void Backward(void);

/*
 * Description :
 * Function to stop the car.
 */
void Stop(void);

/*
 * Description :
 * Function to turn the car right while moving forward.
 */
void Right_Forward(void);

/*
 * Description :
 * Function to turn the car left while moving forward.
 */
void Left_Forward(void);

/*
 * Description :
 * Function to turn the car left while moving forward (for parking).
 */
void Forward_Parking(uint8 speed);
void Backward_Parking(uint8 speed);
void Right_Forward_Parking(uint8 speed);
void Left_Forward_Parking(uint8 speed);
void Right_Backward_Parking(uint8 speed);
void Left_Backward_Parking(uint8 speed);


/*
 * Description :
 * Function to turn the car right while moving backward.
 */
void Right_Backward(void);

/*
 * Description :
 * Function to turn the car left while moving backward.
 */
void Left_Backward(void);

#endif /* HAL_MOTOR_H_ */
