/*
 * DC_MOTOR_interface.h
 *
 *  Created on: Mar 3, 2024
 *      Author: Ahmed
 */

#ifndef DC_MOTOR_INTERFACE_H_
#define DC_MOTOR_INTERFACE_H_


// Motors Definition
#define HH_MOTOR			0
#define VH_L_MOTOR			1
#define VH_R_MOTOR			2
#define CONVEYOR_MOTOR		3

// Directions
#define DIR_CW					0
#define DIR_CCW					1


void MOTOR_voidInit(void);
void MOTOR_voidSetSpeed(u8 Copy_u8Percentage);
void MOTOR_voidRotate(u8 Copy_u8Motor, u8 Copy_u8Dir);
void MOTOR_voidStop(u8 Copy_u8Motor);


#endif /* DC_MOTOR_INTERFACE_H_ */
