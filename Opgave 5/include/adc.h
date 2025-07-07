/* Purpose: Initialisering og håndtering af ADC på en Arduino platform.
   Input: pwmMax og pwmMin for at justere ADC processering baseret på PWM duty cycle værdier.
   Output: adcValue - den seneste ADC-læsning. adcReady-flaget sættes til true, når en ny ADC-værdi er tilgængelig.
   Uses: Standardbiblioteker som <stdint.h>, <Arduino.h>, <stdio.h>, <avr/io.h>, <stdlib.h>, <util/delay.h>, og <avr/interrupt.h>.
   Author: Benjamin Hadziosmanovic, Ali Al-Sayad, Younes Humadi
   Company: DTU
   Version: 1.0
   Date and year: 4/5 2024
*/

#ifndef ADC_H
#define ADC_H
#include <stdint.h>
#include <Arduino.h>
#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//globale variabler
extern volatile bool adcReady;
extern volatile uint16_t adcValue;

extern volatile uint8_t pwmMax;  // Maksimal PWM duty cycle, standardværdi
extern volatile uint8_t pwmMin;    // Minimal PWM duty cycle, standardværdi
//Funktioner
void initADC();
void processADC();

#endif
