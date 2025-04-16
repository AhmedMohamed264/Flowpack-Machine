/*****************************************************************/
/*****************************************************************/
/*************     Author: Abdallah Mohammed     *****************/
/*************     layer: MCAL                   *****************/
/*************     SWC: interrupt                *****************/
/*************     Version : 1.00                *****************/
/*************     Date :16/8/2023               *****************/
/*****************************************************************/
/*****************************************************************/
#ifndef EXTI_INTERFACE_H_INCLUDED
#define EXTI_INTERFACE_H_INCLUDED

#define LOW_LEVEL     1
#define ON_CHANGE     2
#define FALLING_EDGE  3
#define RISING_EDGE   4

#define ENABLED       1
#define DISABLED      2

void EXTI_VoidInt0_Init(void);

void EXTI_VoidInt1_Init(void);

void EXTI_VoidInt2_Init(void);
/* Description: A function to set the required sense control of (INT0,INT1) using postbuild configuration
 * input:  Copy_u8Sense , output:1- LOW_LEVEL
 *                               2- ON_CHANGE
 *                               3- FALLING_EDGE
 *                               4- RISING_EDGE
 *output :error status with type u8
 **/
u8 EXTI_u8Int0SetSenseControl(u8 Copy_u8Sense);
u8 EXTI_u8Int1SetSenseControl(u8 Copy_u8Sense);
/* Description: A function to set the required sense control of (INT2) using postbuild configuration
 * input:  Copy_u8Sense , output:1- FALLING_EDGE
 *                               2- RISING_EDGE
 *output :error status with type u8
 **/
u8 EXTI_u8Int2SetSenseControl(u8 Copy_u8Sense);

u8 EXTI_u8IntEnable(u8 Copy_u8INT);
u8 EXTI_u8IntDisable(u8 Copy_u8INT);

u8 EXTI_u8INT0SetCallBack(void (*Copy_pvInt0Func)(void));
u8 EXTI_u8INT1SetCallBack(void (*Copy_pvInt1Func)(void));
u8 EXTI_u8INT2SetCallBack(void (*Copy_pvInt2Func)(void));
#endif // EXTI_INTERFACE_H_INCLUDED
