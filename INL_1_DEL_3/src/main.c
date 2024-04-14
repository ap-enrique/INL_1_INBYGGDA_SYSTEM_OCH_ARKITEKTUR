#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "serial.h"

#define BUFFER_SIZE 64

volatile char rx_buffer[BUFFER_SIZE];
volatile uint8_t rx_buffer_index = 0;

ISR(USART_RX_vect) {
    char received_char = UDR0; // Läs in det mottagna tecknet
    rx_buffer[rx_buffer_index++] = received_char; // Lägg till tecknet i mottagningsbufferten

    // Om mottagningsbufferten är full eller vi har mottagit ett nytt radtecken
    if (rx_buffer_index >= BUFFER_SIZE || received_char == '\n') {
        // Skriv ut den mottagna strängen på Serial Monitor
        for (uint8_t i = 0; i < rx_buffer_index; i++) {
            uart_putchar(rx_buffer[i]);
        }
        // Nollställ buffertindex för nästa mottagning
        rx_buffer_index = 0;
    }
}

int main(void) {
    uart_init();        // konfigurera UART först från start

    sei();              // Aktivera globala avbrott

    while (1) {
        uart_echo();    // Skicka strängen via UART från TX till RX
    }

    return 0;
}