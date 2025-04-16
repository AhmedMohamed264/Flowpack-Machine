/*
 * LIMIT_SWITCH_interface.h
 *
 *  Created on: Mar 3, 2024
 *      Author: Ahmed
 */

#ifndef LIMIT_SWITCH_INTERFACE_H_
#define LIMIT_SWITCH_INTERFACE_H_


#define HH_LIMIT_SW		0
#define VH_L_LIMIT_SW	1
#define VH_R_LIMIT_SW	2


#define LIMIT_SW_REACHED 		0
#define LIMIT_SW_NOT_REACHED 	1

#define ERROR_LIMIT_SW_TIMEOUT	2  // Mechanical/Electrical Error


void LIMIT_SW_voidInit(void);
u8 LIMIT_SW_u8GetState(u8 Copy_u8LimitSW);
u8 LIMIT_SW_voidWaiting(u8 Copy_u8LimitSW);


#endif /* LIMIT_SWITCH_INTERFACE_H_ */
