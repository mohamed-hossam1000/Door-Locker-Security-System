 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the AVR UART driver
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/
#include"common_macros.h"
#include<avr/io.h>
#include "uart.h"

/*
 * Description :
 * initialize the UART with the required baud rate and frame
 */
void UART_init(const UART_ConfigType* config)
{
	uint16 baud_value;
	/* double transmission speed */
	UCSRA=(1<<U2X);
	/* enable data transmission and receiving and disabling interrupts */
	UCSRB=(1<<TXEN)|(1<<RXEN);
	/* URSEL must be 1 to write in register
	 * selecting frame characteristics
	 */
	UCSRC=(1<<URSEL)|(config->parity<<4)|(config->stop_bits<<3)|(config->character_size<<1);
	/* calculating the value to achieve the required baud rate */
	baud_value=(uint16)((F_CPU / (config->baudRate * 8)) - 1);
	UBRRL=baud_value;
	UBRRH=(baud_value>>8);
}

/*
 * Description :
 * Function to send a byte
 */
void UART_sendByte(uint8 data)
{
	/* wait until transmission register is empty */
	while(BIT_IS_CLEAR(UCSRA, UDRE));
	/* send the data */
	UDR=data;
}

/*
 * Description :
 * Function to read a received byte
 */
uint8 UART_receiveByte(void)
{
	/* wait until the entire bit is received */
	while(BIT_IS_CLEAR(UCSRA, RXC));
	/* read the data */
	return UDR;
}

/*
 * Description :
 * Function to send a String
 */
void UART_sendString(uint8* str)
{
	for(; *str!='\0'; str++)
	{
		UART_sendByte(*str);
	}
}

/*
 * Description :
 * Function to read a received String
 */
void UART_receiveString(uint8* str)
{

	/* receive data until the stop byte agreed upon*/
	do
	{
		*str=UART_receiveByte();
		str++;
	}while(*(str-1)!='#');
	/* replace the stop byte with null */
	*(str-1)='\0';
}
