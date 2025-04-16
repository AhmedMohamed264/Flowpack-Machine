/*
 * Proximity_Program.c
 *
 *  Created on: Feb 14, 2024
 *      Author: Abdallah Mohammed
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "Proximity_Interface.h"
#include "Proximity_Config.h"


void Proximity_voidInit()
{
	//INITILZATION INPUT-PULLUP
	DIO_u8SetPinDirection(PROXIMITY_PORT , PROXIMITY_PIN , DIO_u8PIN_INPUT);
	DIO_u8SetPinValue(PROXIMITY_PORT , PROXIMITY_PIN ,DIO_u8PIN_HIGH);

}
u8 Proximity_u8GetState()
{
	u8 Local_Get_State;

	DIO_u8GetPinValue(PROXIMITY_PORT,PROXIMITY_PIN,&Local_Get_State);

	if(Local_Get_State==OBJECT_DETECTED)
	{
		return OBJECT_DETECTED;
	}
	return OBJECT_NOT_DETECTED;
}
