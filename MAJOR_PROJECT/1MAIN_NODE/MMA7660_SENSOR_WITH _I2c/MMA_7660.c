#include <LPC21xx.h>
#include "i2c.h"
#include "delay.h"
#include "mma_7660.h"

void mma7660_write(u8 reg, u8 data)
{
    i2c_start();
    i2c_write(MMA7660_SA);     // Write address
    i2c_write(reg);            // Register
    i2c_write(data);           // Data
    i2c_stop();
    delay_ms(2);
}

u8 mma7660_read(u8 reg)
{
    u8 data;

    i2c_start();
    i2c_write(MMA7660_SA);     // Write mode
    i2c_write(reg);

    i2c_restart();
    i2c_write(MMA7660_SA_R);   // Read mode

    data = i2c_nack();         // Single byte read

    i2c_stop();
    delay_ms(2);

    return data;
}

void mma7660_init(void)
{
    delay_ms(10);

    // Put device in standby
    mma7660_write(MMA_MODE, 0x00);
    delay_ms(10);

    // Set Sample Rate = 120 samples/sec
    mma7660_write(MMA_SR, 0x00);

    // Activate device (MODE = 0x01)
    mma7660_write(MMA_MODE, 0x01);
    delay_ms(10);
}

s8 convert_data(u8 val)
{
    val &= 0x3F;               // 6-bit data

    if(val & 0x20)             // Negative number
        val |= 0xC0;

    return (s8)val;
}

s8 mma7660_get_x(void)
{
    return convert_data(mma7660_read(MMA_XOUT));
}

s8 mma7660_get_y(void)
{
#include <LPC21xx.H>
    return convert_data(mma7660_read(MMA_YOUT));
}

s8 mma7660_get_z(void)
{
    return convert_data(mma7660_read(MMA_ZOUT));
}
