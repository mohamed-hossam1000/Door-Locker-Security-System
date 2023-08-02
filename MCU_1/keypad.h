 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the KEYPAD driver
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_
#include"std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define KEYPAD_PROTEUS 		  TRUE
#define KEYPAD_BASIC		  FALSE

#define KEYPAD_NUM_OF_COLS	  4
#define KEYPAD_NUM_OF_ROWS	  4

#define KEYPAD_COL_PORT_ID	  PORTA_ID
#define KEYPAD_COL_PIN_ID 	  PIN0_ID

#define KEYPAD_ROW_PORT_ID 	  PORTA_ID
#define KEYPAD_ROW_PIN_ID     PIN4_ID

#define KEYPAD_KEY_PRESSED    LOGIC_LOW
#define KEYPAD_KEY_RELEASEED  LOGIC_HIGH

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * get the pressed key number and return its value
 */
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
