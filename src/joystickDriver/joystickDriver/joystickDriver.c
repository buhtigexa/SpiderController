/*
 * joystickController.c
 * 
 *  Author: Rodríguez Marcelo 
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>


// Frecuencia del clock del microcontrolador.
#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

// ratio de transmision para la usart

#define FALSE 0U
#define TRUE  1U
#define externalVoltage 0x40
#define adcMode 0xA0	 //  si se dese free running mode : 0xA8. Por interrupciones 0x88



#include "usart.h"
#include "adc.h"
#include "pwmTimer.h"
#include "pwmPool.h"


int main(void)
{
   
	uint8_t channels;
	uint8_t maxChannels = 8;
	
	setUpUsart(MYUBRR);
	puts("\n\r ..................................................");
	puts("\n\r			<< Taller de µControladores >>");
	puts("\n\r Controlador de joystick");
	puts("\n\n\r Ingrese el número de dimensiones a controlar:");
	scanf("%u", &channels);
	printf("%u",channels);
	puts("\n\r ..................................................");
	
	if ((channels > 8) || (channels < 1))	{
		puts("\n\r Error: Límite de dimensiones excedido.");
	}
	
	else
	{

	
	pwmPool(channels);
	setUpAdc(channels,externalVoltage,adcMode);
	setUpTimer();
	sei();
	
	}		
	while(TRUE)
	{
			// dormir la cpu y dejar el ADC,TIMERS,USART andando.
			set_sleep_mode(SLEEP_MODE_IDLE);
			sleep_mode();
			
	}
}