/*
Formål: Modulerer håndtering af Timer 0 på AVR 
mikrocontrollere til at skabe præcise tidsintervaller og håndtere knaptryk.
   
Input: Ingen direkte input parametre, men modulet 
reagerer på systemtilstande og hardwarehændelser.

Output: Påvirker mikrocontrollerens adfærd via 
timingsekvenser, herunder indstilling af flag og udløsning af rutiner via interrupts.

Bruger: Anvender <Arduino.h>, <stdio.h>, <avr/io.h>, <stdlib.h>, <util/delay.h>, <avr/interrupt.h> for funktionaliteter som datatyper, I/O operationer, og interrupt håndtering.

Author: Benjamin Hadziosmanovic, Ali Al-Sayad, Younes Humadi
   Company: DTU
   Version: 1.0
   Date and year: 4/5 2024
*/
#ifndef TIMER_H
#define TIMER_H
#include <Arduino.h>
#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
//Globale variabler
extern volatile uint8_t button_pressed; // Deklarerer en variabel for at angive om knappen er blevet trykket
//Funktioner
void initTimer0();

#endif
