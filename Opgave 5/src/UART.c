/*
Formål: Dette modul implementerer grundlæggende UART (Universal Asynchronous Receiver-Transmitter) funktionaliteter for at muliggøre dataudveksling mellem mikrocontrolleren og andre enheder via seriel kommunikation.

Input:
- 'baudRate' for initiering, som bestemmer kommunikationshastigheden.
- Data eller strenge, der sendes eller modtages gennem UART.

Output:
- Sender og modtager data mellem mikrocontrolleren og eksterne enheder.
- Funktioner til at sende og modtage både enkelte karakterer og hele strenge.

Bruger:
- "UART.h" for at definere og referere til nødvendige funktioner og opsætninger.
- Direkte manipulation af AVR's hardware-registre til at kontrollere UART opsætningen.

Funktioner:
- uart0_Init(): Initialiserer UART med en specificeret baudrate.
- putsUSART0(), putchUSART0(), uart_transmit(): Funktioner til at sende data.
- uart_receive(), uart_sendString(), uart_readString(): Funktioner til at modtage data og håndtere string inputs.

Author: Benjamin Hadziosmanovic, Ali Al-Sayad, Younes Humadi
   Company: DTU
   Version: 1.0
   Date and year: 4/5 2024
*/
#include "UART.h"
#include <avr/io.h>
#include <stdio.h>
#include <Arduino.h>
#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void uart0_Init(unsigned int baudRate) {
    UCSR0A = 0; // Deaktiver U2X mode
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);  // Aktivér receiver og transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data
    unsigned int ubrr = F_CPU / 16 / baudRate - 1;
    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;
}

void putsUSART0(char *ptr) {
    while (*ptr) {
        putchUSART0(*ptr++);
    }
}

void putchUSART0(char tx) {
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = tx;  // Send tegn
}

void uart_transmit(char data) { // Funktion til at transmittere et enkelt tegn
    while (!(UCSR0A & (1 << UDRE0))); // Venter indtil data registeret er klar til transmission
    
    UDR0 = data; // Sender data
}

char uart_receive(void) { // Funktion til at modtage et enkelt tegn
    while (!(UCSR0A & (1 << RXC0))); // Venter indtil data er modtaget
    
    return UDR0; // Returnerer modtaget data
}

void uart_sendString(const char *str) { // Funktion til at transmittere en streng
    while (*str) { // Loop indtil nulltermineringen af strengen
        uart_transmit(*str++); // Transmitter hvert tegn i strengen
    }
}

void uart_readString(char *str, uint16_t maxLen) {
    memset(str, 0, maxLen);  // Nulstil hele bufferen før brug
    uint16_t i = 0;
    char c;

    while (i < maxLen - 1) {  // Justeret for at undgå buffer overflow
        c = uart_receive();
        if (c == '\r' || c == '\n') {
            if (c == '\r') {  // Check efterfølgende '\n' hvis tilstede
                c = uart_receive();
                if (c != '\n') {
                    str[i++] = '\r';  // Hvis ingen '\n', gem '\r'
                }
            }
            break;  // Stop læsning ved første linjeafslutning
        }
        str[i++] = c;
    }
    str[i] = '\0';  // Sikrer korrekt string afslutning
}
