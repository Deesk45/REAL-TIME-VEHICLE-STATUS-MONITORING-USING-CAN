#include<LPC21xx.h>
#include"delay.h"
#include"type.h"
#include"defines.h"
#include"lcd.h"
#include"lcd_defines.h"

void lcd_init(void)
{
  IODIR0|=(0xff << LCD_DATA)|(1<<RS)|(1<<RW)|(1<<EN);   // Configure LCD data + control pins as output

	delay_ms(20);          // LCD power ON delay
	
	lcd_cmd(0x30);         // Wake-up command sequence (8-bit mode init)
	delay_ms(8);
	lcd_cmd(0x30);
	delay_ms(1);
	lcd_cmd(0x30);
	delay_ms(1);

	lcd_cmd(0x38);         // Function set ? 8bit, 2 line, 5x7 matrix
	lcd_cmd(0x10);         // Cursor move setting
	lcd_cmd(0x01);         // Clear display
	lcd_cmd(0x06);         // Entry mode ? auto cursor increment
	lcd_cmd(0x0c);         // Display ON, cursor OFF
	lcd_cmd(GOTO_LINE_1_POS_0);   // Set cursor to first line start
}

void lcd_disp(u8 val)
{
	IOCLR0=1<<RW;                 // Select WRITE operation
	WRITEBYTE(IOPIN0,LCD_DATA,val);  // Put data/command on LCD data bus

	IOSET0=1<<EN;                 // Generate Enable pulse
	delay_us(2);
	IOCLR0=1<<EN;

	delay_ms(2);                  // Command execution delay
}

void lcd_cmd(u8 cmd)
{
	IOCLR0=1<<RS;                 // RS=0 ? Instruction Register select
	lcd_disp(cmd);                // Send command to LCD
}

void lcd_char(s8 dat)
{
	IOSET0=1<<RS;                 // RS=1 ? Data Register select
	lcd_disp(dat);                // Send character data
}

void lcd_str(s8 *ptr)
{
	while(*ptr)                   // Print string until NULL
	{
		lcd_char(*ptr++);
	}
}

void lcd_int(s32 num)
{
	s8 a[10],i=0;

	if(num==0)
		lcd_char(0+48);          // Display '0'
	else
	{
		if(num<0)                // Handle negative numbers
		{
			lcd_char('-');
			num=-num;
		}

		while(num)               // Convert integer to ASCII digits
		{
			a[i++]=num%10+48;
			num/=10;
		}

		--i;
		for(;i>=0;i--)          // Print digits in correct order
			lcd_char(a[i]);
 }
}

void lcd_f32(f32 num, u32 nDP)
{
	s32 n,i;

	if(num < 0 )                 // Handle negative float
	{
		lcd_char('-');
		num = -num;
	}

	n = num;
	lcd_int(n);                  // Print integer part
	lcd_char('.');               // Decimal point

	for(i = 0;i <= nDP ; i++)    // Print fractional digits
	{
		num = (num - n) * 10;
		n=num;
		lcd_char(n + 48);
	}
}

void WriteToCGRAM(void)
{
	s8 i;

	/* Custom patterns used in project:
	   Arrow symbols ? Indicator animation
	   Block symbols ? Fuel level graphical bar
	*/
	s8	a[] = {0x10,0x1c,0x1E,0x1f,0x1E,0x1C,0x10,0x00};
	s8	b[] = {0x01,0x07,0x0f,0x1f,0x0f,0x07,0x01,0x00};		
	s8	c[] = {0x00,0x04,0x0e,0x1f,0x0e,0x04,0x00,0x00};
	s8  d[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x00};
	s8	e[] = {0x00,0x00,0x00,0x00,0x1f,0x1f,0x1f,0x00};
	s8	f[] = {0x00,0x00,0x1f,0x1f,0x1f,0x1f,0x1f,0x00};
	s8	g[] = {0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x00};
	s8	h[] = {0x1f,0x11,0x11,0x11,0x11,0x11,0x1f,0x00};

	lcd_cmd(0x40);              // Set CGRAM address to start loading patterns

	for(i=0;i<8;i++) lcd_char(a[i]);
	for(i=0;i<8;i++) lcd_char(b[i]);
	for(i=0;i<8;i++) lcd_char(c[i]);
	for(i=0;i<8;i++) lcd_char(d[i]);
	for(i=0;i<8;i++) lcd_char(e[i]);
	for(i=0;i<8;i++) lcd_char(f[i]);
	for(i=0;i<8;i++) lcd_char(g[i]);
	for(i=0;i<8;i++) lcd_char(h[i]);
}

void lcd_hex(u8 data)
{
	u8 up , low;

	up = (data >> 4) & 0x0f;     // Extract upper nibble
	low = data & 0x0f;           // Extract lower nibble
	
	if(up < 10)
		lcd_disp(up + '0');      // Display numeric hex digit
	else
		lcd_disp(up - 10 + 'A'); // Display alphabetic hex digit
	
	if(low < 10)
		lcd_disp(low + '0');
	else
		lcd_disp(low - 10 + 'A');
}

void lcd_hex_data(u32 value)
{
	lcd_str("0x");               // Hex prefix
	
	lcd_hex((value >> 24) & 0xff);   // Display MSB byte
	lcd_hex((value >> 16) & 0xff);
	lcd_hex((value >> 8) & 0xff);
	lcd_hex(value & 0xff);           // Display LSB byte
}