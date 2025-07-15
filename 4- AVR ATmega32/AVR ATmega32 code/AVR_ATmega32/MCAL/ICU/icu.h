/******************************************************************************
 * Module       : ICU
 * File Name    : icu.h
 * Author       : A7la Team :)
 * Created on   : 15/11/2024
 * Description  : Header file for the ICU AVR driver
 *******************************************************************************/

#ifndef MCAL_ICU_H_
#define MCAL_ICU_H_

#include <avr/io.h>  /* Include AVR I/O header file */
#include <avr/interrupt.h>  /* Include AVR interrupt header file */
#include "../../LIB/common_macros.h"  /* Include common macros header file */
#include "../../LIB/std_types.h"  /* Include standard types header file */

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/* Enum to define ICU edge detection types */
typedef enum
{
    FALLING,  /* Trigger on falling edge */
    RAISING   /* Trigger on rising edge */
} ICU_EdgeType;

/* Structure to hold ICU configuration parameters */
typedef struct
{
    Timer_ClockType clock;  /* Timer clock type (e.g., no prescaler, prescaler 8, etc.) */
    ICU_EdgeType edge;  /* Edge detection type (FALLING or RAISING) */
} ICU_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
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
void ICU_init(const ICU_ConfigType * Config_Ptr);

/*
 * Description :
 * Function to set the Call Back function address.
 * Parameters  :
 * - a_ptr: Pointer to the callback function.
 */
void ICU_setCallBack(void(*a_ptr)(void));

/*
 * Description :
 * Function to set the required edge detection.
 * Parameters  :
 * - edgeType: The edge detection type (FALLING or RAISING).
 */
void ICU_setEdgeDetectionType(const ICU_EdgeType edgeType);

/*
 * Description :
 * Function to get the Timer1 Value when the input is captured.
 * The value is stored at the Input Capture Register (ICR1).
 * Returns     :
 * - The captured value from ICR1.
 */
uint16 ICU_getInputCaptureValue(void);

/*
 * Description :
 * Function to clear the Timer1 Value to start counting from ZERO.
 */
void ICU_clearTimerValue(void);

/*
 * Description :
 * Function to disable Timer1 to stop the ICU Driver.
 */
void ICU_deInit(void);

#endif /* MCAL_ICU_H_ */
