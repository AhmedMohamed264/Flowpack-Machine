/*
 * Proximity_Interface.h
 *
 *  Created on: Feb 14, 2024
 *      Author: Abdallah Mohammed
 */

#ifndef PROXIMITY_INTERFACE_H_
#define PROXIMITY_INTERFACE_H_

#define OBJECT_NOT_DETECTED 	1
#define OBJECT_DETECTED 		0

void Proximity_voidInit();

u8 Proximity_u8GetState();

#endif /* PROXIMITY_INTERFACE_H_ */
