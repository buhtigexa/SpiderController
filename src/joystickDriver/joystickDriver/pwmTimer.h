
#ifndef pwmTimer_h
#define pwmTimer_h

#include "index.h"
#include "pwmPool.h"

#define CompareReg1Andoverflow 0x14

typedef struct{

	
	Tindex *idx;
	uint8_t  prescaler;
	uint8_t i,j;
	uint16_t pwmPeriod;

}PwmTimer;

PwmTimer timer;
//*************************************************************************

void setUpTimer(void){

	timer.j=0;
	timer.idx=index();
	timer.pwmPeriod=0x09C3;
	
	switch(F_CPU){
		
		case 1000000 : timer.prescaler=1;
						break;	
		case 8000000 : timer.prescaler = 2;			//prescaler x 8
						break;
		case 16000000: 
						timer.prescaler=2;
						timer.pwmPeriod=0x1386;
						break;
		default: timer.prescaler=2;
				
				
				  				 // Por defecto,asumimos clock frec 8Mhz
	
	}
	
	TCNT1=0xFFFF;
	OCR1A=0xFFF0;
	ICR1 =timer.pwmPeriod;
	TIMSK =CompareReg1Andoverflow;
	TCCR1A=0x02;
	TCCR1B=0x18 | timer.prescaler;
	
}


ISR (TIMER1_OVF_vect){

	
	setLow();
	timer.i=timer.j;
	timer.j=adc.idx->current;
	while ((ADCSRA & ADSC)==TRUE);
	OCR1A=adjustAdc;
	next(adc.idx);
	nextMux(adc.idx->current);
		
	
	
}

ISR(TIMER1_COMPA_vect){
	
	setHigh(timer.i);

}

#endif
