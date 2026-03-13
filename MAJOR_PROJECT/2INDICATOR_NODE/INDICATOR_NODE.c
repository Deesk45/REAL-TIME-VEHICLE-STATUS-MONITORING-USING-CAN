#include<LPC21XX.h>
#include"delay.h"
#include"can.h"
//#include"can_defines.h"
#include"types.h"
#include"indicator.h"

typedef enum
{
    MODE_OFF = 0,
    MODE_LEFT,
    MODE_RIGHT
}LED_MODE;

LED_MODE current_mode = MODE_OFF;

#define LED 18

	CANF rxF;

int main()
{

	can1_init();
   
	 while(1)
{
    if(can1_rx(&rxF))
    {	IOPIN0 ^= 1 << LED;
        if(rxF.ID == 1)
        {
            if(rxF.DATA1 == 0x01)
            {
                if(current_mode == MODE_LEFT)
                    current_mode = MODE_OFF;
                else
                    current_mode = MODE_LEFT;
            }
            else if(rxF.DATA1 == 0x02)
            {
                if(current_mode == MODE_RIGHT)
                    current_mode = MODE_OFF;
                else
                    current_mode = MODE_RIGHT;
            }
        }
    }

    switch(current_mode)
    {
        case MODE_LEFT:
            led_left_step();
            break;

        case MODE_RIGHT:
            led_right_step();
            break;

        case MODE_OFF:
            led_off();
            break;
    }
}
	}
