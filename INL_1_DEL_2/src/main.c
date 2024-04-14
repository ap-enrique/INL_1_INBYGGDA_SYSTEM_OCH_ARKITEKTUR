#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"

int main(void) {
    uart_init();                        // Konfigurera UART först

    while (1) {
        uart_putstr("Summer is HERE!"); // 
        _delay_ms(1000);                // Fördröjning med 1 sekund
    }

    return 0;
}