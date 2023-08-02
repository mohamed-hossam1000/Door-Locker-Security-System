/*
 * communication_macros.h
 *
 *  Created on: Jun 29, 2023
 *      Author: SIGMA
 */

#ifndef COMMUNICATION_MACROS_H_
#define COMMUNICATION_MACROS_H_

#define OPEN_DOOR 			5  /*  command to open door */
#define SET_PASSWORD 		10 /* command to set password  */
#define COMPARE_PASSWORD	15 /* command to compare password to the one stored in EEPROM  */
#define BUZZER_ON 			25 /* command to turn the buzzer on */
#define BUZZER_OFF 			30 /* command to turn the buzzer off */
#define UNMATCHED_PASSWORDS 35 /* the two passwords don't match status */
#define MATCHED_PASSWORDS 	40 /* the two passwords match status */
#define DUMMY_BYTE 			45

#endif /* COMMUNICATION_MACROS_H_ */
