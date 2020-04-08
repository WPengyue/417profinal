#include <stdint.h>

#define LCD_CM_ENA 0x00210002 //
#define LCD_CM_DIS 0x00230000 //
#define LCD_DM_ENA 0x00200003 //
#define LCD_DM_DIS 0x00220001 //

extern uint16_t Line_1;
void LCD_init(void);
void Cmd2LCD(uint8_t data);
void Data2LCD(uint8_t data);
void String2LCD(char *);
void Go2Line_2(void);
void lcd_IO_init (void);
uint16_t Hex2Asc(uint8_t);
uint16_t Hex2Dec(uint16_t);