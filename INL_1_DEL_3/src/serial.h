#ifndef SERIAL_H_
#define SERIAL_H_

void uart_init(void);
void uart_putchar(char c);
char uart_getchar(void);
void uart_echo(void);
void uart_putstr(const char *str);

#endif /* SERIAL_H_ */
