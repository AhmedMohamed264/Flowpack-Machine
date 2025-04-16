/*
 * DC_MOTOR_program.c
 *
 *  Created on: Mar 3, 2024
 *      Author: Ahmed
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "TIMER_register.h"
#include "TIMER_interface.h"
#include "DC_MOTOR_config.h"
#include "DC_MOTOR_interface.h"


u8 Global_u8ConveyorSpeed = 0;

void MOTOR_voidInit(void)
{
	// Conveyor Motor
	//== Timer0 Init
	TIMER0_voidInit();

	// Set OC0 (PB3) pin as output
	DIO_u8SetPinDirection(CONVEYOR_PWM_PORT,CONVEYOR_PWM_PIN,DIO_u8PIN_OUTPUT);

	//Set Motor Direction Pins as Output
	DIO_u8SetPinDirection(CONVEYOR_DIR1_PORT,CONVEYOR_DIR1_PIN,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(CONVEYOR_DIR2_PORT,CONVEYOR_DIR2_PIN,DIO_u8PIN_OUTPUT);

	// Vertical Heaters Motors
	DIO_u8SetPinDirection(VH_L_M_PWM_PORT, VH_L_M_PWM_PIN, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(VH_L_M_DIR_PORT, VH_L_M_DIR_PIN, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(VH_R_M_PWM_PORT, VH_R_M_PWM_PIN, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(VH_R_M_DIR_PORT, VH_R_M_DIR_PIN, DIO_u8PIN_OUTPUT);

	// Horizontal Heaters Motors
	DIO_u8SetPinDirection(HH_M_PWM_PORT, HH_M_PWM_PIN, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(HH_M_DIR1_PORT, HH_M_DIR1_PIN, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(HH_M_DIR2_PORT, HH_M_DIR2_PIN, DIO_u8PIN_OUTPUT);
}

void MOTOR_voidSetSpeed(u8 Copy_u8Percentage)
{
	// Set PWM duty cycle (0 to 254)
	u16 Local_u16Temp = Copy_u8Percentage * 10;
	Global_u8ConveyorSpeed = (u8)(((u8)(Local_u16Temp/100) * 254)/10);
}

void MOTOR_voidRotate(u8 Copy_u8Motor, u8 Copy_u8Dir)
{
	switch(Copy_u8Motor)
	{
	case HH_MOTOR:
		switch(Copy_u8Dir)
		{
		case DIR_CW:
			// Rotating HH Motor in Clockwise Direction (Mechanism open)
			DIO_u8SetPinValue(HH_M_DIR1_PORT, HH_M_DIR1_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(HH_M_DIR2_PORT, HH_M_DIR2_PIN, DIO_u8PIN_LOW);

			// MAX SPEED RUN
			DIO_u8SetPinValue(HH_M_PWM_PORT, HH_M_PWM_PIN, DIO_u8PIN_HIGH);
			break;
		case DIR_CCW:
			// Rotating HH Motor in counter Clockwise Direction (Mechanism Close)
			DIO_u8SetPinValue(HH_M_DIR1_PORT, HH_M_DIR1_PIN, DIO_u8PIN_LOW);
			DIO_u8SetPinValue(HH_M_DIR2_PORT, HH_M_DIR2_PIN, DIO_u8PIN_HIGH);

			// MAX SPEED RUN
			DIO_u8SetPinValue(HH_M_PWM_PORT, HH_M_PWM_PIN, DIO_u8PIN_HIGH);
			break;
		}
		break;
	case VH_L_MOTOR:
		switch(Copy_u8Dir)
		{
		case DIR_CW: // opens the mechanism
			// Rotating VH Left Motor ClockWise
			DIO_u8SetPinValue(VH_L_M_DIR_PORT, VH_L_M_DIR_PIN, DIO_u8PIN_HIGH);

			// Run at max speed
			DIO_u8SetPinValue(VH_L_M_PWM_PORT, VH_L_M_PWM_PIN, DIO_u8PIN_HIGH);
			break;
		case DIR_CCW:
			// Rotating VH Left Motor ClockWise
			DIO_u8SetPinValue(VH_L_M_DIR_PORT, VH_L_M_DIR_PIN, DIO_u8PIN_LOW);

			// Run at max speed
			DIO_u8SetPinValue(VH_L_M_PWM_PORT, VH_L_M_PWM_PIN, DIO_u8PIN_HIGH);
			break;
		}
		break;
	case VH_R_MOTOR:
		switch(Copy_u8Dir)
		{
		case DIR_CW: // Opens the mechanism
			// Rotating VH right Motor ClockWise
			DIO_u8SetPinValue(VH_R_M_DIR_PORT, VH_R_M_DIR_PIN, DIO_u8PIN_HIGH);

			// Run at max speed
			DIO_u8SetPinValue(VH_R_M_PWM_PORT, VH_R_M_PWM_PIN, DIO_u8PIN_HIGH);
			break;
		case DIR_CCW:
			// Rotating VH right Motor ClockWise
			DIO_u8SetPinValue(VH_R_M_DIR_PORT, VH_R_M_DIR_PIN, DIO_u8PIN_LOW);

			// Run at max speed
			DIO_u8SetPinValue(VH_R_M_PWM_PORT, VH_R_M_PWM_PIN, DIO_u8PIN_HIGH);
			break;
		}
		break;
	case CONVEYOR_MOTOR:
		switch(Copy_u8Dir)
		{
		case DIR_CW:
			// CW Direction set for the conveyor motor
			DIO_u8SetPinValue(CONVEYOR_DIR1_PORT, CONVEYOR_DIR1_PIN , DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(CONVEYOR_DIR2_PORT, CONVEYOR_DIR2_PIN , DIO_u8PIN_LOW);

			// Rotate the conveyor motor
			OCR0 = Global_u8ConveyorSpeed;
			break;
		case DIR_CCW:
			// CCW Direction set for the conveyor motor
			DIO_u8SetPinValue(CONVEYOR_DIR1_PORT, CONVEYOR_DIR1_PIN , DIO_u8PIN_LOW);
			DIO_u8SetPinValue(CONVEYOR_DIR2_PORT, CONVEYOR_DIR2_PIN , DIO_u8PIN_HIGH);

			// Rotate the conveyor motor
			OCR0 = Global_u8ConveyorSpeed;
			break;
		}
		break;
	}
}


void MOTOR_voidStop(u8 Copy_u8Motor)
{
	switch(Copy_u8Motor)
	{
	case HH_MOTOR:
		DIO_u8SetPinValue(HH_M_PWM_PORT, HH_M_PWM_PIN, DIO_u8PIN_LOW);

		DIO_u8SetPinValue(HH_M_DIR1_PORT, HH_M_DIR1_PIN, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(HH_M_DIR2_PORT, HH_M_DIR2_PIN, DIO_u8PIN_LOW);
		break;
	case VH_L_MOTOR:
		DIO_u8SetPinValue(VH_L_M_PWM_PORT, VH_L_M_PWM_PIN, DIO_u8PIN_LOW);
		break;
	case VH_R_MOTOR:
		DIO_u8SetPinValue(VH_R_M_PWM_PORT, VH_R_M_PWM_PIN, DIO_u8PIN_LOW);
		break;
	case CONVEYOR_MOTOR:
		OCR0 = 0;

		DIO_u8SetPinValue(CONVEYOR_DIR1_PORT, CONVEYOR_DIR1_PIN, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(CONVEYOR_DIR2_PORT, CONVEYOR_DIR2_PIN, DIO_u8PIN_LOW);
		break;
	}
}



