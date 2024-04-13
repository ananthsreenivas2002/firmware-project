#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#define BAUD 2400
#define MYUBRR F_CPU/16/BAUD-1

volatile uint8_t data;
volatile bool data_received = false;

void USART_Init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void USART_Transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

ISR(USART_RX_vect) {
    data = UDR0;
    data_received = true;
}

int main() {
    USART_Init(MYUBRR);
    sei();

    while (1) {
        if (data_received) {
            USART_Transmit(data);
            data_received = false;
        }
    }
    return 0;
}
