#ifndef pwmPool_h
#define pwmPool_h

#define offPort(port) port &=0x00;
#define PwmPort PORTB
uint8_t pwmOut[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
		

//**********************************************************************

void setHigh(uint8_t port){
		PwmPort^=pwmOut[port];
		
}

void setLow(void){
	offPort(PwmPort);
}

void pwmPool(uint8_t maxChannels){

	
	switch(maxChannels){
		case 1:
		DDRB=0x01;			
		break;
		case 2:
		DDRB=0x03;				// 2 pines como salida en el puerto B
		break;
		case 3:
		DDRB=0x07;				// 3 pines como salida en el puerto B
		break;
		case 4:
		DDRB=0x0F;				// 4 pines como salida en el puerto B
		break;
		case 5:
		DDRB=0x1F;				// 5 pines como salida en el puerto B
		break;
		case 6:
		DDRB=0x3F;				// 6 pines como salida en el puerto B
		break;
		case 7:
		DDRB=0x7F;				// 5 pines como salida en el puerto B
		break;
		case 8:
		DDRB=0xFF;				// 6 pines como salida en el puerto B
		break;
		
	}
	
	offPort(PwmPort);
	
}
#endif
