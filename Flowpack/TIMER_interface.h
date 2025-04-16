/*
 * TIMER_interface.h
 *
 *  Created on: Dec 2, 2023
 *      Author: Ahmed Osama
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#define TIMER0_Normal_Mode				1
#define TIMER0_PWM_Mode					2
#define TIMER0_CTC_Mode					3
#define TIMER0_FastPWM_Mode				4

#define TIMER_Prescaler_8				5
#define TIMER_Prescaler_64				6
#define TIMER_Prescaler_256				7
#define TIMER_Prescaler_1024			8
#define TIMER_NO_Prescaler				9
#define TIMER_NO_ClockSource			10

#define TIMER2_Normal_Mode				1
#define TIMER2_PWM_Mode					2
#define TIMER2_CTC_Mode					3
#define TIMER2_FastPWM_Mode				4

void TIMER0_voidInit(void);

void TIMER2_voidInit(void);

u8 TIMER0_u8SetCallBack(void(*Copy_pvCallBackFunc)(void));

u8 TIMER2_u8SetCallBack(void(*Copy_pvCallBackFunc)(void));


#endif /* TIMER_INTERFACE_H_ */
