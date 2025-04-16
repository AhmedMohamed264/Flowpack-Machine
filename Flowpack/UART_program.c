/*

 * UART_Program.c
 *
 *  Created on: Aug 29, 2023
 *      Author: Mazen
 */
#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "UART_REGISTER.h"

static void (*UART_pvCallBackFunc)(void) = NULL;
u8 GlobalUART_u8RXData;

void UART_voidInit(void)
{
	u8 UCSRC_Value = 0;

	/*Select Register UCSRC*/
	SET_BIT(UCSRC_Value,7); //0b10000000

	/*8Bits*/
	SET_BIT(UCSRC_Value,2);//0b10000100
	SET_BIT(UCSRC_Value,1);//0b10000110

	UCSRC=UCSRC_Value;

	/*Baud Rate 9600 bit/sec -> 51*/
	UBRRL=51;

	/*Enable */
	SET_BIT(UCSRB,UCSRB_RXEN);
	SET_BIT(UCSRB,UCSRB_TXEN);
	SET_BIT(UCSRB, UCSRB_RXCIE); // RECEIVE INTERRUPT ENABLE
}


void UART_voidSendData(u8 Copy_Data)
{
	/*wait Until Flag is one To sur that Empty*/
	while((GET_BIT(UCSRA,UCSRA_UDRE))==0);
	{
		UDR=Copy_Data;
	}
}

u8 UART_u8RecieveData(void)
{
	/*wait Until Uart Receive Data*/
	while((GET_BIT(UCSRA,UCSRA_RXC)==0));

	/*Receive the Data*/
	return UDR;
}

void UART_voidSendString(const char* str)
{
    while (*str) {
    	UART_voidSendData(*str);
        str++;
    }

    UART_voidSendData('\0');
}

u32 UART_u32ReceiveString(char* buffer, u32 bufferSize)
{
    u32 count = 0;
    char receivedChar;

    while (count < bufferSize - 1) {
        receivedChar = UART_u8RecieveData(); // Assuming UART_u8ReceiveData is a function to receive a single character

        if (receivedChar == '\r' || receivedChar == '\n' || receivedChar == '\0') {
            break; // Stop receiving if newline or carriage return is received
        }

        buffer[count] = receivedChar;
        count++;
    }

    buffer[count] = '\0'; // Null-terminate the received string
    return count;
}

u8 UART_u8RXSetCallBack(void(*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorStatus = OK;

	if(Copy_pvCallBackFunc != NULL)
	{
		UART_pvCallBackFunc = Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorStatus = NULL_POINTER;
	}
	return Local_u8ErrorStatus;
}

void __vector_13 (void) __attribute__((signal));
void __vector_13 (void)
{
	if(UART_pvCallBackFunc != NULL)
	{
		GlobalUART_u8RXData = UDR;
		UART_pvCallBackFunc();
	}
}