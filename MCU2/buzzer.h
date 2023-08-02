 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: Buzzer.h
 *
 * Description: Header file for the Buzzer driver
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

/*******************************************************************************
 *                                Configuration
 *******************************************************************************/
#define BUZZER_PORT_ID PORTD_ID
#define BUZZER_PIN_ID  PIN3_ID

/*******************************************************************************
 *                                Functions Prototypes
 *******************************************************************************/

void Buzzer_init();

void Buzzer_on();

void Buzzer_off();

#endif /* BUZZER_H_ */
