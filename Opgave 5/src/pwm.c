/*
Formål: Implementerer styring af PWM for LED-belysning og kommunikation via UART. Modulerne koordinerer input fra brugeren til at justere PWM-indstillinger og visualiserer oplysninger på et OLED-display.

Input:
- Brugeren angiver maksimale og minimale PWM duty cycle værdier via UART.

Output:
- Justerer LEDens lysstyrke baseret på PWM-værdier.
- Feedback til brugeren om de indtastede og behandlede værdier via UART og OLED.

Bruger:
- "pwm.h", "UART.h", "I2C.h", "ssd1306.h", og "adc.h" for at implementere de nødvendige funktioner for modulinteraktion.
- Standardbiblioteker som <stdio.h> og <avr/io.h> til datahåndtering og hardwarekontrol.

Funktioner:
- setupPWM(): Konfigurerer PWM-hardware til LED-styring.
- setPWMDutyCycle(): Justerer PWM duty cycle baseret på brugerinput.
- askPWMValues(): Anmoder om og validerer PWM-værdier fra brugeren.
- initUARTAndOLED(): Initialiserer UART for kommunikation og OLED for display-output.

Author: Benjamin Hadziosmanovic, Ali Al-Sayad, Younes Humadi
   Company: DTU
   Version: 1.0
   Date and year: 4/5 2024
*/
#include "pwm.h"
#include <stdio.h>
#include <avr/io.h>
#include "ssd1306.h"
#include "UART.h"
#include "I2C.h"
#include "adc.h"

#define LED_PIN PB5  // Bruger pin 11, som er i stand til PWM

// Opsæt PWM-hardware til LED-kontrol
void setupPWM() {
    DDRB |= (1 << LED_PIN); // Sæt LED-pin som output
    TCCR1A |= (1 << COM1A1) | (1 << WGM10);
    TCCR1B |= (1 << WGM12) | (1 << CS11);
}

// Sæt PWM duty cycle
void setPWMDutyCycle(uint8_t dutyCycle) {
    OCR1A = dutyCycle; // Sæt PWM duty cycle
}

// Spørg brugeren om PWM-værdier
void askPWMValues() {
    char inputBuffer[15];  // Tilstrækkelig stor buffer til input
    char buffer[50];       // Til feedback via UART
    int tempMax, tempMin;
    int parsedItems;

    while (1) {  // Fortsæt indtil gyldige og logiske værdier er modtaget
        uart_sendString("Indtast maksimal og minimal PWM duty cycle (format 'max-min'):\n");
        uart_readString(inputBuffer, sizeof(inputBuffer));  // Læs input

        // Debug: Vis modtaget input
        sprintf(buffer, "Modtaget input: '%s'\n", inputBuffer);
        uart_sendString(buffer);

        // Parse input
        parsedItems = sscanf(inputBuffer, "%d-%d", &tempMax, &tempMin);

        // Debug: Vis parsed værdier
        sprintf(buffer, "Parsed max: %d, min: %d\n", tempMax, tempMin);
        uart_sendString(buffer);

        // Tjek parsing og værdiernes gyldighed
        if (parsedItems != 2) {
            uart_sendString("Fejl: Venligst sikre at formatet er 'max-min'.\n");
            continue;
        }

        // Tjek om værdierne er inden for det tilladte interval
        if (tempMax > 255 || tempMin > 255 || tempMax < 0 || tempMin < 0) {
            uart_sendString("Fejl: Værdier skal være mellem 0 og 255.\n");
            continue;  // Fortsætter med at bede om input
        }

        // Tjek om minimumsværdien er større end maksimumsværdien
        if (tempMin > tempMax) {
            uart_sendString("Fejl: Minimumsværdi kan ikke være større end maksimumsværdi.\n");
            continue;  // Fortsætter med at bede om input
        }

        break;  // Bryder løkken, når gyldige og logiske værdier er modtaget
    }

    // Opdater globale variabler efter gyldige værdier er modtaget
    pwmMax = (uint8_t)tempMax;
    pwmMin = (uint8_t)tempMin;

    // Bekræft indstillede værdier til brugeren
    sprintf(buffer, "Sæt max: %d, min: %d\n", pwmMax, pwmMin);
    uart_sendString(buffer);
}

// Initialiser UART og OLED
void initUARTAndOLED() {
    uart0_Init(19200); // Indstil baudrate eksplisit
    I2C_Init();
    InitializeDisplay();
    clear_display();
}
