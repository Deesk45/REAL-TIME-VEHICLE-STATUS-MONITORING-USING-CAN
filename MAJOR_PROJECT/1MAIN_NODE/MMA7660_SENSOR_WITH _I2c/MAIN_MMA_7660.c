#include<LPC21xx.h>
#include"delay.h"
#include "mma_7660.h"
#include"i2c.h"
#include"lcd.h"
#include"lcd_defines.h"


#define GLED 21
#define RLED 22


    s8 x,y,z;

void airbag_trigger()
{

    IODIR0 |= (1<<GLED) | (1<<RLED);

        x = mma7660_get_x();
		y = mma7660_get_y();
		z = mma7660_get_z();
	   /*
		lcd_cmd(GOTO_LINE_1_POS_0);
		lcd_int(x);
		
		lcd_str("   ");
		lcd_cmd(GOTO_LINE_1_POS_0 +4);
		lcd_int(y);
		
		lcd_str("   ");
		lcd_cmd(GOTO_LINE_1_POS_0 + 8);
		lcd_int(z);
		lcd_str("   ");
		 */

        if(((x <= -25 ||x >= 25) ||(y <= -25 ||y >= 25) || (z <= -25 ||z >= 25)))
        {
            IOCLR0 = 1<<GLED;
            IOCLR0 = 1<<RLED;
	//		lcd_cmd(GOTO_LINE_2_POS_0);
	//		lcd_str("AIR_BAG");
		//	lcd_str("       ");
		lcd_cmd(GOTO_LINE_2_POS_0 +10);
			lcd_char(7);
			delay_ms(800);
			IOSET0 = 1<<GLED;
            IOSET0 = 1<<RLED;
						lcd_cmd(GOTO_LINE_2_POS_0 +9);
			lcd_str("     ");


			
			//lcd_cmd(GOTO_LINE_2_POS_0 + 5);
			//lcd_int(x);
        }
      /*  else if(y <= -25 ||y >= 25)
        {
            IOSET1 = 1<<RLED;
            IOCLR1 = 1<<GLED;
			 //lcd_cmd(GOTO_LINE_1_POS_0 + 5);
			 //lcd_int(x);
        }
        else
        {
            IOCLR1 = (1<<GLED) | (1<<RLED);
        } */
}
