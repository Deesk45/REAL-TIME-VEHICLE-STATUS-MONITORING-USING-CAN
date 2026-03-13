#include"types.h"

void eint0_isr(void) __irq;
void eint2_isr(void) __irq;
void ext_int_init(void);

void led_left_step(void);
void led_right_step(void);
void led_off(void);

void airbag_trigger(void);
