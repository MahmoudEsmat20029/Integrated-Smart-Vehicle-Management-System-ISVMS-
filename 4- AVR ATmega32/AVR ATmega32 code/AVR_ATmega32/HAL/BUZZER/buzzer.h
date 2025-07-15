/************************************************************************************
 * Module		: Buzzer
 * File Name	: buzzer.h
 * Author		: A7la Team :)
 * Created on	: 16/2/2025
 * Description	: header file for the Buzzer driver
 ************************************************************************************/
#ifndef HAL_BUZZER_BUZZER_H_
#define HAL_BUZZER_BUZZER_H_

#include "../../LIB/std_types.h"
#include "../../MCAL/GPIO/gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_PORT_ID		PORTC_ID		/* Port where the buzzer is connected */
#define BUZZER_PIN_ID		PIN5_ID		/* Pin where the buzzer is connected */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * 		- Function responsible for initializing the buzzer pin as output and turning it off.
 */
void Buzzer_init(void);

/*
 * Description :
 * 		- Function responsible for activating the buzzer.
 */
void Buzzer_on(void);

/*
 * Description :
 * 		- Function responsible for deactivating the buzzer.
 */
void Buzzer_off(void);

#endif /* HAL_BUZZER_BUZZER_H_ */
