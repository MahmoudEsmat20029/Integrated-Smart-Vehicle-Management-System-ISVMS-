/******************************************************************************
 * Module       : PWM
 * File Name    : pwm.h
 * Author       : A7la Team :)
 * Created on   : 15/11/2024
 * Description  : Header file for the PWM AVR driver
 *******************************************************************************/
#ifndef MCAL_PWM_H_
#define MCAL_PWM_H_

#include "../../LIB/std_types.h"  /* Include standard types header file */

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/* Enum to define PWM modes */
typedef enum
{
    NON_INVERTING = 2,  /* Non-inverting PWM mode (clear OC0/OC2 on compare match) */
    INVERTING           /* Inverting PWM mode (set OC0/OC2 on compare match) */
} PWM_Mode;

/* Structure to hold Timer configuration parameters */
typedef struct
{
    PWM_Mode mode;            /* PWM mode (Non-inverting or Inverting) */
    Timer_ClockType timer_clock;  /* Timer clock type (e.g., no prescaler, prescaler 8, etc.) */
    uint8 duty_cycle;         /* Duty cycle percentage (0% to 100%) */
} Timer_Configuration;

/*******************************************************************************
 *                        Functions Prototypes                                 *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize Timer0 with Fast PWM mode.
 * Parameters  :
 * - Config_Ptr: Pointer to the Timer configuration structure.
 */
void PWM_Timer0_Start(const Timer_Configuration * Config_Ptr);

/*
 * Description :
 * Function to initialize Timer2 with Fast PWM mode.
 * Parameters  :
 * - Config_Ptr: Pointer to the Timer configuration structure.
 */
void PWM_Timer2_Start(const Timer_Configuration * Config_Ptr);

#endif /* MCAL_PWM_H_ */
