#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)

#define I2C_SPEED 100000

#define DIVIDER  ((PCLK/I2C_SPEED)/2)

//CONFIG I2CONSET
#define AA_BIT   2
#define SI_BIT   3
#define STO_BIT  4
#define STA_BIT  5
#define I2EN_BIT 6

//CONFIG I2CONCLR
#define AAC_BIT   2
#define SIC_BIT   3
//#define STOC_BIT  4
#define STAC_BIT  5
#define I2ENC_BIT 6

#define SCL_0_2 0x00000010
#define SDA_0_3 0x00000040

