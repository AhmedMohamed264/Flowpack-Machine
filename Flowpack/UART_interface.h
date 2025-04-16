/*
 * UART_interface.h
 *
 *  Created on: Aug 29, 2023
 *      Author: conncet
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_voidInit(void);

void UART_voidSendData(u8 Copy_u8Data);

u8 UART_u8RecieveData(void);

void UART_voidSendString(const char* str);

u32 UART_u32ReceiveString(char* buffer, u32 bufferSize);

u8 UART_u8RXSetCallBack(void(*Copy_pvCallBackFunc)(void));

#endif /* UART_INTERFACE_H_ */
