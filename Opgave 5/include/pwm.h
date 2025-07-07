/*
Formål: Dette modul håndterer PWM-funktionaliteter på AVR mikrocontrollere,
 med fokus på LED-belysning og motorstyring. Det understøtter dynamisk justering af PWM via UART og OLED.

Input:
- uint8_t dutyCycle: Styrer PWM-outputtet.

Output:
- Modulet styrer PWM-outputs og kommunikation via UART/OLED.

Bruger:
- <stdint.h>, <Arduino.h>, <stdio.h>, <avr/io.h>, <stdlib.h>, <util/delay.h>, <avr/interrupt.h> til funktioner og hardwareinteraktion.

Author: Benjamin Hadziosmanovic, Ali Al-Sayad, Younes Humadi
   Company: DTU
   Version: 1.0
   Date and year: 4/5 2024
*/
#ifndef PWM_H
#define PWM_H
#include <stdint.h>
#include <Arduino.h>
#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//Globale Variabler
#define LED_PIN PB5  // Definerer pin 11 som PWM-kompatibel
#define BUTTON_PIN PE4 // Definerer pin-2 for knappen som PE4

//Funktioner
void setupPWM();
void setPWMDutyCycle(uint8_t dutyCycle);
void initUARTAndOLED();
void readPWMSettings();
void askPWMValues();
#endif