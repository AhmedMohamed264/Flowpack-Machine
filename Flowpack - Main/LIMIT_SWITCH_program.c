/*
 * LIMIT_SWITCH_program.c
 *
 *  Created on: Mar 3, 2024
 *      Author: Ahmed
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "LIMIT_SWITCH_config.h"
#include "LIMIT_SWITCH_private.h"
#include "LIMIT_SWITCH_interface.h"
#include <util/delay.h>


void LIMIT_SW_voidInit(void)
{
	//set the direction of limit switch pins as input activate internal pull up resistor
	DIO_u8SetPinDirection(HH_LIMIT_SW_PORT, HH_LIMIT_SW_PIN, DIO_u8PIN_INPUT);
	DIO_u8SetPinValue(HH_LIMIT_SW_PORT, HH_LIMIT_SW_PIN, DIO_u8PIN_HIGH);

	// LIMIT SWITCHES INTERNAL PULL UP RESISTOR INITIALIZE
	DIO_u8SetPinDirection(VH_L_LIMIT_SW_PORT, VH_L_LIMIT_SW_PIN, DIO_u8PIN_INPUT);
	DIO_u8SetPinDirection(VH_R_LIMIT_SW_PORT, VH_R_LIMIT_SW_PIN, DIO_u8PIN_INPUT);

	DIO_u8SetPinValue(VH_L_LIMIT_SW_PORT, VH_L_LIMIT_SW_PIN, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(VH_R_LIMIT_SW_PORT, VH_R_LIMIT_SW_PIN, DIO_u8PIN_HIGH);
}


u8 LIMIT_SW_u8GetState(u8 Copy_u8LimitSW)
{
	u8 Local_u8PinValue = LIMIT_SW_NOT_REACHED;

	switch(Copy_u8LimitSW)
	{
	case HH_LIMIT_SW:
		DIO_u8GetPinValue(HH_LIMIT_SW_PORT, HH_LIMIT_SW_PIN, &Local_u8PinValue);
		break;
	case VH_L_LIMIT_SW:
		DIO_u8GetPinValue(VH_L_LIMIT_SW_PORT, VH_L_LIMIT_SW_PIN, &Local_u8PinValue);
		break;
	case VH_R_LIMIT_SW:
		DIO_u8GetPinValue(VH_R_LIMIT_SW_PORT, VH_R_LIMIT_SW_PIN, &Local_u8PinValue);
		break;
	}
	return Local_u8PinValue;
}

u8 LIMIT_SW_voidWaiting(u8 Copy_u8LimitSW)
{
	u8 Local_u8LimitSWState = LIMIT_SW_NOT_REACHED;
	u32 Local_u32Counter = 0;
	do
	{
		Local_u8LimitSWState = LIMIT_SW_u8GetState(Copy_u8LimitSW);
		Local_u32Counter++;
		if(Local_u32Counter >= LIMIT_SW_TIMEOUT)
			return ERROR_LIMIT_SW_TIMEOUT;
		_delay_ms(50);
	}
	while(Local_u8LimitSWState == LIMIT_SW_NOT_REACHED); //WHILE LIMIT SWITCH NOT REACHED
	return LIMIT_SW_REACHED;
}

