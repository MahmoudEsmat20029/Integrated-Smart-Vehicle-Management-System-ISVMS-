/******************************************************************************
 * Module       : Ultrasonic Sensor
 * File Name    : ultrasonic_sensor.c
 * Author       : A7la Team :)
 * Created on   : 28/01/2025 --> "Edited in 24/02/2025"
 * Description  : Source file for the Ultrasonic Sensor driver
 *******************************************************************************/
#include "ultrasonic_sensor.h"  /* Include Ultrasonic Sensor header file */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
volatile static uint16 g_highTime_INT0 = 0;	/* Stores the high time (pulse width) */
volatile static uint8 g_edgeTime_INT0 = 0;	/* Tracks the number of edges detected */

volatile static uint16 g_highTime_INT1 = 0;	/* Stores the high time (pulse width) */
volatile static uint8 g_edgeTime_INT1 = 0;	/* Tracks the number of edges detected */

/*******************************************************************************
 *                      	Functions Prototypes                               *
 *******************************************************************************/
static void Ultrasonic_edgeProcessing_INT0(void);
static void Ultrasonic_edgeProcessing_INT2(void);

/*******************************************************************************
 *                      	Functions Definitions                              *
 *******************************************************************************/
void Ultrasonic_init(void)
{
	EXT_INT_ConfigType EXT_INT0_Configrations = {INT_0, RISING_EDGE};
	external_interrupt_setCallBack(Ultrasonic_edgeProcessing_INT0, INT_0); /* Set the callback function for INT0 */
	external_interrupt_init(&EXT_INT0_Configrations);	/* Initialize INT0 with the specified configuration */

	EXT_INT_ConfigType EXT_INT2_Configrations = {INT_1, RISING_EDGE};
	external_interrupt_setCallBack(Ultrasonic_edgeProcessing_INT2, INT_1); /* Set the callback function for INT2 */
	external_interrupt_init(&EXT_INT2_Configrations);	/* Initialize INT2 with the specified configuration */

	/* Set up pin direction for trigger pin as output */
	GPIO_setupPinDirection(TRIGGERS_PORT_CONNECTION, TRIGGER1_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(TRIGGERS_PORT_CONNECTION, TRIGGER2_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(TRIGGERS_PORT_CONNECTION, TRIGGER3_PIN, PIN_OUTPUT);
}

static void Ultrasonic_Trigger(Ultrasonic ultrasonic)
{
	switch(ultrasonic)
	{
	case U_right:
		/* Set the trigger pin to high for 10us */
		GPIO_writePin(TRIGGERS_PORT_CONNECTION, TRIGGER1_PIN, LOGIC_HIGH);
		_delay_us(10);
		/* Set the trigger pin back to low */
		GPIO_writePin(TRIGGERS_PORT_CONNECTION, TRIGGER1_PIN, LOGIC_LOW);
		break;

	case U_forward:
		/* Set the trigger pin to high for 10us */
		GPIO_writePin(TRIGGERS_PORT_CONNECTION, TRIGGER2_PIN, LOGIC_HIGH);
		_delay_us(10);
		/* Set the trigger pin back to low */
		GPIO_writePin(TRIGGERS_PORT_CONNECTION, TRIGGER2_PIN, LOGIC_LOW);
		break;

	case U_backward:
		/* Set the trigger pin to high for 10us */
		GPIO_writePin(TRIGGERS_PORT_CONNECTION, TRIGGER3_PIN, LOGIC_HIGH);
		_delay_us(10);
		/* Set the trigger pin back to low */
		GPIO_writePin(TRIGGERS_PORT_CONNECTION, TRIGGER3_PIN, LOGIC_LOW);
		break;

	}

}

uint16 Ultrasonic_readDistance (Ultrasonic ultrasonic)
{
	switch(ultrasonic)
	{
	case U_right:
		/* Send the trigger pulse to start the measurement */
		Ultrasonic_Trigger(U_right);

		/* Calculate the distance in centimeters using the high time */
		return (g_highTime_INT0 * 1.088) + 1;
		break;

	case U_forward:
		/* Send the trigger pulse to start the measurement */
		Ultrasonic_Trigger(U_forward);

		/* Calculate the distance in centimeters using the high time */
		return (g_highTime_INT1 * 1.088) + 1;
		break;

	case U_backward:
		/* Send the trigger pulse to start the measurement */
		Ultrasonic_Trigger(U_backward);

		/* Calculate the distance in centimeters using the high time */
		return (g_highTime_INT0 * 1.088) + 1;
		break;
	}
}

static void Ultrasonic_edgeProcessing_INT0(void)
{
	g_edgeTime_INT0++; 	// Increment edge count

	if (1 == g_edgeTime_INT0) {
		/* Rising edge detected */
		Timer_deInit(TIMER1_ID); // De-initialize Timer1

		external_interrupt_deinit(INT_0); // De-initialize INT2
		EXT_INT_ConfigType EXT_INT0_Configrations = {INT_0, FALLING_EDGE}; // Configure INT2 for falling edge detection
		external_interrupt_init(&EXT_INT0_Configrations); // Reinitialize INT2 with the new configuration

		Timer_ConfigType Timer_Configrations = {0, 0, TIMER1_ID, F_CPU_1024, NORMAL_MODE}; // Configure Timer1
		Timer_init(&Timer_Configrations); // Initialize Timer1

	} else if (2 == g_edgeTime_INT0) {
		/* Falling edge detected */
		g_highTime_INT0 = Timer_getTimerValue(TIMER1_ID); // Calculate pulse width

		Timer_deInit(TIMER1_ID);	/* De-initialize Timer1 */

		external_interrupt_deinit(INT_0);	/* De-initialize INT2 */
		EXT_INT_ConfigType EXT_INT0_Configrations = {INT_0, RISING_EDGE};	/* Configure INT2 for rising edge detection */
		external_interrupt_init(&EXT_INT0_Configrations);	/* Reinitialize INT2 with the new configuration */

		g_edgeTime_INT0 = 0;		/* Reset edge count */
	}
}

static void Ultrasonic_edgeProcessing_INT2(void)
{
	g_edgeTime_INT1++; 	// Increment edge count

	if (1 == g_edgeTime_INT1) {
		/* Rising edge detected */
		Timer_deInit(TIMER1_ID); // De-initialize Timer1

		external_interrupt_deinit(INT_1); // De-initialize INT2
		EXT_INT_ConfigType EXT_INT2_Configrations = {INT_1, FALLING_EDGE}; // Configure INT2 for falling edge detection
		external_interrupt_init(&EXT_INT2_Configrations); // Reinitialize INT2 with the new configuration

		Timer_ConfigType Timer_Configrations = {0, 0, TIMER1_ID, F_CPU_1024, NORMAL_MODE}; // Configure Timer1
		Timer_init(&Timer_Configrations); // Initialize Timer1

	} else if (2 == g_edgeTime_INT1) {
		/* Falling edge detected */
		g_highTime_INT1 = Timer_getTimerValue(TIMER1_ID); // Calculate pulse width

		Timer_deInit(TIMER1_ID);	/* De-initialize Timer1 */

		external_interrupt_deinit(INT_1);	/* De-initialize INT2 */
		EXT_INT_ConfigType EXT_INT2_Configrations = {INT_1, RISING_EDGE};	/* Configure INT2 for rising edge detection */
		external_interrupt_init(&EXT_INT2_Configrations);	/* Reinitialize INT2 with the new configuration */

		g_edgeTime_INT1 = 0;		/* Reset edge count */
	}
}
