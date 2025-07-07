/*
Formål: Modulet håndterer debounce-logik for knapper 
og konfiguration af eksterne interrupts til at reagere 
på knappetryk. Det er designet til at stabilisere input 
fra mekaniske knapper og forenkle håndteringen af hardwarebaserede brugerinteraktioner.

Input:
- uint8_t pin: Pinnummeret, som debouncing og interrupt-konfigurationen anvender.

Output:
- debounce-funktionen returnerer knaptilstanden efter anvendelse af debounce-logik.
- Interrupts aktiveres eller deaktiveres via enable_interrupts() og disable_interrupts().

Bruger:
- "externInt.h" for funktionsprototyper og konstantdefinitioner.
- Standardbiblioteker som <avr/io.h> og <util/delay.h> bruges til direkte hardwarekontrol og forsinkelser.

Author: Benjamin Hadziosmanovic, Ali Al-Sayad, Younes Humadi
   Company: DTU
   Version: 1.0
   Date and year: 4/5 2024
*/
#include "externInt.h" 
#define BUTTON_PIN PE4 // Definerer pin-nummeret for knappen som PE4
#include <avr/io.h>
#include <util/delay.h>

#define DEBOUNCE_DELAY 50

// Funktion til at udføre debouncing på en given pin
uint8_t debounce(uint8_t pin) {
    static uint8_t lastState = 1; // Antager pull-up modstand, bruger direkte 1 i stedet for HIGH
    uint8_t currentState = PINE & (1 << pin);

    if (currentState != lastState) {
        _delay_ms(DEBOUNCE_DELAY); // Debounce-forsinkelse
        currentState = PINE & (1 << pin); // Genlæs pin-tilstanden efter forsinkelsen
    }

    lastState = currentState;
    return currentState ? 0 : 1; // Returnerer 0 hvis høj, 1 hvis lav (inverteret på grund af pull-up)
}

// Funktion til at aktivere interrupts
void enable_interrupts() {
    // Aktiverer eksterne interrupts
    sei();
}

// Funktion til at deaktivere interrupts
void disable_interrupts() {
    // Deaktiverer eksterne interrupts
    cli();
}

// Konfigurer eksternt interrupt for BUTTON_PIN
void initButtonInterrupt() {
    DDRB &= ~(1 << BUTTON_PIN);  // Sætter knappens pin som input
    PORTE |= (1 << BUTTON_PIN);  // Aktiverer pull-up modstand

    EICRB |= (1 << ISC41);       // Udløs på faldende kant
    EIMSK |= (1 << INT4);        // Aktiver INT4
}
