/*
 * uart.c
 *
 *  Created on: 13 nov. 2019
 *      Author: David
 */
#include <MKL25Z4.H>
#include "uart.h"
int VALUE;
void UART0_init(int v) {
	int L,H;
	switch (v)
			{
			case 2400:L=0x22;H=0x02;VALUE=2400; break;
			case 57600:L=0x17;H=0x00;VALUE=57600;  break;
			case 4800:L=0x11;H=0x01;VALUE=4800;  break;
			case 9600:L=0x89;H=0x00;VALUE= 9600;  break;
			case 19200:L=0x44;H=0x00;VALUE=19200;  break;
			case 14400:L=0x5B;H=0x00;VALUE=14400;  break;
			}

SIM->SCGC4 |= 0x0400; /* enable clock for UART0 */
SIM->SOPT2 |= 0x04000000;
UART0->C2 = 0; /* turn off UART0 while changing configurations */
UART0->BDH = H;
UART0->BDL = L; /* 115200 Baud */
UART0->C4 = 0x0F; /* Over Sampling Ratio 16 */
UART0->C1 = 0x00; /* 8-bit data */
UART0->C2 = 0xC; /* enable transmit */
SIM->SCGC5 |= 0x0200; /* enable clock for PORTA */
PORTA->PCR[2] = 0x0200; /* make PTA2 UART0_Tx pin */
PORTA->PCR[1] = 0x0200; /* make PTA1 UART0_Rx pin */
}
/* Delay n milliseconds */
/* The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit(). */
void delayMs(int n) {
int i;
int j;
for(i = 0 ; i < n; i++)
for (j = 0; j < 7000; j++) {}
}
void UART0_Write(char c[32])
{
	int i=0;
	for(i=0;c[i]!='\r'&&c[i]!='\n'&&c[i]!='\0'; i++)
	{while(!(UART0->S1 & 0x80)) { }
	UART0->D = c[i];

	}
}
void UART0_Read(char v[32]){
	for(int i=0;i<32; i++){
	UART0_init(VALUE);
	while(!(UART0->S1 & 0x20)) {
	} /* wait for receive buffer full */
	v[i] = UART0->D; /* read the char received */
if(v[i]=='\r'||v[i]=='\n'||v[i]=='\0'){
	i=50;
}
	}
}
void UART0_nline(void){
	while(!(UART0->S1 & 0x80)) { }
		UART0->D = '\r';
}
void UART2_init(void) {
SIM->SCGC4 |= 0x1000; /* enable clock to UART2 */
UART2->C2 = 0; /* disable UART during configuration */
UART2->BDH = 0x00;
UART2->BDL = 0x5B; /* 9600 Baud */
UART2->C1 = 0x00; /* normal 8-bit, no parity */
UART2->C3 = 0x00; /* no fault interrupt */
UART2->C2 = 0x0C; /* enable transmit and receive */
SIM->SCGC5 |= 0x1000; /* enable clock to PORTD */
PORTD->PCR[5] = 0x300; /* PTD5 for UART2 transmit */
PORTD->PCR[4] = 0x300; /* PTD5 for UART2 receive */
}
void UART2_Write(char c[32])
{
	int i=0;
	for(i=0;c[i]!='\r'&&c[i]!='\n'&&c[i]!='\0'; i++)
	{while(!(UART2->S1 & 0x80)) { }
	UART2->D = c[i];

	}
}
void UART2_Read(char v[32]){
	for(int i=0;i<32; i++){
	UART2_init();
	while(!(UART2->S1 & 0x20)) {
	} /* wait for receive buffer full */
	v[i] = UART2->D; /* read the char received */
if(v[i]=='\r'||v[i]=='\n'||v[i]=='\0'){
	i=50;
}
	}
}
void UART2_nline(void){
	while(!(UART2->S1 & 0x80)) { }
		UART2->D = '\r';
}
