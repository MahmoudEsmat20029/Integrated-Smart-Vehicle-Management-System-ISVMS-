/******************************************************************************
 * Module       : LCD
 * File Name    : lcd.h
 * Author       : A7la Team :)
 * Created on   : 23/10/2024
 * Description  : Header file for the LCD driver
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "../../LIB/std_types.h"  /* Include standard types header file */

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* LCD Data bits mode configuration (4 or 8 bits) */
#define LCD_DATA_BITS_MODE 4

#if ((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))
#error "Number of Data bits should be equal to 4 or 8"
#endif

/* LCD HW Ports and Pins Ids */
#define LCD_RS_PORT_ID                 PORTA_ID  /* Port for RS pin */
#define LCD_RS_PIN_ID                  PIN1_ID   /* Pin for RS */

#define LCD_E_PORT_ID                  PORTA_ID  /* Port for Enable pin */
#define LCD_E_PIN_ID                   PIN2_ID   /* Pin for Enable */

#define LCD_DATA_PORT_ID               PORTA_ID  /* Port for data pins */

#if (LCD_DATA_BITS_MODE == 4)
#define LCD_DB4_PIN_ID                 PIN3_ID   /* Pin for DB4 */
#define LCD_DB5_PIN_ID                 PIN4_ID   /* Pin for DB5 */
#define LCD_DB6_PIN_ID                 PIN5_ID   /* Pin for DB6 */
#define LCD_DB7_PIN_ID                 PIN6_ID   /* Pin for DB7 */
#endif

/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01  /* Clear display */
#define LCD_GO_TO_HOME                       0x02  /* Return cursor to home position */
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38  /* 2 lines, 8-bit mode */
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28  /* 2 lines, 4-bit mode */
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33  /* Initialization command 1 for 4-bit mode */
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32  /* Initialization command 2 for 4-bit mode */
#define LCD_CURSOR_OFF                       0x0C  /* Turn cursor off */
#define LCD_CURSOR_ON                        0x0E  /* Turn cursor on */
#define LCD_SET_CURSOR_LOCATION              0x80  /* Set cursor position */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions using the GPIO driver.
 * 2. Setup the LCD Data Mode (4-bits or 8-bits).
 */
void LCD_init(void);

/*
 * Description :
 * Send a command to the LCD.
 * Parameters  :
 * - command: The command to be sent.
 */
void LCD_sendCommand(uint8 command);

/*
 * Description :
 * Display a character on the LCD.
 * Parameters  :
 * - data: The character to be displayed.
 */
void LCD_displayCharacter(uint8 data);

/*
 * Description :
 * Display a string on the LCD.
 * Parameters  :
 * - Str: Pointer to the string to be displayed.
 */
void LCD_displayString(const char *Str);

/*
 * Description :
 * Move the cursor to a specified row and column on the LCD.
 * Parameters  :
 * - row: The row number (0 or 1).
 * - col: The column number (0 to 15).
 */
void LCD_moveCursor(uint8 row, uint8 col);

/*
 * Description :
 * Display a string at a specified row and column on the LCD.
 * Parameters  :
 * - row: The row number (0 or 1).
 * - col: The column number (0 to 15).
 * - Str: Pointer to the string to be displayed.
 */
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *Str);

/*
 * Description :
 * Display an integer value on the LCD.
 * Parameters  :
 * - data: The integer value to be displayed.
 */
void LCD_intgerToString(int data);

/*
 * Description :
 * Clear the LCD screen.
 */
void LCD_clearScreen(void);

#endif /* LCD_H_ */
