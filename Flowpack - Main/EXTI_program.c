/*****************************************************************/
/*****************************************************************/
/*************     Author: Abdallah Mohammed     *****************/
/*************     layer: MCAL                   *****************/
/*************     SWC: interrupt                *****************/
/*************     Version : 1.00                *****************/
/*************     Date :16/8/2023               *****************/
/*****************************************************************/
/*****************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include"EXTI_interface.h"
#include"EXTI_config.h"
#include"EXTI_private.h"
#include"EXTI_register.h"

void (*EXTI_pvInt0Func)(void)=NULL;
void (*EXTI_pvInt1Func)(void)=NULL;
void (*EXTI_pvInt2Func)(void)=NULL;
void EXTI_VoidInt0_Init(void)
{
	/*check sense control*/
#if INT0_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	 CLR_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE == FALLING_EDGE
	 CLR_BIT(MCUCR,MCUCR_ISC00);
	 SET_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE == RISING_EDGE
	 SET_BIT(MCUCR,MCUCR_ISC00);
	 SET_BIT(MCUCR,MCUCR_ISC01);

#else
#error"Wrong INT0_SENSE Configuration option"

#endif
	/*Check peripheral interrupt enable initial state for INT0*/
#if INT0_INITAL_STATE == ENABLED
	 SET_BIT(GICR,GICR_INT0);

#elif INT0_INITAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT0);

