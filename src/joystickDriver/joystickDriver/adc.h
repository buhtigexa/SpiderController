#ifndef adc_h
#define adc_h
#include "index.h"


#if F_CPU == 16000000UL
#define adjustAdc (uint16_t) (3000 -((1.95)*ADC))
#else
#define adjustAdc (uint16_t) (1500 -((0.97)*ADC))
#endif

typedef struct {
	
	uint8_t  prescaler;		//prescaler seleccionado
	Tindex *idx;		
	
} TAdc;

TAdc adc;

void setUpAdc(uint8_t channels, uint8_t voltage, uint8_t enable){


	adc.idx=index();	
	
	switch(F_CPU)	{
		case 1000000:
					adc.prescaler =3; //125 khz    
					break;
		case 8000000:
					adc.prescaler= 6; // 125 khz
					break;
		case 16000000:
					adc.prescaler = 7; //125 khz
					break;
		default: 
				adc.prescaler = 6;		
		}
	
	switch(channels){
		// channels as input
		case 1:
			DDRC=0xFE;
			break;
		case 2:
			DDRC=0xFC;
			break;
		case 3:
			DDRC=0xF8;	//Reset como entrada, sin embargo depende de RSTDISBL. Si RSTDISBL está programado, PC6 será I/O pin.
			break;
		case 4:
			DDRC=0xF0;
			break;
		case 5:
			DDRC=0xE0;
			break;
		case 6:
			DDRC=0xC0;
			break;
		case 7:
			DDRC =0x80;
			break;
		case 8:
			DDRC=0x00;
			break;
	}
	
	adc.prescaler = 0x07 & adc.prescaler;				  //
	ADMUX  = voltage;								 // external reference voltage, and result to right.
	ADCSRA = enable|adc.prescaler;					// enable ADC, enable Ints and set prescaler.
	ADCSRA |= (1<<ADSC);
	

}

inline void nextMux(uint8_t channel){

	ADMUX &=0xF0;
	ADMUX |=channel;

	
}


#endif