/******************************************************************************
 * Module       : PWM
 * File Name    : pwm.c
 * Author       : A7la Team :)
 * Created on   : 15/11/2024
 * Description  : Source file for the PWM AVR driver
 *******************************************************************************/
#include "pwm.h"  /* Include PWM header file */
#include <avr/io.h>  /* Include AVR I/O header file */

/*******************************************************************************
 *                       Functions Definitions                                 *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize Timer0 with Fast PWM mode.
 * Parameters  :
 * - Config_Ptr: Pointer to the Timer configuration structure.
 */
void PWM_Timer0_Start(const Timer_Configuration * Config_Ptr)
{
    TCNT0 = 0;  /* Set Timer Initial value to 0. */

    /* Calculate and set the Compare Value (OCR0) for the desired duty cycle.
     * Duty cycle is given as a percentage (0-100), and OCR0 is calculated as:
     * OCR0 = (duty_cycle * 255) / 100
     */
    OCR0  = (Config_Ptr->duty_cycle * 255) / 100;

    /* Set PB3/OC0 as output pin (DDRB |= (1<<PB3)).
     * This is the pin where the PWM signal will be generated.
     */
    DDRB  = DDRB | (1<<PB3);

    /* Configure Timer/Counter Control Register for Timer0 (TCCR0):
     * 1. Fast PWM mode (WGM01:0 = 11).
     * 2. Set Compare Output Mode (COM01:0) based on the selected PWM mode:
     *    - NON_INVERTING: Clear OC0 on compare match.
     *    - INVERTING: Set OC0 on compare match.
     * 3. Set clock source (CS02:0) as per Config_Ptr->timer_clock.
     */
    TCCR0 = (1<<WGM00) | (1<<WGM01) | ((Config_Ptr->mode)<<COM00) | ((Config_Ptr->timer_clock)<<CS00);
}

/*
 * Description :
 * Function to initialize Timer2 with Fast PWM mode.
 * Parameters  :
 * - Config_Ptr: Pointer to the Timer configuration structure.
 */
void PWM_Timer2_Start(const Timer_Configuration * Config_Ptr)
{
    TCNT2 = 0;  /* Set Timer Initial value to 0. */

    /* Calculate and set the Compare Value (OCR2) for the desired duty cycle.
     * Duty cycle is given as a percentage (0-100), and OCR2 is calculated as:
     * OCR2 = (duty_cycle * 255) / 100
     */
    OCR2  = (Config_Ptr->duty_cycle * 255) / 100;

    /* Set PD7/OC2 as output pin (DDRD |= (1<<PD7)).
     * This is the pin where the PWM signal will be generated.
     */
    DDRD  = DDRD | (1<<PD7);

    /* Configure Timer/Counter Control Register for Timer2 (TCCR2):
     * 1. Fast PWM mode (WGM21:0 = 11).
     * 2. Set Compare Output Mode (COM21:0) based on the selected PWM mode:
     *    - NON_INVERTING: Clear OC2 on compare match.
     *    - INVERTING: Set OC2 on compare match.
     * 3. Set clock source (CS22:0) as per Config_Ptr->timer_clock.
     */
    TCCR2 = (1<<WGM20) | (1<<WGM21) | ((Config_Ptr->mode)<<COM20) | ((Config_Ptr->timer_clock)<<CS20);
}
