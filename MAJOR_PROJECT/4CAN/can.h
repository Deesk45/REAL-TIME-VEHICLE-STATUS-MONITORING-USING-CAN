#include"types.h"

typedef struct can_frame
{
	u32 ID;

	struct bitfield
	{
		u32 RTR : 1;
		u32 DLC : 4;
		u32 FF  : 1;
	}bfv;

 	u32 DATA1,DATA2;

}CANF;

void can1_init(void);
void can1_tx(CANF txF);
u8 can1_rx(CANF *rxF);
void left(void);
void right(void);
