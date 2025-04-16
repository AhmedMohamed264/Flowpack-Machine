/*
 * LIMIT_SWITCH_config.h
 *
 *  Created on: Mar 3, 2024
 *      Author: Ahmed
 */

#ifndef LIMIT_SWITCH_CONFIG_H_
#define LIMIT_SWITCH_CONFIG_H_

// We are looking to the machine from back perspective

#define HH_LIMIT_SW_PORT		DIO_u8PORTC   // blue(SW) ---> white (atmega)
#define HH_LIMIT_SW_PIN			DIO_u8PIN4

#define VH_L_LIMIT_SW_PORT		DIO_u8PORTC   // Orange(SW)  --> green (atmega)
#define VH_L_LIMIT_SW_PIN		DIO_u8PIN5

#define VH_R_LIMIT_SW_PORT		DIO_u8PORTC   // Brown(SW) --> Brown (atmega)
#define VH_R_LIMIT_SW_PIN		DIO_u8PIN6


#endif /* LIMIT_SWITCH_CONFIG_H_ */
