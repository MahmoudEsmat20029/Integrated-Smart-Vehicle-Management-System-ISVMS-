/******************************************************************************
 * Module		: TIMER
 * File Name	: timer.c
 * Author		: A7la Team :)
 * Created on	: 21/11/2024
 * Description	: Source file for the TIMER AVR Driver
 *******************************************************************************/
#include "timer.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr_timer0)(void) = NULL_PTR;
static volatile void (*g_callBackPtr_timer1)(void) = NULL_PTR;
static volatile void (*g_callBackPtr_timer2)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
/*
 * ISR For Timer0 Overflow
 */
ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr_timer0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the overflow interrupt */
		(*g_callBackPtr_timer0)();
	}
}

/*
 * ISR For Timer0 Compare Match
 */
ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr_timer0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the compare match interrupt */
		(*g_callBackPtr_timer0)();
	}
}

/*
 * ISR For Timer1 Overflow
 */
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr_timer1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the overflow interrupt */
		(*g_callBackPtr_timer1)();
	}
}

/*
 * ISR For Timer1 Compare Match A
 */
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr_timer1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the compare match interrupt */
		(*g_callBackPtr_timer1)();
	}
}

/*
 * ISR For Timer2 Overflow
 */
ISR(TIMER2_OVF_vect)
{
	if(g_callBackPtr_timer2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the overflow interrupt */
		(*g_callBackPtr_timer2)();
	}
}

/*
 * ISR For Timer2 Compare Match
 */
