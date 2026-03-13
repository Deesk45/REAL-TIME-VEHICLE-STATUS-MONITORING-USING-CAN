#include<LPC21XX.h>
#include"delay.h"
#include"can.h"
#include"can_defines.h"
#include"types.h"
#include"lcd.h"
#include"lcd_defines.h"
#include"indicator.h"
#include"i2c.h"
#include"mma_7660.h"

#define TX_LED 0

CANF rxF;
CANF txF;
extern volatile u32 blink1 ,blink2,eintflg1,eintflg2;
u8 fuel,blocks,i;

int main()
{
  can1_init();        // Initialize CAN controller for node communication
  ext_int_init();     // Enable external interrupts for indicator switches
  i2c_init();         // Initialize I2C for accelerometer communication
  lcd_init();         // Initialize LCD display

  mma7660_init();     // Initialize accelerometer sensor
  WriteToCGRAM();     // Load custom LCD characters (fuel blocks / arrows)
  
	while(1)
	{
		lcd_cmd(GOTO_LINE_1_POS_0);
		lcd_str("------DASHBOARD-----");   // Display dashboard heading

		lcd_cmd(GOTO_LINE_2_POS_0);
		lcd_str("AIR_BAG");               // Static Airbag label

		lcd_cmd(0xD4);
		lcd_str("INDICATOR:");            // Static Indicator label

		lcd_cmd(0x94);
		lcd_str("FUEL: ");                // Static Fuel label

		airbag_trigger();                 // Check accident condition using accelerometer
		
		if(eintflg1 == 1)                 // If LEFT switch interrupt occurred
		{
			eintflg1 = 0;                 // Clear interrupt flag
			left();                       // Send LEFT indicator command via CAN
		}
		else if(eintflg2 == 1)            // If RIGHT switch interrupt occurred
		{
			eintflg2 = 0;
			right();                      // Send RIGHT indicator command via CAN
		}
		
		if(can1_rx(&rxF))                 // Check for received CAN frame
		{
			if(rxF.ID == 2)               // Frame from Fuel Node
			{
				airbag_trigger();         // Update airbag status
				
				fuel = rxF.DATA2;         // Read fuel percentage
				
				if(fuel > 100)            // Limit fuel value
				{
					fuel=100;
				}

				lcd_cmd(0x94);
				lcd_str("FUEL: ");
				
				blocks=fuel/25;           // Calculate number of fuel bar blocks
				
				for(i=0;i<4;i++)          // Draw graphical fuel bar
				{
					if(i<blocks)
					{
						lcd_char(i+3);    // Display block
					}
					else
					{
						lcd_char(' ');    // Clear block
					}
				}
				
				lcd_int(fuel);            // Display numeric fuel %
				lcd_char('%');
			}
		}
				
		delay_ms(200);                    // Small refresh delay


		if(blink1)                        // LEFT indicator blinking logic
		{
			lcd_cmd(0xDe);
			lcd_char(' ');
  		          			
			delay_ms(500);

			lcd_cmd(0xDe);
			lcd_char(1);          
		}
		else
		{
			lcd_cmd(0xDe);
			lcd_char(1);                  // LEFT indicator steady ON
		}

		lcd_cmd(0xE0);
		lcd_char(2);                      // Indicator separator symbol

		if(blink2)                        // RIGHT indicator blinking logic
		{					
			lcd_cmd(0xE2);
			lcd_char(' ');
  		          			
			delay_ms(500);

			lcd_cmd(0xE2);
			lcd_char(0);  
		}
		else
		{
			lcd_cmd(0xE2);
			lcd_char(0);                  // RIGHT indicator steady ON
		}
	}
}
 
void left(void)
{
	IODIR0 |= 1 << TX_LED;     // Configure TX LED pin as output
	
	txF.ID = 1;                // CAN frame ID for Indicator Node
	txF.bfv.RTR = 0;           // Data frame
	txF.DATA1 = 0x01;          // LEFT indicator command
	txF.bfv.DLC = 2;           // Data length

	can1_tx(txF);              // Transmit CAN frame
	IOPIN0 ^= 1 << TX_LED;     // Toggle TX LED to show transmission
}

void right(void)
{
	IODIR0 |= 1 << TX_LED;

	txF.ID = 1;                // CAN frame ID for Indicator Node
	txF.bfv.RTR = 0;
	txF.DATA1 = 0x02;          // RIGHT indicator command
	txF.bfv.DLC = 2;

	can1_tx(txF);              // Transmit CAN frame
	IOPIN0 ^= 1 << TX_LED;
}