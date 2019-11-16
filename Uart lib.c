#include <MKL25Z4.H>
#include "uart.h"
int main (void) {

char c[32];
while (1) {
UART0_init(14400);
UART0_Read(c);
UART0_Write(c);
UART0_nline();
}
}
