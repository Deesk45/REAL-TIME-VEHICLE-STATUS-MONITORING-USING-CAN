#include<LPC21XX.h>
#include"types.h"
#include"delay.h"
#include"can_defines.h"
#include"can.h"

void can1_init(void)		 
{
	PINSEL1 |= (RD1_PIN_0_25);     // Configure CAN RX/TX pins function

	C1MOD |= 1 << RM_BIT;          // Enter CAN Reset Mode for safe configuration
	
	AFMR &= ~(1 << ACCOFF_BIT);    // Enable Acceptance Filter
	AFMR |= 1 << ACCBP_BIT;        // Bypass filter ? Accept all CAN frames

	C1BTR = BTR_LVAL;              // Set CAN baud rate (bit timing configuration)

	C1MOD &= ~(1 << RM_BIT);	     // Exit Reset Mode ? Start CAN operation
}

void can1_tx(CANF txF)
{
	u32 timeout = 50000;

	/* Wait until Transmit Buffer-1 becomes free */
	while(((C1GSR >> TBS1_BIT) & 1) == 0)
	{
		if(timeout-- == 0)          // Timeout protection to avoid infinite wait
			break;
	}

	C1TID1 = txF.ID;               // Load CAN Identifier into TX register

	/* Configure Frame Info ? RTR bit + Data Length Code */
	C1TFI1 = ((txF.bfv.RTR << RTR_BIT) | (txF.bfv.DLC << DLC_BIT));

	if(txF.bfv.RTR != 1)           // If Data Frame (not Remote Frame)
	{
		C1TDA1 = txF.DATA1;        // Load first data word
		C1TDB1 = txF.DATA2;        // Load second data word
	}

	C1CMR |= ((1 << STB1_BIT) | (1 << TR_BIT));   // Select TX buffer and start transmission

	timeout = 50000;

	/* Wait for Transmission Complete Status */
	while(((C1GSR >> TCS1_BIT) & 1) == 0)
	{
		if(timeout-- == 0)          // Timeout safety
			break;
	}
}

u8 can1_rx(CANF *rxF)
{
	/* Check Receive Buffer Status ? Frame Available or Not */
	if(((C1GSR >> RBS_BIT) & 1) == 0)
	{
		return 0;                   // No frame received
	}

	rxF->ID = C1RID;               // Read received CAN Identifier

	rxF->bfv.RTR = ((C1RFS >> RTR_BIT) & 1);   // Read Remote Transmission Request bit
	
	rxF->bfv.DLC = ((C1RFS >> DLC_BIT) & 15);  // Read Data Length Code
	
	
	if(rxF->bfv.RTR == 0)          // If Data Frame
	{
		rxF->DATA1 = C1RDA;        // Read first data word
		rxF->DATA2 = C1RDB;        // Read second data word
	}

	C1CMR |= (1 << RRB_BIT);       // Release Receive Buffer ? Ready for next frame

	return 1;                      // Frame successfully received
}