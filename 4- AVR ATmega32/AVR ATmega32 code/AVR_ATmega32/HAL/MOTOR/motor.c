/******************************************************************************
 * Module       : DC Motor
 * File Name    : motor.c
 * Author       : A7la Team :)
 * Created on   : 11/11/2024
 * Description  : Source file for the DC Motor AVR driver
 *******************************************************************************/

#include "motor.h"  /* Include Motor header file */
#include "../../MCAL/GPIO/gpio.h"  /* Include GPIO driver for pin control */
#include "../../MCAL/PWM/pwm.h"  /* Include PWM driver for speed control */
#include <util/delay.h>  /* Include delay utility for timing */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

uint8 max_Speed = 0;  /* Variable to store the maximum speed of the motor */

/*******************************************************************************
 *                       Static Functions Definitions                          *
 *******************************************************************************/

/*
 * Description :
 * Static function to handle the maximum speed of the motor.
 * Parameters  :
 * - speed: The maximum speed to be set.
 */
static void Handel_Max_Speed(uint8 speed)
{
    max_Speed = speed;
}

/*******************************************************************************
 *                       Functions Definitions                                 *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the DC motor.
 * This function sets up the necessary pin directions and stops the motor initially.
 * Parameters  :
 * - MAXSPEED: The maximum speed of the motor (0 to 100).
 */
void DcMotor_Init(uint8 MAXSPEED)
{
    /* Set the maximum speed */
    Handel_Max_Speed(MAXSPEED);

    /* For motor 1 */
    GPIO_setupPinDirection(MOTOR_PORT_CONNECTION, PIN_INT1, PIN_OUTPUT);  /* Set INT1 as output */
    GPIO_setupPinDirection(MOTOR_PORT_CONNECTION, PIN_INT2, PIN_OUTPUT);  /* Set INT2 as output */
    GPIO_setupPinDirection(ENABLE1_PORT_CONNECTION, ENABLE1_PIN, PIN_OUTPUT);  /* Set Enable1 as output */

    /* For motor 2 */
    GPIO_setupPinDirection(MOTOR_PORT_CONNECTION, PIN_INT3, PIN_OUTPUT);  /* Set INT3 as output */
    GPIO_setupPinDirection(MOTOR_PORT_CONNECTION, PIN_INT4, PIN_OUTPUT);  /* Set INT4 as output */
    GPIO_setupPinDirection(ENABLE2_PORT_CONNECTION, ENABLE2_PIN, PIN_OUTPUT);  /* Set Enable2 as output */

    /* Stop the motor at the beginning */
    GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT1, LOGIC_LOW);
    GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT2, LOGIC_LOW);
    GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT3, LOGIC_LOW);
    GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT4, LOGIC_LOW);
}

/*
 * Description :
 * Function to rotate motor 1 in a specific direction and speed.
 * Parameters  :
 * - state: The motor state (STOP, CW, CCW).
 * - speed: The motor speed (0 to 100).
 */
void DcMotor1_Rotate(DcMotor_State state, uint8 speed)
{
    /* Configure PWM for motor 1 */
	Timer_Configuration configrations = {NON_INVERTING, F_CPU_CLOCK, speed};
    PWM_Timer0_Start(&configrations);

    /* Control motor 1 direction */
    switch (state)
    {
    case STOP:
        GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT1, LOGIC_LOW);
        GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT2, LOGIC_LOW);
        break;

    case CW:
        GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT1, LOGIC_HIGH);
        GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT2, LOGIC_LOW);
        break;

    case CCW:
        GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT1, LOGIC_LOW);
        GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT2, LOGIC_HIGH);
        break;
    }
}

/*
 * Description :
 * Function to rotate motor 2 in a specific direction and speed.
 * Parameters  :
 * - state: The motor state (STOP, CW, CCW).
 * - speed: The motor speed (0 to 100).
 */
