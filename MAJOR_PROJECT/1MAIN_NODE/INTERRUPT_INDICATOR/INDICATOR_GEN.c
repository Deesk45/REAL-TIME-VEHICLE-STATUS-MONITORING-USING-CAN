#include<LPC21XX.h>
#include"delay.h"
#include"can.h"
#include"can_defines.h"
#include"types.h"
#include"lcd.h"
#include"lcd_defines.h"
#include"indicator.h"

#define TX_LED 0


volatile u32 blink1 = 0,blink2 =0,eintflg1 = 0 , eintflg2 = 0;

/* ===== LEFT SWITCH INTERRUPT SERVICE ROUTINE =====
   Triggered when SW1 (EINT0) is pressed.
   Sets flag for Main Node to send LEFT indicator CAN command.
   Also controls blinking state logic.
*/
void eint0_isr(void) __irq
{	
	eintflg1 = 1;          // Notify main loop that LEFT interrupt occurred

	blink1 = !blink1;      // Toggle LEFT indicator blink state
	blink2 = 0;            // Disable RIGHT blink when LEFT is active

	EXTINT = 1<<0;         // Clear EINT0 interrupt flag
	VICVectAddr = 0;       // End of ISR (VIC acknowledge)
}


/* ===== RIGHT SWITCH INTERRUPT SERVICE ROUTINE =====
   Triggered when SW2 (EINT2) is pressed.
   Sets flag for Main Node to send RIGHT indicator CAN command.
*/
void eint2_isr(void) __irq
{
	eintflg2 = 1;          // Notify main loop that RIGHT interrupt occurred

	blink2 = !blink2;      // Toggle RIGHT indicator blink state
	blink1 = 0;            // Disable LEFT blink when RIGHT is active

	EXTINT = 1<<2;         // Clear EINT2 interrupt flag
	VICVectAddr = 0;       // End of ISR
}


/* ===== EXTERNAL INTERRUPT CONFIGURATION =====
   Configure EINT0 and EINT2 pins, enable VIC channels,
   assign ISR vector addresses and set edge-trigger mode.
*/
void ext_int_init(void)
{
	PINSEL0 |= EINT0_0_1|
	           EINT2_0_7;        // Configure pins as external interrupt pins
	  
	VICIntEnable = 1 << EINT0_VIC_CHNO|
	               1 << EINT2_VIC_CHNO;   // Enable interrupt channels in VIC

	VICVectCntl0 = (1 << 5)| EINT0_VIC_CHNO;   // Enable vector slot for EINT0
	VICVectAddr0 = (s32) eint0_isr;            // Assign ISR address

	VICVectCntl1 =(1<<5) | EINT2_VIC_CHNO;     // Enable vector slot for EINT2
	VICVectAddr1 = (s32) eint2_isr;            // Assign ISR address

	EXTMODE = 1 << 0|
	          1 << 2;        // Configure interrupts as edge-triggered (falling edge default)
}