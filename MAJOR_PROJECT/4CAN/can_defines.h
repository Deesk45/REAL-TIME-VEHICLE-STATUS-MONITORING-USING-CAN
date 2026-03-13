#include"types.h"

//#define TD1_PIN
//#define PIN_FUN2 1
#define RD1_PIN_0_25 0x15440000

#define PCLK 15000000

#define	BIT_RATE 125000

#define QUANTA 15

#define BRP (PCLK/(BIT_RATE * QUANTA))

#define SAMPLE_POINT (0.7 * QUANTA)

#define TSEG1 ((u32)SAMPLE_POINT -1)

#define TSEG2 (QUANTA - (1 + TSEG1))

#define SJW ((TSEG2 >= 5)?4:(TSEG2-1))

#define SAM_BIT 0

#define BTR_LVAL ((SAM_BIT << 23)|((TSEG2 - 1) << 20)|((TSEG1 - 1)<< 16)|((SJW-1) << 14)|(BRP-1))

//C1MOD REGISTER 

#define RM_BIT 0

//C1CMR REGISTER

#define	TR_BIT   0 
#define RRB_BIT	 2
#define	STB1_BIT 5

//C1GSR REGISTER

#define RBS_BIT   0
#define TBS1_BIT  2
#define TCS1_BIT  3

//C1RFS REGISTER

#define FF_BIT  31
#define RTR_BIT 30
#define DLC_BIT	16

//AFMR REGISTER

#define ACCOFF_BIT 0
#define ACCBP_BIT  1


#define EINT0_0_1 0x0000000c
#define EINT0_VIC_CHNO 14
//#define	EINT0_STATUS_LED 16
 
#define EINT2_0_7 0x0000c000
#define EINT2_VIC_CHNO 16
///#define	EINT1_STATUS_LED 17


#define L_LED 0
#define R_LED 0
