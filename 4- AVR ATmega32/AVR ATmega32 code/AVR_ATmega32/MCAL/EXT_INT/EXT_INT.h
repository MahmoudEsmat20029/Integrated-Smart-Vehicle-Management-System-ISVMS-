/******************************************************************************
 * Module       : External Interrupts
 * File Name    : external_interrupts.h
 * Author       : A7la Team :)
 * Created on   : 22/12/2024
 * Description  : Header file for the External Interrupts AVR driver
 *******************************************************************************/

#ifndef MCAL_EXTERNAL_INTERRUPTS_H_
#define MCAL_EXTERNAL_INTERRUPTS_H_

#include "../../LIB/std_types.h"  /* Include standard types header file */

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/* Enum to define the external interrupt types. */
typedef enum
{
    INT_0,  /* External Interrupt 0 */
    INT_1,  /* External Interrupt 1 */
    INT_2   /* External Interrupt 2 */
} EXT_INT_Type;

/* Enum to define the sense control for external interrupts. */
typedef enum
{
    FALLING_EDGE = 2,  /* Falling edge triggers the interrupt (for INT0 and INT1) */
    RISING_EDGE,       /* Rising edge triggers the interrupt (for INT0 and INT1) */
    FALLING_EDGE_INT2 = 0,  /* Falling edge triggers the interrupt (for INT2) */
    RISING_EDGE_INT2   /* Rising edge triggers the interrupt (for INT2) */
} EXT_INT_Sense;

/* Structure to configure the external interrupt. */
typedef struct
{
    EXT_INT_Type INT_ID;    /* Interrupt ID (INT0, INT1, INT2) */
    EXT_INT_Sense INT_Sense; /* Interrupt sense control (Falling, Rising) */
} EXT_INT_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the external interrupt.
 * This function configures the interrupt sense control and enables the interrupt.
 * Parameters  :
 * - a_ptr: Pointer to the external interrupt configuration structure.
 */
void external_interrupt_init(const EXT_INT_ConfigType * a_ptr);

/*
 * Description :
 * Function to disable external interrupt via INT_ID.
 * This function disables the specified external interrupt.
 * Parameters  :
 * - INT_ID: The external interrupt ID (INT_0, INT_1, INT_2).
 */
void external_interrupt_deinit(EXT_INT_Type INT_ID);

/*
 * Description :
 * Function to set the Call Back function address to the required external interrupt.
 * This function assigns the callback function to be called when the specified interrupt occurs.
 * Parameters  :
 * - a_ptr: Pointer to the callback function.
 * - INT_ID: The external interrupt ID (INT_0, INT_1, INT_2).
 */
void external_interrupt_setCallBack(void(*a_ptr)(void), EXT_INT_Type INT_ID);

#endif /* MCAL_EXTERNAL_INTERRUPTS_H_ */
