/* Formål: Håndtering af eksterne afbrydelser med debounce-funktionalitet for AVR mikrocontrollere.
   Input: `uint8_t pin` parameter repræsenterer mikrocontroller pin tilkoblet til en knap.
   Output: Debounce-funktionen returnerer en `uint8_t` værdi (HIGH eller LOW).
   Brug: Standardbiblioteker som <avr/io.h> og <avr/interrupt.h> anvendes.
   Konstanter som `HIGH`, `LOW`, og `DEBOUNCE_DELAY` er defineret internt.
   Author: Benjamin Hadziosmanovic, Ali Al-Sayad, Younes Humadi
   Company: DTU
   Version: 1.0
   Date and year: 4/5 2024
*/

#ifndef externInt_H_
#define externInt_H_
#ifndef HIGH
#define HIGH 0x1
#endif
#include <avr/io.h>
#include <avr/interrupt.h>
#define DEBOUNCE_DELAY 50
//Funktioner
uint8_t debounce(uint8_t pin);
void enable_interrupts();
void disable_interrupts();
void initButtonInterrupt();

#endif /* externInt_H_ */
#ifndef LOW
#define LOW 0x0
#endif