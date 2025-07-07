/*
Formål: Hovedprogrammet koordinerer initialisering og løbende styring af flere hardwaremoduler i et AVR-baseret system. Det håndterer brugerinput via UART, justerer PWM-indstillinger, og behandler ADC-læsninger.

Input:
- Brugeren indtaster data via UART for at justere PWM-indstillinger.
- ADC-data indsamles automatisk når de er klar.

Output:
- Systemet justerer PWM-output baseret på brugerinput.
- Viser status og fejlmeddelelser via UART.

Bruger:
- Inkluderer moduler som "UART.h", "ssd1306.h", "I2C.h", "pwm.h", "adc.h", "timer.h", og "externInt.h" for at håndtere forskellige funktioner i systemet.
- Anvender <Arduino.h>, <stdio.h>, <avr/io.h>, <stdlib.h>, <util/delay.h>, <avr/interrupt.h> for integration og interaktion med AVR-hardwaren.

Funktioner:
- initUARTAndOLED(), uart0_Init(), initADC(), setupPWM(), initTimer0(), initButtonInterrupt(): Initialiserer de forskellige systemkomponenter.
- sei(): Aktiverer globale interrupts for at tillade interrupt-drevet handling.
- Hovedløkken behandler knaptryk for at modtage og validere brugerinput og ajourfører systemindstillinger baseret på dette.

Author: Benjamin Hadziosmanovic, Ali Al-Sayad, Younes Humadi
   Company: DTU
   Version: 1.0
   Date and year: 4/5 2024
*/
#include <Arduino.h>
#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "ssd1306.h"
#include "I2C.h"
#include "pwm.h"
#include "adc.h"
#include "timer.h"
#include "externInt.h"

#define LED_PIN PB5  // Definerer pin 11 som PWM-kompatibel
#define BUTTON_PIN PE4 // Definerer pin-2 for knappen som PE4

int main(void) {
    initUARTAndOLED();
    askPWMValues();
    uart0_Init(19200);
    initADC();
    setupPWM();
    initTimer0();
    initButtonInterrupt();
    sei();  // Enable global interrupts
    char buffer[100];  // Buffer to hold strings for output

    while (1) {
        if (button_pressed) {
            int newMax, newMin;
            while (1) {
                uart_sendString("Enter new max-min PWM values (format 'max-min'):\n");
                char pwmInput[15];
                uart_readString(pwmInput, sizeof(pwmInput));
                int parsedItems = sscanf(pwmInput, "%d-%d", &newMax, &newMin);

                if (parsedItems != 2) {
                    uart_sendString("Error: Invalid input format. Please ensure the format is 'max-min'.\n");
                    continue;
                }
                
                if (newMax > 255 || newMin > 255 || newMax < 0 || newMin < 0) {
                    uart_sendString("Error: Values must be between 0 and 255.\n");
                    continue;
                }

                if (newMin > newMax) {
                    uart_sendString("Error: Minimum value cannot be greater than maximum value.\n");
                    continue;
                }

                break;  // Ud af loop når rigtige værdier er indtastet
            }
            pwmMax = newMax;
            pwmMin = newMin;
            sprintf(buffer, "New settings: Max = %d, Min = %d\n", pwmMax, pwmMin);
            uart_sendString(buffer);

            // Clear the button pressed flag
            button_pressed = 0;
        }

        if (adcReady) {
            processADC();
        }
    }
}
