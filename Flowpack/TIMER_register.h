/*
 * TIMER_register.h
 *
 *  Created on: Dec 2, 2023
 *      Author: Ahmed Osama
 */

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_

#define TCCR0			*((volatile u8*)0x53)		/*TIMER0 Control Register*/
#define TCCR0_CS00		0							/*Clock select bit0*/
#define TCCR0_CS01		1							/*Clock select bit1*/
#define TCCR0_CS02		2							/*Clock select bit2*/
#define TCCR0_WGM01		3							/*Waveform Generation Mode Bit1*/
#define TCCR0_WGM00		6							/*Waveform Generation Mode Bit0*/
#define TCCR0_COM00		4							/*Compare Match Output Mode bit0*/
#define TCCR0_COM01		5							/*Compare Match Output Mode bit1*/
#define TCCR0_FOC0		7							/*Force Output Compare bit*/

#define TCNT0			*((volatile u8*)0x52)		/*TIMER0 Register*/
#define OCR0			*((volatile u8*)0x5C)		/*Output Compare Register*/

#define TIMSK			*((volatile u8*)0x59)		/*TIMER0 Interrupt Mask Register*/
#define TIMSK_TOIE0		0							/*TIMER0 Overflow Interrupt Enable*/
#define TIMSK_OCIE0		1							/*TIMER0 Output Compare Match Interrupt Enable*/
#define TIMSK_TOIE2		6
#define TIMSK_OCIE2		7

#define TIFR			*((volatile u8*)0x58)		/*TIMER0 Interrupt Flag Register*/
#define TIFR_TOV0		0							/*TIMER0 Overflow Flag*/
#define TIFR_OCF0		1							/*TIMER0 Output Compare Flag*/

//TIMER2
#define TCCR2			*((volatile u8*)0x45)		/*TIMER2 Control Register*/
#define TCCR2_CS20      0
#define TCCR2_CS21      1
#define TCCR2_CS22      2
#define TCCR2_WGM21     3
#define TCCR2_COM20     4
#define TCCR2_COM21     5
#define TCCR2_WGM20     6
#define TCCR2_FOC2      7

#define TCNT2			*((volatile u8*)0x44)		/*TIMER2  Register*/
#define OCR2			*((volatile u8*)0x43)		/*TIMER2 output Compare Register*/



#endif /* TIMER_REGISTER_H_ */
