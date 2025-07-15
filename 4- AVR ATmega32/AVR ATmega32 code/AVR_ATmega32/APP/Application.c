/******************************************************************************
 * Module       : Application
 * File Name    : Application.c
 * Author       : A7la Team :)
 * Created on   : 22/11/2024
 * Description  : Source file for the Application layer
 *******************************************************************************/
#include "Application.h"

/*********************** Global Variables ***********************/
volatile uint16 g_distanceRight    = 0;
volatile uint16 g_distanceForward  = 0;
volatile uint16 g_distanceBackward = 0;
volatile uint8  g_selection 	   = 0;

/****************** Interrupt Service Routines ******************/
/*
void ISR2(void) {
	Stop();
}

void ISR1(void) {
	Stop();
}
*/

int main(void)
{
	SREG |= (1 << 7);		/* Enable global interrupts */

	UART_Init(&config);
	UART_SetRxCallback(App_Receive);

	LCD_init();
	LEDS_init();
	Buzzer_init();
	DcMotor_Init(MOTOR_SPEED_ONE);

	Ultrasonic_init();

	while (1)
	{
		readDistance();			/* Read distances from Three Ultrasonics */
		collisionAvoidance();	/* Handle collision avoidance mode  */
	}
}

/********************* Functions Definitions *********************/
void App_Receive(uint8 recievedMSG)
{
	g_selection = recievedMSG ;
	switch (recievedMSG)
	{
	case 'F':
		Forward();			/* Move forward */
		break;
	case 'B':
		Backward();			/* Move backward */
		break;
	case 'S':
		Stop();				/* Stop movement */
		break;
	case 'R':
		Right_Forward();	/* Turn right and move forward */
		break;
	case 'L':
		Left_Forward();		/* Turn left and move forward */
		break;
	case 'A':
		Right_Backward();	/* Turn right and move backward */
		break;
	case 'H':
		Left_Backward();	/* Turn left and move backward */
		break;
	case 'P':
		autoParking();		/* Perform auto-parking */
		break;
	case '1':
		DcMotor_Init(MOTOR_SPEED_ONE);	/* Reinitialize motor with new speed */
		break;
	case '2':
		DcMotor_Init(MOTOR_SPEED_TWO);	/* Reinitialize motor with new speed */
		break;
	case '3':
		DcMotor_Init(MOTOR_MAX_SPEED);	/* Reinitialize motor with new speed */
		break;
	}
}

void readDistance(void)
{
	uint16 l_nums[3];

	g_distanceRight = Ultrasonic_readDistance(U_right);

	_delay_ms(100);

	g_distanceForward = Ultrasonic_readDistance(U_forward);

	_delay_ms(100);

	g_distanceBackward = Ultrasonic_readDistance(U_backward);

	_delay_ms(100);

	if(g_distanceRight >= 100)
	{
		g_distanceRight = 99;
	}
	if(g_distanceForward >= 100)
	{
		g_distanceForward = 99;
	}
	if(g_distanceBackward >= 100)
	{
		g_distanceBackward = 99;
	}

	l_nums[0] = g_distanceRight;
	l_nums[1] = g_distanceForward;
	l_nums[2] = g_distanceBackward;

	UART_SendNumbersWithDelimiter(l_nums, 3, ',');
}

void collisionAvoidance(void)
{
	if(g_distanceForward <= 40 && (g_selection == 'F' || g_selection == 'R' || g_selection == 'L'))
	{
		if(g_distanceForward <= 30)
		{
			Backward();
			_delay_ms(100);
			Stop();
			Buzzer_off();
		}
		else
		{
			Buzzer_on();
		}
	}
	else if(g_distanceBackward <= 40 && (g_selection == 'B' || g_selection == 'A' || g_selection == 'H'))
	{
		if(g_distanceBackward <= 30)
		{
			Forward();
			_delay_ms(100);
			Stop();
			Buzzer_off();
		}
		else
		{
			Buzzer_on();
		}
	}
	else
	{
		Buzzer_off();
	}
}

void autoParking (void)
{
	uint8 l_counter = 0;

	LCD_clearScreen();

	_delay_ms(500);

	readDistance();

	Forward();

	while (30 <= g_distanceRight)
	{
		readDistance();
		collisionAvoidance();

		_delay_ms(100);

		l_counter++;
		if (5 < l_counter)
		{
			LCD_displayStringRowColumn(1, 0, "SPACE Available");

			Stop();

			_delay_ms(500);

			Left_Forward_Parking(100);
			_delay_ms(500);
			Backward();
			_delay_ms(100);
			Left_Forward_Parking(100);
			_delay_ms(500);
			Backward();
			_delay_ms(100);
			Left_Forward_Parking(100);
			_delay_ms(500);

			Stop();
			_delay_ms(500);

			Backward();
			_delay_ms(900);

			Stop();

			_delay_ms(500);

			Right_Forward_Parking(100);
			_delay_ms(700);
			Backward();
			_delay_ms(500);
			Right_Forward_Parking(100);
			_delay_ms(700);
			Backward();
			_delay_ms(500);
			Right_Forward_Parking(100);
			_delay_ms(700);
			Backward();
			_delay_ms(200);
			Right_Forward_Parking(100);
			_delay_ms(700);
			Backward();
			_delay_ms(200);
			Right_Forward_Parking(100);
			_delay_ms(200);
			Stop();
			_delay_ms(700);
			_delay_ms(700);

			break;
		}
	}
	if (5 > l_counter)
	{
		LCD_displayStringRowColumn(1, 0, "NO SPACE");
	}

	Stop();
}
