/******************************************************************************
 * Module       : External Interrupts
 * File Name    : external_interrupts.c
 * Author       : A7la Team :)
 * Created on   : 22/12/2024
 * Description  : Source file for the External Interrupts AVR driver
 *******************************************************************************/

#include <avr/io.h>  /* Include AVR I/O header file */
#include <avr/interrupt.h>  /* Include AVR interrupt header file */
#include "EXT_INT.h"  /* Include External Interrupts header file */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the callback function in the application */
static volatile void (*g_callBackPtr_INT0)(void) = NULL_PTR;  /* Callback for INT0 */
static volatile void (*g_callBackPtr_INT1)(void) = NULL_PTR;  /* Callback for INT1 */
static volatile void (*g_callBackPtr_INT2)(void) = NULL_PTR;  /* Callback for INT2 */

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

/*
 * Description :
 * Interrupt Service Routine for INT0.
 * This ISR is called when an interrupt is triggered on INT0.
 */
ISR(INT0_vect)
{
    if (g_callBackPtr_INT0 != NULL_PTR)
    {
        /* Call the callback function in the application after the edge is detected */
        (*g_callBackPtr_INT0)();
    }
}

/*
 * Description :
 * Interrupt Service Routine for INT1.
 * This ISR is called when an interrupt is triggered on INT1.
 */
ISR(INT1_vect)
{
    if (g_callBackPtr_INT1 != NULL_PTR)
    {
        /* Call the callback function in the application after the edge is detected */
        (*g_callBackPtr_INT1)();
    }
}

/*
 * Description :
 * Interrupt Service Routine for INT2.
 * This ISR is called when an interrupt is triggered on INT2.
 */
ISR(INT2_vect)
{
    if (g_callBackPtr_INT2 != NULL_PTR)
    {
        /* Call the callback function in the application after the edge is detected */
        (*g_callBackPtr_INT2)();
    }
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the external interrupt.
 * This function configures the interrupt sense control and enables the interrupt.
 * Parameters  :
 * - a_ptr: Pointer to the external interrupt configuration structure.
 */
void external_interrupt_init(const EXT_INT_ConfigType * a_ptr)
{
    switch (a_ptr->INT_ID)
    {
    case INT_0:
        DDRD &= (~(1 << PD2));  /* Configure INT0/PD2 as input pin */

        /*
         * Configure the sense control for INT0:
         * - Falling edge: ISC00 = 0, ISC01 = 1
         * - Rising edge: ISC00 = 1, ISC01 = 1
         */
        MCUCR = (MCUCR & ~(1 << ISC00 | 1 << ISC01)) | ((a_ptr->INT_Sense) << ISC00);

        /* Enable external interrupt INT0 */
        GICR |= (1 << INT0);
        break;

    case INT_1:
        DDRD &= (~(1 << PD3));  /* Configure INT1/PD3 as input pin */

        /*
         * Configure the sense control for INT1:
         * - Falling edge: ISC10 = 0, ISC11 = 1
         * - Rising edge: ISC10 = 1, ISC11 = 1
         */
        MCUCR = (MCUCR & ~(1 << ISC10 | 1 << ISC11)) | ((a_ptr->INT_Sense) << ISC10);

        /* Enable external interrupt INT1 */
        GICR |= (1 << INT1);
        break;

    case INT_2:
        DDRB &= (~(1 << PB2));  /* Configure INT2/PB2 as input pin */

        /*
         * Configure the sense control for INT2:
         * - Falling edge: ISC2 = 0
         * - Rising edge: ISC2 = 1
         */
        if (a_ptr->INT_Sense == RISING_EDGE_INT2) {
            MCUCSR |= (1 << ISC2);
        } else {
            MCUCSR &= ~(1 << ISC2);
        }

        /* Enable external interrupt INT2 */
        GICR |= (1 << INT2);
        break;
    }
}

/*
 * Description :
 * Function to disable external interrupt via INT_ID.
 * This function disables the specified external interrupt.
 * Parameters  :
 * - INT_ID: The external interrupt ID (INT_0, INT_1, INT_2).
 */
void external_interrupt_deinit(EXT_INT_Type INT_ID)
{
    switch (INT_ID)
    {
    case INT_0:
        /* Clear the sense control bits for INT0 */
        MCUCR &= ~(1 << ISC00) & ~(1 << ISC01);

        /* Disable external interrupt INT0 */
        GICR &= ~(1 << INT0);
        break;

    case INT_1:
        /* Clear the sense control bits for INT1 */
        MCUCR &= ~(1 << ISC10) & ~(1 << ISC11);

        /* Disable external interrupt INT1 */
        GICR &= ~(1 << INT1);
        break;

    case INT_2:
        /* Clear the sense control bit for INT2 */
        MCUCSR &= ~(1 << ISC2);

        /* Disable external interrupt INT2 */
        GICR &= ~(1 << INT2);
        break;
    }
}

/*
 * Description :
 * Function to set the Call Back function address to the required external interrupt.
 * This function assigns the callback function to be called when the specified interrupt occurs.
 * Parameters  :
 * - a_ptr: Pointer to the callback function.
 * - INT_ID: The external interrupt ID (INT_0, INT_1, INT_2).
 */
void external_interrupt_setCallBack(void(*a_ptr)(void), EXT_INT_Type INT_ID)
{
    switch (INT_ID)
    {
    case INT_0:
        g_callBackPtr_INT0 = a_ptr;  /* Set callback for INT0 */
        break;
    case INT_1:
        g_callBackPtr_INT1 = a_ptr;  /* Set callback for INT1 */
        break;
    case INT_2:
        g_callBackPtr_INT2 = a_ptr;  /* Set callback for INT2 */
        break;
    }
}
