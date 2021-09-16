#define LCD_RS 7
#define LCD_RW 6
#define LCD_EN 5
#include <stm32f103x6.h>
#include "delay.h"
#include <stdint.h>
void lcd_init(void);
void lcd_sendCommand (uint8_t);
void lcd_sendData (uint8_t );
void lcd_putValue (uint8_t );

