/*********************************************************/
/*********************************************************/
/**************     Author: Ahmed Osama    ***************/
/**************     Layer:  HAL            ***************/
/**************     Component: CLCD        ***************/
/**************     Version:1.00           ***************/
/*********************************************************/
/*********************************************************/


/*preprocessor file guard*/

#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_


/*LCD DATA PORT*/
#define CLCD_DATA_PORT      DIO_u8PORTA

/*8 BIT MODE DATA PORT*/
#define CLCD_CTRL_PORT      DIO_u8PORTB

/*LCD CONTROL PINS*/
#define CLCD_RS_PIN         DIO_u8PIN0
#define CLCD_RW_PIN         DIO_u8PIN1
#define CLCD_E_PIN          DIO_u8PIN2

#define CLCD_MODE			M_8BIT






#endif
