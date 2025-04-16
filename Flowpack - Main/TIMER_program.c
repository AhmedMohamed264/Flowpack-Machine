/*
 * TIMER_program.c
 *
 *  Created on: Dec 2, 2023
 *      Author: Ahmed Osama
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "TIMER_interface.h"
#include "TIMER_config.h"
#include "TIMER_register.h"

static void (*TIMER0_pvCallBackFunc)(void) = NULL;
static void (*TIMER2_pvCallBackFunc)(void) = NULL;

void TIMER0_voidInit(void)
{
	/* Waveform Generation Mode Selection*/
#if(TIMER0_Waveform_Generation_Mode == TIMER0_Normal_Mode)
	CLR_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);
	SET_BIT(TIMSK,TIMSK_TOIE0);		/*Overflow interrupt enable*/
#elif(TIMER0_Waveform_Generation_Mode == TIMER0_PWM_Mode)
	SET_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);
#elif(TIMER0_Waveform_Generation_Mode == TIMER0_CTC_Mode)
	CLR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
	SET_BIT(TIMSK,TIMSK_OCIE0);		/*Compare Match interrupt enable*/
#elif(TIMER0_Waveform_Generation_Mode == TIMER0_FastPWM_Mode)
	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
	//Clear OC0 on compare match, set OC0 at BOTTOM,(non-inverting mode)
	CLR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);
#endif

	/*Prescaler selection*/
#if(TIMER0_Prescaler_Select == TIMER_NO_ClockSource)
	CLR_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
#elif(TIMER0_Prescaler_Select == TIMER_NO_Prescaler)
	SET_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
#elif(TIMER0_Prescaler_Select == TIMER_Prescaler_8)
	CLR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
#elif(TIMER0_Prescaler_Select == TIMER_Prescaler_64)
	SET_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
#elif(TIMER0_Prescaler_Select == TIMER_Prescaler_256)
	CLR_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS02);
#elif(TIMER0_Prescaler_Select == TIMER_Prescaler_1024)
	SET_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS02);
#endif

	 // Set TOP value (for 8-bit PWM)
	OCR0 = 0;  // Initialize with 0% duty cycle
}

void TIMER2_voidInit(void)
{
	/* Waveform Generation Mode Selection*/
	#if(TIMER2_Waveform_Generation_Mode == TIMER2_Normal_Mode)
		CLR_BIT(TCCR2,TCCR2_WGM20);
		CLR_BIT(TCCR2,TCCR2_WGM21);
		SET_BIT(TIMSK,TIMSK_TOIE2);		/*Overflow interrupt enable*/
	#elif(TIMER2_Waveform_Generation_Mode == TIMER2_PWM_Mode)
		SET_BIT(TCCR2,TCCR2_WGM20);
		CLR_BIT(TCCR2,TCCR2_WGM21);
	#elif(TIMER2_Waveform_Generation_Mode == TIMER2_CTC_Mode)
		CLR_BIT(TCCR2,TCCR2_WGM20);
		SET_BIT(TCCR2,TCCR2_WGM21);
		SET_BIT(TIMSK,TIMSK_OCIE2);		/*Compare Match interrupt enable*/
	#elif(TIMER2_Waveform_Generation_Mode == TIMER2_FastPWM_Mode)
		SET_BIT(TCCR2,TCCR2_WGM20);
		SET_BIT(TCCR2,TCCR2_WGM21);
		//Clear OC2 on compare match, set OC2 at BOTTOM,(non-inverting mode)
		CLR_BIT(TCCR2,TCCR2_COM20);
		SET_BIT(TCCR2,TCCR2_COM21);
	#endif


		/*Prescaler selection*/
	#if(TIMER2_Prescaler_Select == TIMER_NO_ClockSource)
		CLR_BIT(TCCR2,TCCR2_CS20);
		CLR_BIT(TCCR2,TCCR2_CS21);
		CLR_BIT(TCCR2,TCCR2_CS22);
	#elif(TIMER2_Prescaler_Select == TIMER_NO_Prescaler)
		SET_BIT(TCCR2,TCCR2_CS20);
		CLR_BIT(TCCR2,TCCR2_CS21);
		CLR_BIT(TCCR2,TCCR2_CS22);
	#elif(TIMER2_Prescaler_Select == TIMER_Prescaler_8)
		CLR_BIT(TCCR2,TCCR2_CS20);
		SET_BIT(TCCR2,TCCR2_CS21);
		CLR_BIT(TCCR2,TCCR2_CS22);
	#elif(TIMER2_Prescaler_Select == TIMER_Prescaler_64)
		CLR_BIT(TCCR2,TCCR2_CS20);
		CLR_BIT(TCCR2,TCCR2_CS21);
		SET_BIT(TCCR2,TCCR2_CS22);
	#elif(TIMER2_Prescaler_Select == TIMER_Prescaler_256)
		CLR_BIT(TCCR2,TCCR2_CS20);
		SET_BIT(TCCR2,TCCR2_CS21);
		SET_BIT(TCCR2,TCCR2_CS22);
	#elif(TIMER2_Prescaler_Select == TIMER_Prescaler_1024)
		SET_BIT(TCCR2,TCCR2_CS20);
		SET_BIT(TCCR2,TCCR2_CS21);
		SET_BIT(TCCR2,TCCR2_CS22);
	#endif

		 // Set TOP value (for 8-bit PWM)
		OCR2 = 0;  // Initialize with 0% duty cycle
}





u8 TIMER0_u8SetCallBack(void(*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorStatus = OK;

	if(Copy_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc = Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorStatus = NULL_POINTER;
	}
	return Local_u8ErrorStatus;
}

u8 TIMER2_u8SetCallBack(void(*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorStatus = OK;

	if(Copy_pvCallBackFunc != NULL)
	{
		TIMER2_pvCallBackFunc = Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorStatus = NULL_POINTER;
	}
	return Local_u8ErrorStatus;
}

void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if(TIMER0_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc();
	}
}

void __vector_5 (void) __attribute__((signal));
void __vector_5 (void)
{
	if(TIMER2_pvCallBackFunc != NULL)
	{
		TIMER2_pvCallBackFunc();
	}
}

