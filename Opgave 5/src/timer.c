/*
Formål: Modulet initialiserer og håndterer Timer0 i CTC (Clear Timer on Compare Match) mode for at generere præcise timings til ADC-konverteringer. Det håndterer også eksterne interrupts for at detektere knaptryk.

Input:
- Ingen eksterne inputs direkte til funktionerne, men timer og interrupt reagerer på systemets tidsintervaller og eksterne knaptryk.

Output:
- initTimer0 funktionen konfigurerer Timer0 og aktiverer interrupts, der trigger ADC-konvertering ved hver timer compare match.
- Interrupt-rutinen for INT4 detekterer, om en specifik knap er blevet trykket og sætter en flag.

Bruger:
- "timer.h" og <avr/interrupt.h> for interrupt-funktionalitet og timerkonfiguration.
- Timer- og interrupt-registre manipuleres direkte via hardware-specifikke operationer.

Funktioner:
- initTimer0(): Sætter Timer0 til CTC mode og definerer frekvensen og prescaleren for at matche systemets krav.
- ISR(TIMER0_COMPA_vect): Udløser en ADC-konvertering som respons på timer compare matches.
- ISR(INT4_vect): Kontrollerer tilstanden af en bestemt knap og sætter en flag, hvis den er trykket ned.

Author: Benjamin Hadziosmanovic, Ali Al-Sayad, Younes Humadi
   Company: DTU
   Version: 1.0
   Date and year: 4/5 2024
*/
#include "timer.h" 
#include <avr/interrupt.h> 

volatile uint8_t button_pressed = 0; // Variabel til at angive om knappen er blevet trykket

// Opsæt Timer0 til CTC mode
void initTimer0() {
    TCCR0A |= (1 << WGM01);  // Sæt Timer0 til CTC mode
    OCR0A = 13;  // For ca. 9500 Hz ved 8 MHz CPU med en prescaler på 64
    TCCR0B |= (1 << CS01) | (1 << CS00);  // Prescaler: 64
    TIMSK0 |= (1 << OCIE0A);  // Aktivér Timer0 Compare Match A Interrupt
}

// Interrupt service rutine for Timer0 CTC afbrydelse
ISR(TIMER0_COMPA_vect) {
    ADCSRA |= (1 << ADSC);  // Start en ADC konvertering
}

// Interrupt service rutine for ekstern interrupt INT4
ISR(INT4_vect) {
    // Tjek om knappen er i lav tilstand (trykket)
    if (!(PINE & (1 << PE4))) {
        button_pressed = 1;
    }
}
