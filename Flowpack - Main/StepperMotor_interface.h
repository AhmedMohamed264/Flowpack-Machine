/*
 * StepperMotor_interface.h
 *
 *  Created on: Jan 25, 2024
 *      Author: Ahmed Osama
 */

#ifndef STEPPERMOTOR_INTERFACE_H_
#define STEPPERMOTOR_INTERFACE_H_

/*Clock wise direction*/
#define STEPPER_DIRICTION_CW	0

/*Counter clock wise direction*/
#define STEPPER_DIRICTION_CCW	1


/*Stepper motors*/
#define STEPPER_LEFT		0
#define STEPPER_RIGHT		1


void Stepper_voidInit(void);

void Stepper_voidAngleRotate(u8 Copy_u8Stepper, u8 Copy_u8Direction, f32 Copy_f32Angle);

#endif /* STEPPERMOTOR_INTERFACE_H_ */