void DcMotor2_Rotate(DcMotor_State state, uint8 speed)
{
    /* Configure PWM for motor 2 */
	Timer_Configuration configrations = {NON_INVERTING, F_CPU_CLOCK, speed};
    PWM_Timer2_Start(&configrations);

    /* Control motor 2 direction */
    switch (state)
    {
    case STOP:
        GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT3, LOGIC_LOW);
        GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT4, LOGIC_LOW);
        break;

    case CW:
        GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT3, LOGIC_HIGH);
        GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT4, LOGIC_LOW);
        break;

    case CCW:
        GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT3, LOGIC_LOW);
        GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT4, LOGIC_HIGH);
        break;
    }
}

/*
 * Description :
 * Function to move the car forward.
 * This function gradually increases the speed of both motors to move the car forward.
 */
void Forward(void)
{
    for (int i = 0; i <= max_Speed; i = i + 10)
    {
        DcMotor1_Rotate(CCW, i);
        DcMotor2_Rotate(CCW, i);
        _delay_ms(DELAY_MOTOR);
    }
}

/*
 * Description :
 * Function to move the car backward.
 * This function gradually increases the speed of both motors to move the car backward.
 */
void Backward(void)
{
    for (int i = 0; i <= max_Speed; i = i + 10)
    {
        DcMotor1_Rotate(CW, i);
        DcMotor2_Rotate(CW, i);
        _delay_ms(DELAY_MOTOR);
    }
}


/*
 * Description :
 * Function to stop the car.
 * This function stops both motors.
 */
void Stop(void)
{
    DcMotor1_Rotate(STOP, MOTOR_STOP);
    DcMotor2_Rotate(STOP, MOTOR_STOP);
}

/*
 * Description :
 * Function to turn the car right while moving forward.
 * This function stops motor 1 and gradually increases the speed of motor 2.
 */
void Right_Forward(void)
{
    for (int i = 0; i <= max_Speed; i = i + 10)
    {
        DcMotor1_Rotate(STOP, MOTOR_STOP);
        DcMotor2_Rotate(CCW, i);
        _delay_ms(DELAY_MOTOR);
    }
}
void Right_Forward_Parking(uint8 speed)
{
    for (int i = 0; i <= speed; i = i + 10)
    {
        DcMotor1_Rotate(CW, 50);
        DcMotor2_Rotate(CCW, i);
        _delay_ms(DELAY_MOTOR);
    }
}

/*
 * Description :
 * Function to turn the car left while moving forward.
 * This function stops motor 2 and gradually increases the speed of motor 1.
 */
void Left_Forward(void)
{
    for (int i = 0; i <= max_Speed; i = i + 10)
    {
        DcMotor1_Rotate(CCW, i);
        DcMotor2_Rotate(STOP, MOTOR_STOP);
        _delay_ms(DELAY_MOTOR);
    }
}

/*
 * Description :
 * Function to turn the car left while moving forward (for parking).
 * This function stops motor 2 and gradually increases the speed of motor 1 to the maximum speed.
 */
void Left_Forward_Parking(uint8 speed)
{
    for (int i = 0; i <= speed; i = i + 10)
    {
        DcMotor1_Rotate(CCW, i);
        DcMotor2_Rotate(CW, 50);
        _delay_ms(DELAY_MOTOR);
    }
}

/*
 * Description :
 * Function to turn the car right while moving backward.
 * This function stops motor 1 and gradually increases the speed of motor 2.
 */
void Right_Backward(void)
{
    for (int i = 0; i <= max_Speed; i = i + 10)
    {
        DcMotor1_Rotate(STOP, MOTOR_STOP);
        DcMotor2_Rotate(CW, i);
        _delay_ms(DELAY_MOTOR);
    }
}


/*
 * Description :
 * Function to turn the car left while moving backward.
 * This function stops motor 2 and gradually increases the speed of motor 1.
 */
void Left_Backward(void)
{
    for (int i = 0; i <= max_Speed; i = i + 10)
    {
        DcMotor1_Rotate(CW, i);
        DcMotor2_Rotate(STOP, MOTOR_STOP);
        _delay_ms(DELAY_MOTOR);
    }
}

