 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the AVR UART driver
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_
#include"std_types.h"

/*******************************************************************************
 * 									Types Declarations
 *******************************************************************************/
typedef enum{
	DISABLED=0, EVEN_PARIT=2, ODD_PARITY=3
}UART_parityMode;

typedef enum{
	ONE_BIT, TWO_BITS
}UART_NO_OF_STOP_BITS;

typedef enum{
	FIVE_BITS, SIX_BITS, SEVEN_BITS, EIGHT_BITS
}UART_characterSize;

typedef struct{
	uint32 		   		 baudRate;
	UART_characterSize	 character_size;
	UART_parityMode 	 parity;
	UART_NO_OF_STOP_BITS stop_bits;
}UART_configType;

/*******************************************************************************
 * 									Functions Prototypes
 *******************************************************************************/

/*
 * Description :
 * initialize the UART with the required baud rate and frame
 */
void UART_init(const UART_configType* config);

/*
 * Description :
 * Function to send a byte
 */
void UART_sendByte(uint8 data);

/*
 * Description :
 * Function to read a received byte
 */
uint8 UART_receiveByte(void);

/*
 * Description :
 * Function to send a string
 */
void UART_sendString(sint8* str);

/*
 * Description :
 * Function to read a received string
 */
void UART_receiveString(sint8* str);

#endif /* UART_H_ */
