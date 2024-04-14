#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"

void uart_init(void) {
    UBRR0H = (uint8_t)(103 >> 8);
    UBRR0L = (uint8_t)103;

    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);  // Aktivera både sändning och mottagning
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // För 8 bitars size [UCSZ02=0; UCSZ01=1; UCSZ00=1]
}

void uart_putchar(char c) {
    //SÄNDING FRÅN UART
    while (!(UCSR0A & (1 << UDRE0))) {  // När sändningsbufferten är tom
        UDR0 = c;                       // Skicka bit tecken till sändningsbufferten för sändning
    };

    // Utskrift på Serial Monitor för att visa vad som skickas
    uart_putstr("TX Sent: ");
    uart_putchar(c);
    uart_putstr("\n");
}

char uart_getchar(void) {
    //MOTTAGNING TILL UART
    while (!(UCSR0A & (1 << RXC0))) {   // Vänta tills mottagningsbufferten innehåller data
        //Gör inget bara vänta
    };

    char received_char = UDR0;      // Läs in det mottagna tecknet

    // Utskrift på Serial Monitor för att visa vad som mottagits
    uart_putstr("RX Received: ");
    uart_putchar(UDR0);
    uart_putstr("\n");

    return received_char;                        // Returnera det mottagna tecknet
}

void uart_echo(void) {
    char received_char = uart_getchar(); // Lagra i den char variabel från uart_getchar funktionen.
    uart_putchar(received_char);         // Skicka tillbaka samma tecken
}

// Funktion för att skriva ut en sträng via UART
void uart_putstr(const char *str) {
    while (*str) {
        uart_putchar(*str++);
    }
}