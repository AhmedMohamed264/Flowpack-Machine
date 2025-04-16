/*
 * BUTTON_interface.h
 *
 *  Created on: Mar 3, 2024
 *      Author: Ahmed
 */

#ifndef BUTTON_INTERFACE_H_
#define BUTTON_INTERFACE_H_


#define BUTTON_UP				0
#define BUTTON_DOWN				1
#define BUTTON_ENTER			2
#define BUTTON_TOGGLE_RUN		3


#define BUTTON_PRESSED 			0
#define BUTTON_NOT_PRESSED 		1


void BUTTON_voidInit(void);
u8 BUTTON_u8GetState(u8 Copy_u8Button);
u8 BUTTON_u8Waiting(void);


#endif /* BUTTON_INTERFACE_H_ */
