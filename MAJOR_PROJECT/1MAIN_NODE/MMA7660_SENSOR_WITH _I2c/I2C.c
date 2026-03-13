#include<LPC21xx.h>
#include"delay.h"
#include"types.h"
#include"defines.h"
#include"i2c_defines.h"
#include"mma7660.h"

void i2c_init(void)
{
	PINSEL0 |= (SCL_0_2 | SDA_0_3);   // Configure P0.2 & P0.3 as I2C SCL and SDA pins

	I2SCLH = DIVIDER;                 // Set I2C clock high time (baud rate setting)
	I2SCLL = DIVIDER;                 // Set I2C clock low time

	I2CONSET = 1 << I2EN_BIT;         // Enable I2C peripheral
}

void i2c_start(void)
{
	I2CONSET = 1 << STA_BIT;          // Generate START condition on I2C bus
	
	while(READBIT(I2CONSET,SI_BIT)==0);  // Wait until START transmitted

	I2CONCLR = 1 << STAC_BIT;         // Clear START flag
}

void i2c_restart(void)
{
	I2CONSET = 1 << STA_BIT;          // Generate REPEATED START condition

	I2CONCLR = 1 << SIC_BIT;          // Clear interrupt flag

	while(READBIT(I2CONSET , SI_BIT) == 0);   // Wait for restart completion

	I2CONCLR = 1 << STAC_BIT;         // Clear START flag
}

void i2c_stop(void)
{
	I2CONSET = 1 << STO_BIT;          // Generate STOP condition ? Release I2C bus

	I2CONCLR = 1 << SIC_BIT;          // Clear interrupt flag
}

void i2c_write(u8 dat)
{
	I2DAT = dat;                      // Load data byte to transmit register

	I2CONCLR = 1 << SIC_BIT;          // Clear interrupt flag ? Start transmission

	while(READBIT(I2CONSET,SI_BIT) == 0);   // Wait until byte transmitted
}

u8 i2c_nack(void)
{
	I2CONCLR  = 1 << SIC_BIT;         // Clear interrupt flag ? Receive next byte

	while(READBIT(I2CONSET ,SI_BIT) == 0);   // Wait until data received

	return I2DAT;                     // Read data without sending ACK (last byte read)
	
}

u8 i2c_mack(void)
{
	I2CONSET = 1 << AA_BIT;           // Enable ACK generation after byte reception

	I2CONCLR = 1 << SIC_BIT;          // Clear interrupt flag

	while(READBIT(I2CONSET,SI_BIT) == 0);   // Wait until data received

	I2CONCLR = 1 << AAC_BIT;          // Clear ACK enable bit

	return I2DAT;                     // Read received byte
}