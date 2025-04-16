/*
 * BUTTON_program.c
 *
 *  Created on: Mar 3, 2024
 *      Author: Ahmed
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "BUTTON_config.h"
#include "BUTTON_private.h"
#include "BUTTON_interface.h"
#include <util/delay.h>


void BUTTON_voidInit(void)
{
	// ALL BUTTONS INPUT
	DIO_u8SetPinDirection(BUTTON_UP_PORT, BUTTON_UP_PIN, DIO_u8PIN_INPUT);
	DIO_u8SetPinDirection(BUTTON_DOWN_PORT, BUTTON_DOWN_PIN, DIO_u8PIN_INPUT);
	DIO_u8SetPinDirection(BUTTON_ENTER_PORT, BUTTON_ENTER_PIN, DIO_u8PIN_INPUT);
	DIO_u8SetPinDirection(BUTTON_TOGGLE_RUN_PORT, BUTTON_TOGGLE_RUN_PIN, DIO_u8PIN_INPUT);

	// ALL BUTTONS PULL UP ENABLE
	DIO_u8SetPinValue(BUTTON_UP_PORT, BUTTON_UP_PIN, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(BUTTON_DOWN_PORT, BUTTON_DOWN_PIN, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(BUTTON_ENTER_PORT, BUTTON_ENTER_PIN, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(BUTTON_TOGGLE_RUN_PORT, BUTTON_TOGGLE_RUN_PIN, DIO_u8PIN_HIGH);
}

u8 BUTTON_u8GetState(u8 Copy_u8Button)
{
	u8 Local_u8PinValue;

	switch(Copy_u8Button)
	{
	case BUTTON_UP:
		DIO_u8GetPinValue(BUTTON_UP_PORT, BUTTON_UP_PIN, &Local_u8PinValue);
		break;
	case BUTTON_DOWN:
		DIO_u8GetPinValue(BUTTON_DOWN_PORT, BUTTON_DOWN_PIN, &Local_u8PinValue);
		break;
	case BUTTON_ENTER:
		DIO_u8GetPinValue(BUTTON_ENTER_PORT, BUTTON_ENTER_PIN, &Local_u8PinValue);
		break;
	case BUTTON_TOGGLE_RUN:
		DIO_u8GetPinValue(BUTTON_TOGGLE_RUN_PORT, BUTTON_TOGGLE_RUN_PIN, &Local_u8PinValue);
		break;
	}

	return Local_u8PinValue;
}