#else
#error"Wrong INT0_INITAL_STATE Configuration option "
#endif
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void EXTI_VoidInt1_Init(void)
{
	/*check sense control*/
#if INT1_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_SENSE == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#else
#error"Wrong INT1_SENSE Configuration option"

#endif
	/*Check peripheral interrupt enable initial state for INT1*/
#if INT1_INITAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT1);

#elif INT1_INITAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT1);

#else
#error"Wrong INT1_INITAL_STATE Configuration option "
#endif
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
void EXTI_VoidInt2_Init(void)
{
	/*check sense control*/
#if INT2_SENSE == FALLING_EDGE
	CLR_BIT(MCUCSR,MCUCSR_ISC2);

#elif INT2_SENSE == RISING_EDGE
	SET_BIT(MCUCSR,MCUCSR_ISC2);
#else
#error"Wrong INT2_SENSE Configuration option"

#endif
	/*Check peripheral interrupt enable initial state for INT2*/
#if INT2_INITAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT2);

#elif INT2_INITAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT2);

#else
#error"Wrong INT2_INITAL_STATE Configuration option "
#endif
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
u8 EXTI_u8Int0SetSenseControl(u8 Copy_u8Sense)
{
	u8 Local_u8ErrorState=OK;
	switch(Copy_u8Sense)
	{
	case LOW_LEVEL: CLR_BIT(MCUCR,MCUCR_ISC00);   CLR_BIT(MCUCR,MCUCR_ISC01);break;
	case ON_CHANGE: SET_BIT(MCUCR,MCUCR_ISC00);     CLR_BIT(MCUCR,MCUCR_ISC01);break;
	case FALLING_EDGE:CLR_BIT(MCUCR,MCUCR_ISC00); SET_BIT(MCUCR,MCUCR_ISC01);  break;
	case RISING_EDGE:SET_BIT(MCUCR,MCUCR_ISC00);    SET_BIT(MCUCR,MCUCR_ISC01);  break;
	default:Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
u8 EXTI_u8Int1SetSenseControl(u8 Copy_u8Sense)
{
	u8 Local_u8ErrorState=OK;
	switch(Copy_u8Sense)
	{
	case LOW_LEVEL: CLR_BIT(MCUCR,MCUCR_ISC10);   CLR_BIT(MCUCR,MCUCR_ISC11);break;
	case ON_CHANGE: SET_BIT(MCUCR,MCUCR_ISC10);     CLR_BIT(MCUCR,MCUCR_ISC11);break;
	case FALLING_EDGE:CLR_BIT(MCUCR,MCUCR_ISC10); SET_BIT(MCUCR,MCUCR_ISC11);  break;
	case RISING_EDGE:SET_BIT(MCUCR,MCUCR_ISC10);    SET_BIT(MCUCR,MCUCR_ISC11);  break;
	default:Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
u8 EXTI_u8Int2SetSenseControl(u8 Copy_u8Sense)
{
	u8 Local_u8ErrorState=OK;
	switch(Copy_u8Sense)
	{
	case FALLING_EDGE:CLR_BIT(MCUCSR,MCUCSR_ISC2);  break;
	case RISING_EDGE:SET_BIT(MCUCSR,MCUCSR_ISC2);     break;
	default:Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////
u8 EXTI_u8IntEnable(u8 Copy_u8INT)
{
	u8 Local_u8ErrorState=OK;

	if(Copy_u8INT == GICR_INT0)
	{
		SET_BIT(GICR,GICR_INT0);
	}
	else if(Copy_u8INT == GICR_INT1)
	{
		SET_BIT(GICR,GICR_INT1);
	}
	else if(Copy_u8INT == GICR_INT2)
	{
		SET_BIT(GICR,GICR_INT2);
	}
	return Local_u8ErrorState;
}
////////////////////////////////////////////////////
u8 EXTI_u8IntDisable(u8 Copy_u8INT)
{
	u8 Local_u8ErrorState=OK;
	if(Copy_u8INT == GICR_INT0)
	{
		CLR_BIT(GICR,GICR_INT0);
	}
	else if(Copy_u8INT == GICR_INT1)
	{
		CLR_BIT(GICR,GICR_INT1);
	}
	else if(Copy_u8INT == GICR_INT2)
	{
		CLR_BIT(GICR,GICR_INT2);
	}
	return Local_u8ErrorState;
}
////////////////////////////////////////////////////////////////
u8 EXTI_u8INT0SetCallBack(void (*Copy_pvInt0Func)(void))
{
	u8 Local_u8ErrorStatus=OK;
	if(Copy_pvInt0Func!= NULL)
	{
		EXTI_pvInt0Func = Copy_pvInt0Func;

	}
	else
	{
		Local_u8ErrorStatus=NULL_POINTER;
	}


	return Local_u8ErrorStatus;
}
/*ISR FOR INT0*/
void __vector_1(void) __attribute__((signal));

void __vector_1(void)
{
	if(EXTI_pvInt0Func!= NULL)
	{
		EXTI_pvInt0Func();
	}
	else
	{
		/* Do nothing*/
	}


}
/////////////////////////////////////////////////////////////////////////////
u8 EXTI_u8INT1SetCallBack(void (*Copy_pvInt1Func)(void))
{
	u8 Local_u8ErrorStatus=OK;
		if(Copy_pvInt1Func!= NULL)
		{
			EXTI_pvInt0Func = Copy_pvInt1Func;

		}
		else
		{
			Local_u8ErrorStatus=NULL_POINTER;
		}


		return Local_u8ErrorStatus;
}
/*ISR FOR INT1*/
void __vector_2(void) __attribute__((signal));

void __vector_2(void)
{
	if(EXTI_pvInt1Func!= NULL)
	{
		EXTI_pvInt1Func();
	}
	else
	{
		/* Do nothing*/
	}


}
////////////////////////////////////////////////////////
u8 EXTI_u8INT2SetCallBack(void (*Copy_pvInt2Func)(void))
{
	u8 Local_u8ErrorStatus=OK;
		if(Copy_pvInt2Func!= NULL)
		{
			EXTI_pvInt2Func = Copy_pvInt2Func;

		}
		else
		{
			Local_u8ErrorStatus=NULL_POINTER;
		}


		return Local_u8ErrorStatus;
}
/*ISR FOR INT2*/
void __vector_3(void) __attribute__((signal));

void __vector_3(void)
{
	if(EXTI_pvInt2Func!= NULL)
	{
		EXTI_pvInt2Func();
	}
	else
	{
		/* Do nothing*/
	}


}
