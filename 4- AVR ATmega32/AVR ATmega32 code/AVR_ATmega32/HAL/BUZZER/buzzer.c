/************************************************************************************
 * Module		: Buzzer
 * File Name	: buzzer.c
 * Author		: A7la Team :)
 * Created on	: 16/2/2025
 * Description	: source file for the Buzzer driver
 ************************************************************************************/
#include "buzzer.h"

void Buzzer_init(void)
{
    /* Set the buzzer pin as output */
    GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);

    /* Turn off the buzzer initially */
    Buzzer_off();
}

void Buzzer_on(void)
{
    /* Activate the buzzer */
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

void Buzzer_off(void)
{
    /* Deactivate the buzzer */
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
