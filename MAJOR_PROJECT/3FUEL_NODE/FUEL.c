#include<LPC21xx.h>
#include"type.h"
#include"delay.h"
#include"fuel_defnes.h"

void adc_init(void)
{
	PINSEL1 &=~(0xff << 22);// 27,28,28,30 use as adc 27 - 16 = 11*2 =22->PINSEL1 - 16 - 31
	PINSEL1 |= (AIN0_0_27)|
			   (AIN1_0_28);
			   

 ADCR |= (CLK_DIV << CLK_DIV_BITS)|
 		 (1 << PDN_BIT);
}

void read_adc_value(u32 ch_no ,u32 *dVal ,f32 *eAr)
{
	ADCR &= 0xffffff00; //clear 1st 8 bits fo setting channel

	ADCR |= (1 << ch_no)| //set new channel
			(1 << CONV_START_BITS);	  //start ADC coversion

	delay_us(3);					//2.44_us time required for adc coversion

	while(((ADDR >> DONE_BIT) & 1) == 0); //wait for success convwersi0n

	ADCR &=~ (1 << CONV_START_BITS);  //stop conversion
	
	*dVal = ((ADDR >> RESULT_BITS) & 1023);	// calculate digital values
	
	*eAr = (*dVal * (3.3/1023));			// calculate analog equivalnt values
}
