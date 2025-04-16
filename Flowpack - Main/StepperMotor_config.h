/*
 * StepperMotor_config.h
 *
 *  Created on: Jan 25, 2024
 *      Author: Ahmed Osama
 */

#ifndef STEPPERMOTOR_CONFIG_H_
#define STEPPERMOTOR_CONFIG_H_

// We are looking to the machine from back perspective

#define	PULSE_REV	400

#define SL_PULSE_PORT	DIO_u8PORTC
#define SL_PULSE_PIN	DIO_u8PIN0
#define	SL_DIR_PORT		DIO_u8PORTC
#define	SL_DIR_PIN		DIO_u8PIN1

#define SR_PULSE_PORT	DIO_u8PORTC
#define SR_PULSE_PIN	DIO_u8PIN2
#define	SR_DIR_PORT		DIO_u8PORTC
#define	SR_DIR_PIN		DIO_u8PIN3

#endif /* STEPPERMOTOR_CONFIG_H_ */
