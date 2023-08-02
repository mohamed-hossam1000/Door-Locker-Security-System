 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source file for the KEYPAD driver
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/
#include<util/delay.h>
#include"keypad.h"
#include"gpio.h"

#if (!KEYPAD_BASIC)
/*
 * Description :
 * takes the number of the key pressed and returns the intended input
 */
static uint8 decipherKey(uint8 key_num)
{
#if (KEYPAD_NUM_OF_COLS == 3)
	switch (key_num)
	{
	case 10:
		return '*';
		break;
	case 11:
		return 0;
		break;
	case 12:
		return  '#';
		break;
	default:
		return key_num;
	}
#elif (KEYPAD_NUM_OF_COLS == 4)
	#if (!KEYPAD_PROTEUS)
		switch (key_num)
		{
		case 4:
			return 'A';
			break;
		case 5:
			return 4;
			break;
		case 6:
			return 5;
			break;
		case 7:
			return 6;
			break;
		case 8:
			return 'B';
			break;
		case 9:
			return 7;
			break;
		case 10:
			return 8;
			break;
		case 11:
			return 9;
			break;
		case 12:
			return 'C';
			break;
		case 13:
			return '*';
			break;
		case 14:
			return 0;
			break;
		case 15:
			return '#';
			break;
		case 16:
			return 'D';
			break;
		default:
			return key_num;
		}
	#else
		switch (key_num)
		{
		case 1:
			return 7;
			break;
		case 2:
			return 8;
			break;
		case 3:
			return 9;
			break;
		case 4:
			return '%';
			break;
		case 5:
			return 4;
			break;
		case 6:
			return 5;
			break;
		case 7:
			return 6;
			break;
		case 8:
			return '*';
			break;
		case 9:
			return 1;
			break;
		case 10:
			return 2;
			break;
		case 11:
			return 3;
			break;
		case 12:
			return  '-';
			break;
		case 13:
			return '!';
			break;
		case 14:
			return 0;
			break;
		case 15:
			return '=';
			break;
		case 16:
			return '+';
			break;
		default:
			return 0;
		}

	#endif
#endif
}
#endif

/*
 * Description :
 * get the pressed key number and return its value
 */
uint8 KEYPAD_getPressedKey(void)
{
	uint8 row,col;/* counters for the loops */
	/* setup all the pins as input */
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_PIN_ID, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_PIN_ID+1, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_PIN_ID+2, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_PIN_ID+3, PIN_INPUT);

	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_COL_PIN_ID, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_COL_PIN_ID+1, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_COL_PIN_ID+2, PIN_INPUT);
#if(KEYPAD_NUM_OF_COLS == 4)
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_COL_PIN_ID+3, PIN_INPUT);
#endif

	/* loop through all the keys until we find a pressed key */
	for(;;)
	{
		for(row=0; row<KEYPAD_NUM_OF_ROWS; row++)
		{
			/* set one row as output and enable it */
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_PIN_ID + row, PIN_OUTPUT);
			GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_PIN_ID + row, KEYPAD_KEY_PRESSED);
			/* loop through all the key in the enabled row */
			for(col=0; col<KEYPAD_NUM_OF_COLS; col++)
			{
				if(GPIO_readPin(KEYPAD_COL_PORT_ID, KEYPAD_COL_PIN_ID + col) == KEYPAD_KEY_PRESSED)
				{
					/* after finding a pressed key return the input intended by it */
					#if (KEYPAD_BASIC)
						return (row * KEYPAD_NUM_OF_COLS + col + 1);
					#else
						return decipherKey(row * KEYPAD_NUM_OF_COLS + col + 1);
					#endif
				}
			}
			/* set the same row as input to disable it */
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_PIN_ID + row, PIN_INPUT);
			_delay_ms(10);
		}
	}
	return 0;
}
