/******************************************************************************
 * Module		: TIMER
 * File Name	: timer.h
 * Author		: A7la Team :)
 * Created on	: 21/11/2024
 * Description	: Header file for the TIMER AVR Driver
 *******************************************************************************/
#ifndef MCAL_TIMER_H_
#define MCAL_TIMER_H_

#include "../../LIB/std_types.h"
#include <avr/interrupt.h>
#include <avr/io.h>

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/* Enum to define Timer IDs */
typedef enum
{
	TIMER0_ID, TIMER1_ID, TIMER2_ID
} Timer_ID_Type;

/* Enum to define Timer clock sources */

/* Enum to define Timer modes */
typedef enum
{
	NORMAL_MODE, COMPARE_MODE
} Timer_ModeType;

/* Structure to configure the Timer */
typedef struct
{
	uint16 timer_InitialValue;          /* Initial value for the timer */
	uint16 timer_compare_MatchValue;    /* Compare match value, used in compare mode only */
	Timer_ID_Type timer_ID;             /* Timer ID */
	Timer_ClockType timer_clock;        /* Clock source for the timer */
	Timer_ModeType timer_mode;          /* Mode of the timer */
} Timer_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function to initialize the Timer driver.
 * Config_Ptr: Pointer to the Timer configuration structure.
 */
void Timer_init(const Timer_ConfigType * Config_Ptr);

/*
 * Function to disable the Timer via Timer_ID.
 * timer_type: The ID of the timer to be disabled.
 */
void Timer_deInit(Timer_ID_Type timer_type);

/*
 * Function to get the Timer Value.
 * timer_type: The ID of the timer to get the value from.
 * Returns: The current value of the timer.
 */
uint16 Timer_getTimerValue(Timer_ID_Type timer_type);

/*
 * Function to set the Call Back function address to the required Timer.
 * a_ptr: Pointer to the callback function.
 * a_timer_ID: The ID of the timer to set the callback for.
 */
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID);

#endif /* MCAL_TIMER_H_ */
