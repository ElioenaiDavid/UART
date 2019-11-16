/*
 * uart.h
 *
 *  Created on: 13 nov. 2019
 *      Author: David
 */

#ifndef UART_H_
#define UART_H_
void delayMs(int n);
void UART0_init(int v);
void UART0_Write(char c[32]);
void UART0_Read(char v[32]);
void UART0_nline(void);
void UART2_init(void);
void UART2_Write(char c[32]);
void UART2_Read(char v[32]);
void UART2_nline(void);

#endif /* UART_H_ */