ISR(TIMER2_COMP_vect)
{
	if(g_callBackPtr_timer2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the compare match interrupt */
		(*g_callBackPtr_timer2)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Function to initialize the Timer driver.
 * Config_Ptr: Pointer to the Timer configuration structure.
 */
void Timer_init(const Timer_ConfigType * Config_Ptr)
{
	switch(Config_Ptr->timer_ID)
	{
	case TIMER0_ID:
		/*
		 * FOC0 = 1 when the WGM00 bit specifies a non-PWM mode.
		 * Normal Mode WGM01=0 & WGM00=0
		 * Compare Mode WGM01=1 & WGM00=0
		 * Set clock as we need from CS00 & CS01 & CS02.
		 */
		TCCR0 = (1<<FOC0) | ((Config_Ptr->timer_mode)<<WGM01) | ((Config_Ptr->timer_clock)<<CS00);

		/* Set Timer/Counter Register – TCNT0 */
		TCNT0 = Config_Ptr->timer_InitialValue;

		if((Config_Ptr->timer_mode) == COMPARE_MODE)
		{
			/* Set Output Compare Register – OCR0 */
			OCR0 = Config_Ptr->timer_compare_MatchValue;
		}

		/*
		 * Enable interrupt for overflow (normal) mode if used.
		 * Enable interrupt for compare mode if used.
		 */
		if((Config_Ptr->timer_mode) == NORMAL_MODE)
		{
			TIMSK |= (1<<TOIE0);
		}
		else
		{
			TIMSK |= (1<<OCIE0);
		}
		break;

	case TIMER1_ID:
		/*
		 * The FOC1A/FOC1B = 1 when the WGM13:0 bits specifies a non-PWM mode.
		 * Normal mode WGM10 = 0, WGM11 = 0, WGM12 = 0; WGM13 = 0
		 * Compare mode WGM10 = 0, WGM11 = 0, WGM12 = 1; WGM13 = 0
		 * Set clock as we need from CS10 & CS11 & CS12.
		 */
		TCCR1A = (1<<FOC1A) | (1<<FOC1B);
		TCCR1B = ((Config_Ptr->timer_mode)<<WGM12) | ((Config_Ptr->timer_clock)<<CS10);

		/* Set Timer/Counter1 – TCNT1H and TCNT1L */
		TCNT1 = Config_Ptr->timer_InitialValue;

		if((Config_Ptr->timer_mode) == COMPARE_MODE)
		{
			/* Set Output Compare Register 1 A – OCR1AH and OCR1AL */
			OCR1A = Config_Ptr->timer_compare_MatchValue;
		}

		/*
		 * Enable interrupt for overflow (normal) mode if used.
		 * Enable interrupt for compare mode if used.
		 */
		if((Config_Ptr->timer_mode) == NORMAL_MODE)
		{
			TIMSK |= (1<<TOIE1);
		}
		else
		{
			TIMSK |= (1<<OCIE1A);
		}
		break;

	case TIMER2_ID:
		/*
		 * FOC0 = 1 when the WGM00 bit specifies a non-PWM mode.
		 * Normal Mode WGM01=0 & WGM00=0
		 * Compare Mode WGM01=1 & WGM00=0
		 * Set clock as we need from CS20 & CS21 & CS22.
		 */
		TCCR2 = (1<<FOC2) | ((Config_Ptr->timer_mode)<<WGM21) | ((Config_Ptr->timer_clock)<<CS20);

		/* Set Timer/Counter Register – TCNT2 */
		TCNT2 = Config_Ptr->timer_InitialValue;

		if((Config_Ptr->timer_mode) == COMPARE_MODE)
		{
			/* Set Output Compare Register – OCR2 */
			OCR2 = Config_Ptr->timer_compare_MatchValue;
		}

		/*
		 * Enable interrupt for overflow (normal) mode if used.
		 * Enable interrupt for compare mode if used.
		 */
		if((Config_Ptr->timer_mode) == NORMAL_MODE)
		{
			TIMSK |= (1<<TOIE2);
		}
		else
		{
			TIMSK |= (1<<OCIE2);
		}
		break;
	}
}

/*
 * Function to disable the Timer via Timer_ID.
 * timer_type: The ID of the timer to be disabled.
 */
void Timer_deInit(Timer_ID_Type timer_type)
{
	switch(timer_type)
	{
	case TIMER0_ID:
		/*
		 * Reset settings.
		 * Disable clock.
		 */
		TCCR0 = 0;

		/* Reset Timer/Counter Register – TCNT0 */
		TCNT0 = 0;

		/* Reset Output Compare Register – OCR0 */
		OCR0 = 0;

		/*
		 * Disable interrupt for overflow (normal) mode if used.
		 * Disable interrupt for compare mode if used.
		 */
		TIMSK &= ~(1<<TOIE0);
		TIMSK &= ~(1<<OCIE0);
		break;

	case TIMER1_ID:
		/*
		 * Reset settings.
		 * Disable clock.
		 */
		TCCR1A = 0;
		TCCR1B = 0;

		/* Reset Timer/Counter1 – TCNT1H and TCNT1L */
		TCNT1 = 0;

		/* Reset Output Compare Register 1 A – OCR1AH and OCR1AL */
		OCR1A = 0;

		/*
		 * Disable interrupt for overflow (normal) mode if used.
		 * Disable interrupt for compare mode if used.
		 */
		TIMSK &= ~(1<<TOIE1);
		TIMSK &= ~(1<<OCIE1A);
		break;

	case TIMER2_ID:
		/*
		 * Reset settings.
		 * Disable clock.
		 */
		TCCR2 = 0;

		/* Reset Timer/Counter Register – TCNT2 */
		TCNT2 = 0;

		/* Reset Output Compare Register – OCR2 */
		OCR2 = 0;

		/*
		 * Disable interrupt for overflow (normal) mode if used.
		 * Disable interrupt for compare mode if used.
		 */
		TIMSK &= ~(1<<TOIE2);
		TIMSK &= ~(1<<OCIE2);
		break;
	}
}

/*
 * Function to get the Timer Value.
 * timer_type: The ID of the timer to get the value from.
 * Returns: The current value of the timer.
 */
uint16 Timer_getTimerValue(Timer_ID_Type timer_type)
{
	switch(timer_type)
	{
	case TIMER0_ID:
		return TCNT0;
		break;
	case TIMER1_ID:
		return TCNT1;
		break;
	case TIMER2_ID:
		return TCNT2;
		break;
	}
}

/*
 * Function to set the Call Back function address to the required Timer.
 * a_ptr: Pointer to the callback function.
 * timer_type: The ID of the timer to set the callback for.
 */
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type timer_type)
{
	switch(timer_type)
	{
	case TIMER0_ID:
		g_callBackPtr_timer0 = a_ptr;
		break;
	case TIMER1_ID:
		g_callBackPtr_timer1 = a_ptr;
		break;
	case TIMER2_ID:
		g_callBackPtr_timer2 = a_ptr;
		break;
	}
}
