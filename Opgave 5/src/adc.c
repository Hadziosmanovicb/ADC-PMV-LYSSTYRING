/*
Formål: Modul til at styre ADC (Analog-to-Digital Converter) 
og PWM (Pulse Width Modulation) operationer på AVR mikrocontrollere. 
Det indsamler analoge data, omdanner dem til digitale værdier, beregner
 spændingsværdier og justerer PWM duty cycle baseret på disse målinger. Dataene sendes også til UART for visning.

Input:
- Ingen eksterne inputs kræves direkte af funktionerne, 
men ADC konfigurationerne afhænger af systemets hardwareopsætning og tilkoblede sensorer.

Output:
- ADC data behandles til at styre PWM-output og sende formateret tekst via UART til eksterne enheder eller displayenheder.

Bruger:
- Modulerne 'adc.h', 'UART.h', og 'pwm.h' er nødvendige for at implementere funktionaliteterne korrekt.
- Benytter standardbibliotekerne som <avr/io.h>, <Arduino.h>, <stdio.h>, <stdlib.h>, og <util/delay.h> for at interagere med hardwaren og foretage nødvendige beregninger og timing.

Author: Benjamin Hadziosmanovic, Ali Al-Sayad, Younes Humadi
   Company: DTU
   Version: 1.0
   Date and year: 4/5 2024
*/
#include "adc.h"
#include <avr/io.h>
#include <Arduino.h>
#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "pwm.h"

// Initialiserer globale variabler for ADC-klar og ADC-værdi med standardværdier
volatile bool adcReady = false;
volatile uint16_t adcValue = 0;

// Initialiserer globale variabler for maksimal og minimal PWM duty cycle med standardværdier
volatile uint8_t pwmMax = 255;  // Maksimal PWM duty cycle, standardværdi
volatile uint8_t pwmMin = 0;    // Minimal PWM duty cycle, standardværdi

// Initialiser ADC med de rette indstillinger for spændingsreference og justering
void initADC() {
    ADMUX = (1 << REFS0) | (0 << ADLAR); // Brug AVCC som reference, juster resultat til højre
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (7 << ADPS0); // Aktivér ADC og interrupt, sæt prescaler til 128
    ADCSRB = (0 << ADTS0) | (1 << ADTS1) | (1 << ADTS2); // Auto Trigger Source: Timer0 Compare Match A
}

// Behandler ADC-værdien og udfører passende handlinger
void processADC() {
    // ADC processing code
    float voltage = adcValue * 5.0 / 1023.0;
    int integerPart = (int)voltage;
    int decimalPart = (int)((voltage - integerPart) * 100);

    uint8_t pwmDuty = (uint8_t)((voltage / 5.0) * 255);
    pwmDuty = (pwmDuty < pwmMin) ? pwmMin : (pwmDuty > pwmMax) ? pwmMax : pwmDuty;
    setPWMDutyCycle(pwmDuty);

    char buffer[50];
    sprintf(buffer, "Voltage: %d.%02d V, PWM DC: %03d%%\n", integerPart, decimalPart, (int)((pwmDuty / 255.0) * 100));
    putsUSART0(buffer);
    sendStrXY(buffer, 3, 2);  // Assuming sendStrXY sends data to OLED
}

// Interrupt service rutine for når en ADC læsning er klar
ISR(ADC_vect) {
    adcValue = ADC;  // Læs ADC værdien
    adcReady = true;  // Sæt klar flaget
}
