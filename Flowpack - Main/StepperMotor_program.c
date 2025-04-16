/*
 * StepperMotor_program.c
 *
 *  Created on: Jan 25, 2024
 *      Author: Ahmed Osama
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "StepperMotor_config.h"
#include "StepperMotor_interface.h"

#include <util/delay.h>


void Stepper_voidInit(void)
{
	DIO_u8SetPinDirection(SL_DIR_PORT, SL_DIR_PIN, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(SL_PULSE_PORT, SL_PULSE_PIN, DIO_u8PIN_OUTPUT);

	DIO_u8SetPinDirection(SR_DIR_PORT, SR_DIR_PIN, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(SR_PULSE_PORT, SR_PULSE_PIN, DIO_u8PIN_OUTPUT);
}

void Stepper_voidAngleRotate(u8 Copy_u8Stepper, u8 Copy_u8Direction, f32 Copy_f32Angle)
{
	u16 Local_u16Counter = 0,Local_u16Iterations;

	Local_u16Iterations = (PULSE_REV * Copy_f32Angle) / 360;

	switch(Copy_u8Stepper)
	{
	case STEPPER_LEFT:
		switch(Copy_u8Direction)
		{
		case STEPPER_DIRICTION_CW:
			DIO_u8SetPinValue(SL_DIR_PORT, SL_DIR_PIN, DIO_u8PIN_HIGH);
			break;

		case STEPPER_DIRICTION_CCW:
			DIO_u8SetPinValue(SL_DIR_PORT, SL_DIR_PIN, DIO_u8PIN_LOW);
			break;

		}
		for(Local_u16Counter=0; Local_u16Counter < Local_u16Iterations; Local_u16Counter++)
		{
			DIO_u8SetPinValue(SL_PULSE_PORT, SL_PULSE_PIN, DIO_u8PIN_HIGH);
			_delay_ms(2);
			DIO_u8SetPinValue(SL_PULSE_PORT, SL_PULSE_PIN, DIO_u8PIN_LOW);
			_delay_ms(2);
		}
		break;
	case STEPPER_RIGHT:
		switch(Copy_u8Direction)
		{
		case STEPPER_DIRICTION_CW:
			DIO_u8SetPinValue(SR_DIR_PORT, SR_DIR_PIN, DIO_u8PIN_HIGH);
			break;

		case STEPPER_DIRICTION_CCW:
			DIO_u8SetPinValue(SR_DIR_PORT, SR_DIR_PIN, DIO_u8PIN_LOW);
			break;

		}
		for(Local_u16Counter=0; Local_u16Counter < Local_u16Iterations; Local_u16Counter++)
		{
			DIO_u8SetPinValue(SR_PULSE_PORT, SR_PULSE_PIN, DIO_u8PIN_HIGH);
			_delay_ms(2);
			DIO_u8SetPinValue(SR_PULSE_PORT, SR_PULSE_PIN, DIO_u8PIN_LOW);
			_delay_ms(2);
		}
		break;
	}

	/*
	 * 400 pulse/rev -> 360 degree
	 * ?             -> Copy_f32Angle
	 * no. of iterations = (400 * Copy_f32Angle) / 360
	 *
	 * */
}
