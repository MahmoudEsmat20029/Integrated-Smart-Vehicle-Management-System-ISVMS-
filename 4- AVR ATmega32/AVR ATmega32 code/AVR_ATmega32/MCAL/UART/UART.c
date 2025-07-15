/******************************************************************************
 * Module		: UART
 * File Name	: UART.c
 * Author		: A7la Team :)
 * Created on	: 21/11/2024
 * Description	: Source file for the TIMER AVR Driver
 *******************************************************************************/
#include "../UART/UART.h"

/* Callbacks */
static void (*RxCallback)(uint8) = 0;
static void (*TxCallback)(void) = 0;

void UART_Init(UART_ConfigType *config)
{
    /* Set baud rate */
    uint16 ubrr = (F_CPU / (16 * config->baudRate)) - 1;
    UBRRH = (uint8)(ubrr >> 8);
    UBRRL = (uint8)ubrr;

    /* Set frame format */
    uint8 ucsrb = (1 << RXEN) | (1 << TXEN);  /* Enable RX and TX */
    uint8 ucsrc = (1 << URSEL);	/* URSEL must be 1 when writing to UCSRC */

    /* Data bits */
    switch (config->dataBits)
    {
        case 5: ucsrc |= (0 << UCSZ0) | (0 << UCSZ1); break;
        case 6: ucsrc |= (1 << UCSZ0) | (0 << UCSZ1); break;
        case 7: ucsrc |= (0 << UCSZ0) | (1 << UCSZ1); break;
        case 8: ucsrc |= (1 << UCSZ0) | (1 << UCSZ1); break;
        case 9: ucsrc |= (1 << UCSZ0) | (1 << UCSZ1); ucsrb |= (1 << UCSZ2); break;
    }

    if (config->parity == 1) ucsrc |= (1 << UPM1);	/* Even parity */
    else if (config->parity == 2) ucsrc |= (1 << UPM1) | (1 << UPM0);	/* Odd parity */

    if (config->stopBits == 2) ucsrc |= (1 << USBS);	/* Stop bits */

    // Apply configurations
    UCSRB = ucsrb;
    UCSRC = ucsrc;

    sei();		/* Enable Global Interrupts */
}

/* Transmit data */
void UART_Transmit (uint8 data)
{
    while (!(UCSRA & (1 << UDRE)));  // Wait for empty transmit buffer
    UDR = data;
}

/* Receive data */
uint8 UART_Receive (void)
{
    while (!(UCSRA & (1 << RXC)));  // Wait for data to be received
    return UDR;
}

/* Set RX callback */
void UART_SetRxCallback(void (*callback)(uint8))
{
    RxCallback = callback;
    UCSRB |= (1 << RXCIE);		/* Enable RX interrupt */
}

/* Set TX callback */
void UART_SetTxCallback(void (*callback)(void))
{
    TxCallback = callback;
    UCSRB |= (1 << TXCIE);		/* Enable TX interrupt */
}

ISR (USART_RXC_vect)		/* ISR for RX complete */
{
    if (RxCallback)
    {
        RxCallback(UDR);
    }
}

ISR (USART_TXC_vect)		/* ISR for TX complete */
{
    if (TxCallback)
    {
        TxCallback();
    }
}

void UART_SendNumbersWithDelimiter(const uint16* numbers, uint8 count, char delimiter)
{
    char buffer[10];
    for (uint8 i = 0; i < count; i++)
    {
        itoa(numbers[i], buffer, 10);  /* From integer to string */
        for (uint8 j = 0; buffer[j] != '\0'; j++)
        {
            UART_Transmit(buffer[j]);
        }

        if (i < count - 1)
        {
            UART_Transmit(delimiter);
        }
    }
    UART_Transmit('\n'); 	/* If i want */
}

void UART_sendByte(uint8 data)
{
	while (!( UCSRA & (1<<UDRE)));  // wait until UDR is empty
	UDR = data;                     // send the data
}


void UART_sendString(const uint8 *str)
{
	while(*str != '\0')  // loop until end of string
	{
		UART_sendByte(*str);  // send each character
		str++;  // move to next character
	}
}
