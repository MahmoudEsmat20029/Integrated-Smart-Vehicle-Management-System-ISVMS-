/******************************************************************************
 * Module       : ICU
 * File Name    : icu.c
 * Author       : A7la Team :)
 * Created on   : 15/11/2024
 * Description  : Source file for the ICU AVR driver
 *******************************************************************************/

#include "icu.h"  /* Include ICU header file */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variable to hold the address of the callback function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

/*
 * Description :
 * Interrupt Service Routine for Timer1 Input Capture Event.
 * This ISR is triggered when an edge is detected on the ICP1/PD6 pin.
 */
ISR(TIMER1_CAPT_vect)
{
    if (g_callBackPtr != NULL_PTR)
    {
        /* Call the callback function in the application after the edge is detected */
        (*g_callBackPtr)();  /* Another method: g_callBackPtr(); */
    }
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the ICU driver:
 * 1. Set the required clock.
 * 2. Set the required edge detection.
 * 3. Enable the Input Capture Interrupt.
 * 4. Initialize Timer1 Registers.
 * Parameters  :
 * - Config_Ptr: Pointer to the ICU configuration structure.
 */
void ICU_init(const ICU_ConfigType * Config_Ptr)
{
    /* Configure ICP1/PD6 as an input pin (DDRD &= ~(1<<PD6)) */
    DDRD &= ~(1<<PD6);

    /* Timer1 always operates in Normal Mode (WGM13:0 = 0000) */
    TCCR1A = (1<<FOC1A) | (1<<FOC1B);  /* Force Output Compare for non-PWM mode */

    /*
     * Insert the required clock value in the first three bits (CS10, CS11, and CS12)
     * of the TCCR1B Register.
     */
    TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock);

    /*
     * Insert the required edge type in the ICES1 bit of the TCCR1B Register.
     * ICES1 = 0: Falling edge detection.
     * ICES1 = 1: Rising edge detection.
     */
    TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->edge)<<6);

    /* Initialize Timer1 counter value to 0 */
    TCNT1 = 0;

    /* Initialize the Input Capture Register (ICR1) to 0 */
    ICR1 = 0;

    /* Enable the Input Capture interrupt to generate an interrupt when an edge is detected on ICP1/PD6 pin */
    TIMSK |= (1<<TICIE1);

    /* Enable global interrupts (SREG |= (1<<7)) */
    SREG |= (1<<7);
}

/*
 * Description :
 * Function to set the callback function address.
 * Parameters  :
 * - a_ptr: Pointer to the callback function.
 */
void ICU_setCallBack(void(*a_ptr)(void))
{
    /* Save the address of the callback function in a global variable */
    g_callBackPtr = a_ptr;
}

/*
 * Description :
 * Function to set the required edge detection.
 * Parameters  :
 * - a_edgeType: The edge detection type (FALLING or RAISING).
 */
void ICU_setEdgeDetectionType(const ICU_EdgeType a_edgeType)
{
    /*
     * Insert the required edge type in the ICES1 bit of the TCCR1B Register.
     * ICES1 = 0: Falling edge detection.
     * ICES1 = 1: Rising edge detection.
     */
    TCCR1B = (TCCR1B & 0xBF) | (a_edgeType<<6);
}

/*
 * Description :
 * Function to get the Timer1 value when the input is captured.
 * The value is stored in the Input Capture Register (ICR1).
 * Returns     :
 * - The captured value from ICR1.
 */
uint16 ICU_getInputCaptureValue(void)
{
    return ICR1;
}

/*
 * Description :
 * Function to clear the Timer1 value to start counting from ZERO.
 */
void ICU_clearTimerValue(void)
{
    TCNT1 = 0;
}

/*
 * Description :
 * Function to disable Timer1 to stop the ICU driver.
 */
void ICU_deInit(void)
{
    /* Clear all Timer1/ICU registers */
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    ICR1 = 0;

    /* Disable the Input Capture interrupt */
    TIMSK &= ~(1<<TICIE1);

    /* Reset the global callback pointer to NULL */
    g_callBackPtr = NULL_PTR;
}
