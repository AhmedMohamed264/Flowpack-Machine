/*****************************************************************/
/*****************************************************************/
/*************     Author: Abdallah Mohammed     *****************/
/*************     layer: MCAL                   *****************/
/*************     SWC: interrupt                *****************/
/*************     Version : 1.00                *****************/
/*************     Date :16/8/2023               *****************/
/*****************************************************************/
/*****************************************************************/
#ifndef EXTI_REGISTER_H_INCLUDED
#define EXTI_REGISTER_H_INCLUDED

#define GICR    *((volatile u8*)0x5B)
#define GICR_INT0    6
#define GICR_INT1    7
#define GICR_INT2    5


#define GIFR    *((volatile u8*)0x5A)

#define MCUCR   *((volatile u8*)0x55)
#define MCUCR_ISC11  3
#define MCUCR_ISC10  2
#define MCUCR_ISC01  1
#define MCUCR_ISC00  0

#define MCUCSR  *((volatile u8*)0x54)
#define MCUCSR_ISC2 6




#endif // EXTI_REGISTER_H_INCLUDED
