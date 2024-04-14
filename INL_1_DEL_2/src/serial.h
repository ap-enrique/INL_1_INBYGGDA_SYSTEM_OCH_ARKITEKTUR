#ifndef SERIAL_H_
#define SERIAL_H_

void uart_init(void);
void uart_putchar(char c);
void uart_putstr(const char *str);

#endif /* SERIAL_H_ */