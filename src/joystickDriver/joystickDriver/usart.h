
#ifndef usart_h
#define usart_h

#include <stdio.h>

/*
 *	Define la velocidad de transmisión del USART (en bits/segundo), si aún no 
 *	ha sido definida.
 *
 */

#ifndef USART_BAUD
#define USART_BAUD  9600UL
#endif



// Macros para AVR GCC 

#if defined( __GNUC__ )
#ifdef putchar
#undef putchar
#endif
#ifdef getchar
#undef getchar
#endif
#endif


// Configurar Usart
void setUpUsart(uint16_t ubrr)
{
    UCSRA |= (0<<U2X);
    UBRRH = (uint8_t) (ubrr >>8);
    UBRRL = (uint8_t) ubrr;   
 
 
    UCSRC = (1<<UCSZ1)|(1<<UCSZ0);
    
    UCSRB = (1<<RXEN)|(1<<TXEN);

// Asociar las funciones 'putchar' y 'getchar' con las funciones de entrada
// y salida (como printf, scanf, etc.)
#if defined( __GNUC__ )
    fdevopen((int (*)(char, FILE*))putchar, (int (*)(FILE*))getchar);
#endif

}
// Enviar un dato
int putchar(int dato)
{
    while ((UCSRA & (1<<UDRE)) == 0 );

    UDR = dato;
    return dato;
}

// Recibir un dato
int getchar(void)
{
    while ((UCSRA & (1<<RXC)) == 0 );   
    return UDR;
}
#endif
