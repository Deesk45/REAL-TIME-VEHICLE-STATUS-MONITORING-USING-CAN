#ifndef _MMA7660_H_
#define _MMA7660_H_

#include "types.h"

#define MMA7660_ADDR  0x4C

void mma7660_init(void);
void mma7660_read_xyz(s8 *x, s8 *y, s8 *z);

#endif
