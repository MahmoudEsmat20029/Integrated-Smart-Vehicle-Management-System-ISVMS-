/******************************************************************************
 * Module       : LCD
 * File Name    : lcd.c
 * Author       : A7la Team :)
 * Created on   : 23/10/2024
 * Description  : Source file for the LCD driver
 *******************************************************************************/

#include <util/delay.h>  /* Include delay utility for timing */
#include "../../LIB/common_macros.h"  /* Include common macros for bit manipulation */
#include "lcd.h"  /* Include LCD header file */
#include "../../MCAL/GPIO/gpio.h"  /* Include GPIO driver for pin control */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions using the GPIO driver.
 * 2. Setup the LCD Data Mode (4-bits or 8-bits).
 */
void LCD_init(void)
{
    /* Configure the direction for RS and E pins as output pins */
    GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);

    _delay_ms(20);  /* LCD Power ON delay (always > 15ms) */

#if (LCD_DATA_BITS_MODE == 4)
    /* Configure 4 pins in the data port as output pins */
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, PIN_OUTPUT);

    /* Send initialization commands for 4-bit mode */
    LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
    LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

    /* Set 2-line LCD, 4-bit mode, and 5x7 dot display */
    LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif (LCD_DATA_BITS_MODE == 8)
    /* Configure the data port as output port */
    GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);

    /* Set 2-line LCD, 8-bit mode, and 5x7 dot display */
    LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#endif

    LCD_sendCommand(LCD_CURSOR_OFF);  /* Turn cursor off */
    LCD_sendCommand(LCD_CLEAR_COMMAND);  /* Clear LCD at the beginning */
}

/*
 * Description :
 * Send a command to the LCD.
 * Parameters  :
 * - command: The command to be sent.
 */
void LCD_sendCommand(uint8 command)
{
    GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);  /* Instruction Mode (RS = 0) */
    _delay_ms(1);  /* Delay for processing (Tas = 50ns) */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);  /* Enable LCD (E = 1) */
    _delay_ms(1);  /* Delay for processing (Tpw - Tdws = 190ns) */

#if (LCD_DATA_BITS_MODE == 4)
    /* Send the higher nibble of the command */
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command, 4));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command, 5));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command, 6));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command, 7));

    _delay_ms(1);  /* Delay for processing (Tdsw = 100ns) */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);  /* Disable LCD (E = 0) */
    _delay_ms(1);  /* Delay for processing (Th = 13ns) */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);  /* Enable LCD (E = 1) */
    _delay_ms(1);  /* Delay for processing (Tpw - Tdws = 190ns) */

    /* Send the lower nibble of the command */
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command, 0));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command, 1));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command, 2));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command, 3));

    _delay_ms(1);  /* Delay for processing (Tdsw = 100ns) */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);  /* Disable LCD (E = 0) */
    _delay_ms(1);  /* Delay for processing (Th = 13ns) */

#elif (LCD_DATA_BITS_MODE == 8)
    /* Send the entire command in 8-bit mode */
    GPIO_writePort(LCD_DATA_PORT_ID, command);  /* Output the command to the data bus (D0-D7) */
    _delay_ms(1);  /* Delay for processing (Tdsw = 100ns) */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);  /* Disable LCD (E = 0) */
    _delay_ms(1);  /* Delay for processing (Th = 13ns) */
#endif
}

/*
 * Description :
 * Display a character on the LCD.
 * Parameters  :
 * - data: The character to be displayed.
 */
void LCD_displayCharacter(uint8 data)
{
    GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);  /* Data Mode (RS = 1) */
    _delay_ms(1);  /* Delay for processing (Tas = 50ns) */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);  /* Enable LCD (E = 1) */
    _delay_ms(1);  /* Delay for processing (Tpw - Tdws = 190ns) */

#if (LCD_DATA_BITS_MODE == 4)
    /* Send the higher nibble of the data */
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(data, 4));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(data, 5));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(data, 6));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(data, 7));

    _delay_ms(1);  /* Delay for processing (Tdsw = 100ns) */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);  /* Disable LCD (E = 0) */
    _delay_ms(1);  /* Delay for processing (Th = 13ns) */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);  /* Enable LCD (E = 1) */
    _delay_ms(1);  /* Delay for processing (Tpw - Tdws = 190ns) */

    /* Send the lower nibble of the data */
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(data, 0));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(data, 1));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(data, 2));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(data, 3));

    _delay_ms(1);  /* Delay for processing (Tdsw = 100ns) */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);  /* Disable LCD (E = 0) */
    _delay_ms(1);  /* Delay for processing (Th = 13ns) */

#elif (LCD_DATA_BITS_MODE == 8)
    /* Send the entire data in 8-bit mode */
    GPIO_writePort(LCD_DATA_PORT_ID, data);  /* Output the data to the data bus (D0-D7) */
    _delay_ms(1);  /* Delay for processing (Tdsw = 100ns) */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);  /* Disable LCD (E = 0) */
    _delay_ms(1);  /* Delay for processing (Th = 13ns) */
#endif
}

/*
 * Description :
 * Display a string on the LCD.
 * Parameters  :
 * - Str: Pointer to the string to be displayed.
 */
void LCD_displayString(const char *Str)
{
    uint8 i = 0;
    while (Str[i] != '\0')
    {
        LCD_displayCharacter(Str[i]);  /* Display each character */
        i++;
    }
}

/*
 * Description :
 * Move the cursor to a specified row and column on the LCD.
 * Parameters  :
 * - row: The row number (0 or 1).
 * - col: The column number (0 to 15).
 */
void LCD_moveCursor(uint8 row, uint8 col)
{
    uint8 lcd_memory_address;

    /* Calculate the required address in the LCD DDRAM */
    switch (row)
    {
    case 0:
        lcd_memory_address = col;
        break;
    case 1:
        lcd_memory_address = col + 0x40;
        break;
    case 2:
        lcd_memory_address = col + 0x10;
        break;
    case 3:
        lcd_memory_address = col + 0x50;
        break;
    }

    /* Move the LCD cursor to this specific address */
    LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/*
 * Description :
 * Display a string at a specified row and column on the LCD.
 * Parameters  :
 * - row: The row number (0 or 1).
 * - col: The column number (0 to 15).
 * - Str: Pointer to the string to be displayed.
 */
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *Str)
{
    LCD_moveCursor(row, col);  /* Move the cursor to the specified position */
    LCD_displayString(Str);  /* Display the string */
}

/*
 * Description :
 * Display an integer value on the LCD.
 * Parameters  :
 * - data: The integer value to be displayed.
 */
void LCD_intgerToString(int data)
{
    char buff[16];  /* String to hold the ASCII result */
    itoa(data, buff, 10);  /* Convert the integer to its ASCII representation (base 10) */
    LCD_displayString(buff);  /* Display the string */
}

/*
 * Description :
 * Clear the LCD screen.
 */
void LCD_clearScreen(void)
{
    LCD_sendCommand(LCD_CLEAR_COMMAND);  /* Send clear display command */
}
