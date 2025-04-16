/*
 * DC_MOTOR_config.h
 *
 *  Created on: Mar 3, 2024
 *      Author: Ahmed
 */

#ifndef DC_MOTOR_CONFIG_H_
#define DC_MOTOR_CONFIG_H_

// We are looking to the machine from back perspective

// Cytron motor driver
// Vertical Heaters Motors
#define VH_L_M_DIR_PORT				DIO_u8PORTA
#define VH_L_M_DIR_PIN				DIO_u8PIN0
#define VH_L_M_PWM_PORT				DIO_u8PORTA
#define VH_L_M_PWM_PIN				DIO_u8PIN1

#define VH_R_M_DIR_PORT				DIO_u8PORTA
#define VH_R_M_DIR_PIN				DIO_u8PIN2
#define VH_R_M_PWM_PORT				DIO_u8PORTA
#define VH_R_M_PWM_PIN				DIO_u8PIN3


// l298n (7A) motor driver
// Horizontal Heater Motor
#define HH_M_PWM_PORT				DIO_u8PORTA // ENA
#define HH_M_PWM_PIN				DIO_u8PIN4
#define HH_M_DIR1_PORT				DIO_u8PORTA //IN1
#define HH_M_DIR1_PIN				DIO_u8PIN5
#define HH_M_DIR2_PORT				DIO_u8PORTA //IN2
#define HH_M_DIR2_PIN				DIO_u8PIN6

// Conveyor motor
#define CONVEYOR_PWM_PORT     		DIO_u8PORTB
#define CONVEYOR_PWM_PIN     		DIO_u8PIN3
#define CONVEYOR_DIR1_PORT     		DIO_u8PORTB
#define CONVEYOR_DIR1_PIN     		DIO_u8PIN1
#define CONVEYOR_DIR2_PORT     		DIO_u8PORTB
#define CONVEYOR_DIR2_PIN     		DIO_u8PIN2


#endif /* DC_MOTOR_CONFIG_H_ */
