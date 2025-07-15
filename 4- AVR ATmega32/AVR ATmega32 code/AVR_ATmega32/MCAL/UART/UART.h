/******************************************************************************
 * Module		: UART
 * File Name	: UART.h
 * Author		: A7la Team :)
 * Created on	: 21/11/2024
 * Description	: Header file for the TIMER AVR Driver
 *******************************************************************************/
#ifndef MCAL_UART_UART_H_
#define MCAL_UART_UART_H_

#include <avr/io.h>
#include <stdlib.h>  			/* For itoa */
#include <avr/interrupt.h>
#include "../../LIB/std_types.h"

/* Configuration structure */
typedef struct
{
    uint32 baudRate;
    uint8 dataBits;		/* 5, 6, 7, 8, or 9 */
    uint8 parity;		/* 0 = None, 1 = Even, 2 = Odd */
    uint8 stopBits;		/* 1 or 2 */
} UART_ConfigType;

/* Function prototypes */
void UART_Init(UART_ConfigType *config);
void UART_Transmit(uint8 data);
uint8 UART_Receive(void);

/* Optional: Callbacks for RX and TX interrupts */
void UART_SetRxCallback(void (*callback)(uint8));
void UART_SetTxCallback(void (*callback)(void));

void UART_SendNumbersWithDelimiter(const uint16* numbers, uint8 count, char delimiter);

void UART_sendByte(uint8 data);

void UART_sendString(const uint8 *str);

#endif /* MCAL_UART6_UART_H_ */
