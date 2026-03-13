#include"type.h"

void lcd_init(void);
void lcd_disp(u8);
void lcd_cmd(u8);
void lcd_str(s8*);
void lcd_char(s8);
void lcd_int(s32);
void lcd_f32(f32,u32);
void WriteToCGRAM(void);
void lcd_hex(u8 data);
void lcd_hex_data(u32 value);
