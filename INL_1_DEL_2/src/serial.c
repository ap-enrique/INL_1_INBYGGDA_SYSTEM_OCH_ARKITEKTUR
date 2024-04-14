#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"

void uart_init(void) {
    // Konfigurera Baud hastighet till 9600
    // UBRR0 är 16-bitarsregister. UBRR0H (HIGH) 8 bitars Mest signifikanta och UBRR0L (LOW) 8 bitar minst signifikanta
    // Arduino använder 16 MHz

    // Baudrate = (Clock frequency) / (16 * (UBRR + 1))
    // UBRR = (Clock frequency/(16*Baudrate)) - 1
    // UBRR = (16MHz/(16 bitar * 9600 Baudrate)) = 103.1667

    UBRR0H = (uint8_t)(103 >> 8);   // (0b0110 0111 >> 8 bit positioner till höger) = (0b0000 0000)
    UBRR0L = (uint8_t)103;

    // Enable transmiter 
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);  // (00000001 << 3) | (00000001 << 5) ; (TXEN0 har position bit 3 och RXEN0 har bitposition 5)

    // Set frame format:
    // 8 data bits => UCSZ02 = 0, UCSZ01 = 1, UCSZ00 = 1
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);     // (00000001 << 2) | (00000001 << 1) ; (UCSZ01 har bitposition 2 och UCSZ00 har bitposition 1)
    
    // Paritetsbitsinställningarna (UPM01 och UPM00) är redan 0 som standard (No Parity)
    // USBS0 är redan 0 som standard, vilket innebär en stoppbit (1 stop bit => USBS0 = 0)
    // UMSEL00 och UMSEL01 är redan som standard noll och det är Asynchronous USART
}

void uart_putchar(char c) {
    // UCSR0A = (00100000) från start
    // Det är sant när bufferten tom och är klar och falskt när den är upptagen
    // (!(00100000 & (00000001 << 5)))
    while (!(UCSR0A & (1 << UDRE0))) { // När UDRE0 är 1, kan vi fortsätta att skriva till buffer tills hela strängen är klar. 
        UDR0 = c;
    };  
}

void uart_putstr(const char *str) { // Pekaren pekar på adressen av den första tecken av strängen
    // En while-loop används för att gå igenom varje tecken i den inmatade strängen
    while (*str) {  // Loopen fortsätter så länge *str inte är lika med noll dvs. tills den når slutet av strängen där *str är ('\0'), vilket indikerar slutet på strängen.
        uart_putchar(*str++);   // Adressen för Varje tecken sänds till buffer sändningen 
    }
    uart_putchar('\n'); // strängen avslutas med speciellt tecken för newline. Detta för att nästa nya sträng hamnar på en ny rad.
}