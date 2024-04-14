#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PIN PINB1
#define LED_PIN    PB0

void setup(void) {
    // Port pin Configuration (ATmega328P pdf, sid. 60)
    DDRB &= ~(1 << DDB1);                 //Sätta PINB1 som input - DDB1 har bitposition 1
    DDRB |= (1 << DDB0);                  //Sätta PB0 som output - DDB0 har bitposition 0
}

int main(void) {
    setup();                              //Anropa funktionen setup för konfiguration.

    while (1) {
        if (PINB & (1 << PINB1)) {        //När PINB är 1 då knappen har trycks är lika som PINB1 och har samma bitposition.
            PORTB ^= (1 << PB0);          //XOR operation ändrar Port B Data register status för LED lampan. Mellan att det lyser eller inte lyser.
            _delay_ms(200);               //Debounce i form av kort paus.
            while (PINB & (1 << PINB1));  //Det blir falsk när man släpper knappen. Det är sätt att hålla reda på knappens tillstånd. Nertryck eller släppt.
        }
    }
    return 0;
}