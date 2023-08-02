 /******************************************************************************
 *
 * Project : Smart Lock
 *
 * File Name: MCU_1.c
 *
 * Description: Human machine interface for Smart Lock
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/

#include<avr/io.h>
#include<util/delay.h>
#include"keypad.h"
#include"lcd.h"
#include"timer1.h"
#include"uart.h"
#include"communication_macros.h"

#define ENTER '='


void getPassword(uint8*);
uint8 setPassword();
uint8 checkPassword();
void timerTick();


volatile uint8 g_time;


int main()
{
	/* a variable to store pressed key */
	uint8 key;
	/* a variable to store UART configuration */
	UART_ConfigType uartConfig;
	/* a variable to store Timer1 configuration */
	Timer1_ConfigType timerConfig;

	/* UART configuration and initialization */
	uartConfig.baudRate = 9600;
	uartConfig.character_size = EIGHT_BITS;
	uartConfig.parity = DISABLED;
	uartConfig.stop_bits = ONE_BIT;
	UART_init(&uartConfig);

	/* Timer1 configuration without initialization
	 * configured to give interrupt every 7.5 seconds */
	timerConfig.initial_value = 0;
	timerConfig.mode = COMPARE;
	timerConfig.compare_value = 58593;
	timerConfig.prescaler = CLK_1024;
	Timer1_setCallBack(timerTick);

	/* initialize LCD */
	LCD_init();
	/* enable global interrupt */
	SREG|=(1<<7);

	/* set password for first time
	 * continue asking for password if the confirmation doesn't match the password */
	while(setPassword() == UNMATCHED_PASSWORDS);

	for(;;)
	{
		LCD_clearScreen();
		LCD_displayString("+ : Open Door");
		LCD_displayStringRowColumn(1, 0, "- : Change Pass");
		do
		{
			key = KEYPAD_getPressedKey();
		}while(key != '+' && key != '-');

		/* ask the user for the password and check if it's correct
		 * we need to check password to do either operation  */
		if(checkPassword() == MATCHED_PASSWORDS)
		{
			switch(key)
			{
			case '+':
				/* send command open door to MCU2 */
				UART_sendByte(OPEN_DOOR);
				/* display the state of the lock
				 * MCU2 sends a dummy byte every time the state changes */
				UART_receiveByte();
				LCD_clearScreen();
				LCD_displayString("    Door is");
				LCD_displayStringRowColumn(1, 3, "Unlocking");

				UART_receiveByte();
				LCD_clearScreen();
				LCD_displayString("    Door is");
				LCD_displayStringRowColumn(1, 6, "Open");


				UART_receiveByte();
				LCD_clearScreen();
				LCD_displayString("    Door is");
				LCD_displayStringRowColumn(1, 4, "Locking");

				UART_receiveByte();
				break;
			case '-':
				/* change password
				 * continue asking for password if the confirmation doesn't
				 *  match the password */
				while(setPassword() == UNMATCHED_PASSWORDS);
				break;
			}
		}
		else
		{
			/* if user enter password wrong 3 times release the alarm and stop
			 * the system for a minute */
			/* turn MCU2 buzzer on */
			UART_sendByte(BUZZER_ON);
			/* display error message */
			LCD_clearScreen();
			LCD_displayString("WRONG PASSWORD!");
			LCD_displayStringRowColumn(1, 1, "System Locked");
			/* set time t0 60 seconds (8 * 7.5 = 60) */
			g_time = 8;
			/* initialize timer1 */
			Timer1_init(&timerConfig);
			/* wait until the minute is over */
			while(g_time > 0);
			/* de_initialize timer1 */
			Timer1_deInit();
			/* turn MCU2 buzzer off */
			UART_sendByte(BUZZER_OFF);
		}
	}
}


/*
 * Description :
 * a function that acts as the ISR of timer1
 * increase the time every interrupt
 */
void timerTick()
{
	g_time--;
}


/*
 * Description :
 * a function to take 5 digits input from keypad (password)
 */
void getPassword(uint8* ptr)
{
	/* a variable to store pressed key */
	uint8 key;
	/* loop variable */
	uint8 i;
	/* get 5 digits password through keypad */
	for(i=0; i<5; i++)
	{
		do
		{
			key = KEYPAD_getPressedKey();
		}while(key < 0 || key >9);/* only take numbers as input */

		ptr[i] = key;
		LCD_displayCharacter('*');
		_delay_ms(400);
	}
	/* wait for user to press enter */
	while(KEYPAD_getPressedKey() != ENTER);
	_delay_ms(400);
}

/*
 * Description :
 * a function to set the password of lock
 */
uint8 setPassword()
{
	/* a variable to store the password */
	uint8 pass[5];
	/* a variable to store the re_entered password */
	uint8 passConfirm[5];
	/* ask the user for password */
	LCD_clearScreen();
	LCD_displayString("plz enter pass: ");
	LCD_moveCursor(1, 0);
	/* get 5 digits password through keypad */
	getPassword(pass);
	/* clear screen and ask the user to re_enter password */
	LCD_clearScreen();
	LCD_displayString("plz re_enter the");
	LCD_displayStringRowColumn(1, 0, "same pass: ");
	/* get 5 digits password through keypad */
	getPassword(passConfirm);

	/* send a predefined character that indicates to the second MCU
	 * the operation is setting a new password */
	UART_sendByte(SET_PASSWORD);
	/* send the two passwords */
	for(int i=0; i<5; i++)
	{
		UART_sendByte(pass[i]);
		UART_receiveByte();
	}
	for(int i=0; i<5; i++)
	{
		UART_sendByte(passConfirm[i]);\
		UART_receiveByte();
	}

	/* return MCU2 response whether the two passwords match or not */
	return UART_receiveByte();
}

/*
 * Description :
 * a function to take the password and check if it is the same as the
 * password stored in the EEPROM connected to MCU2
 */
uint8 checkPassword()
{
	/* loop variable */
	uint8 i;
	/* a variable to store the password */
	uint8 pass[6];
	/* ask the user for password */
	for(i=0; i<3; i++)
	{
		LCD_clearScreen();
		LCD_displayString("plz enter pass: ");
		LCD_moveCursor(1, 0);

		UART_sendByte(COMPARE_PASSWORD);
		/* get 5 digits password through keypad */
		getPassword(pass);
		/* send password to MCU2 */
		for(int i=0; i<5; i++)
		{
			UART_sendByte(pass[i]);
			UART_receiveByte();
		}
		/* return MCU2 response  whether the two passwords match or not */
		if(UART_receiveByte() == MATCHED_PASSWORDS)
		{
			return MATCHED_PASSWORDS;
		}
	}

	return UNMATCHED_PASSWORDS;
}

