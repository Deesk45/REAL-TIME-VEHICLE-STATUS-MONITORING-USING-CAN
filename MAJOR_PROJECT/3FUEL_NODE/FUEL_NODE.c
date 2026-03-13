#include<LPC21XX.h>
#include"delay.h"
#include"can.h"
#include"can_defines.h"
#include"types.h"
//#include"lcd.h"
//#include"lcd_defines.h"
//#include"indicator.h"
#include"fuel.h"

#define TX_LED 0

u32	dVal;
f32	eAr;
int percentage;

int main()
{
	CANF txF;

	IODIR0 |= 1 << TX_LED;
	
	can1_init();
    adc_init();

	txF.ID = 2;
	txF.bfv.RTR = 0;
//	txF.DATA1 = 0;
	//txF.DATA2 = 0;
	txF.bfv.DLC = 8;
  
	
	while(1)
	{
		read_adc_value(1,&dVal,&eAr);
		
		percentage = (dVal * 100) / 1023;
		
	
	  	txF.DATA2 = percentage;

		can1_tx(txF);
		IOPIN0 ^= 1 << TX_LED;
		delay_ms(300);
	}
}
