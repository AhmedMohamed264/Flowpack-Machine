/*****************************************************************/
/*****************************************************************/
/*************     Author: Abdallah Mohammed     *****************/
/*************     layer: MCAL                   *****************/
/*************     SWC: interrupt                *****************/
/*************     Version : 1.00                *****************/
/*************     Date :16/8/2023               *****************/
/*****************************************************************/
/*****************************************************************/
#ifndef EXTI_CONFIG_H_INCLUDED
#define EXTI_CONFIG_H_INCLUDED

/* OPTIONS:
 *   1-LOW_LEVEL
 *   2-ON_CHANGE
 *   3-FALLING_EDGE
 *   4-RISING_EDGE     */

#define INT0_SENSE   FALLING_EDGE
#define INT1_SENSE   FALLING_EDGE
/////////////////////////////////////////////////////////////
/* OPTIONS:
 *   1-FALLING_EDGE
 *   2-RISING_EDGE     */
#define INT2_SENSE RISING_EDGE
/////////////////////////////////////////////////////////////
/* OPTIONS:
 *   1-ENABLED
 *   2-DISABLED   */

#define INT0_INITAL_STATE  ENABLED
#define INT1_INITAL_STATE  DISABLED
#define INT2_INITAL_STATE  DISABLED


#endif // EXTI_CONFIG_H_INCLUDED
