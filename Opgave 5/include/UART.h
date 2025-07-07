/*
Formål: Modul til at implementere UART-kommunikation på AVR mikrocontrollere, 
tilpasset til en specifik baudrate og CPU-frekvens. Det tilbyder grundlæggende 
funktioner til at initialisere UART, sende og modtage tegn og strengedata.

Input:
- unsigned int ubrr: Baud rate register værdi for initialisering af UART.
- char data, const char *str, char *str, uint16_t maxLen: Parametre til transmission og modtagelse af data.

Output:
- Funktionerne styrer dataoverførsel via UART og returnerer data som modtages fra UART.

Bruger:
- <stdint.h> for standard integer definitioner.
- Konstanter som BAUD, F_CPU, og MYUBRRF for at definere kommunikationshastigheder og systemkonfigurationer.

Author: Benjamin Hadziosmanovic, Ali Al-Sayad, Younes Humadi
   Company: DTU
   Version: 1.0
   Date and year: 4/5 2024
*/
#define BAUD 19200
#define F_CPU 16000000UL
#define MYUBRRF F_CPU/8/BAUD-1
#include <stdint.h>
//Funktioner
extern void uart0_Init(unsigned int ubrr);
extern char getchUSART0(void);
extern void putchUSART0(char tx);
extern void putsUSART0(char *ptr);
// Funktion til at sende et enkelt tegn via UART
void uart_transmit(char data);

// Funktion til at modtage et enkelt tegn via UART
char uart_receive(void);

// Funktion til at sende en streng via UART
void uart_sendString(const char *str);

// Funktion til at læse en streng via UART, med en maksimal længde angivet af maxLen
void uart_readString(char *str, uint16_t maxLen); 
