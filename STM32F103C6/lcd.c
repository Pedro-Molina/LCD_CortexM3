#include "lcd.h"
void lcd_init()
{
   GPIOB->BRR = (1<<LCD_EN); //same as GPIOA->ODR &= ~(1<<LCD_EN); /* LCD_EN = 0 */
   GPIOB->BRR = (1<<LCD_RW); //same as GPIOA->ODR &= ~(1<<LCD_RW); /* LCD_RW = 0 */
   delay_us(3000); /* wait 3ms */
   lcd_sendCommand(0x38); /* init. LCD 2 line,5´7 matrix */
   lcd_sendCommand(0x0E); /* display on, cursor on */
   lcd_sendCommand(0x01); /* clear LCD */
   delay_us(2000); /* wait 2ms */
   lcd_sendCommand(0x06); /* shift cursor right */
}

void lcd_sendCommand (uint8_t cmd)
{
   GPIOB->BRR = (1<<LCD_RS); /* RS = 0 for command */
   lcd_putValue(cmd);
}
void lcd_sendData (uint8_t data)
{
   GPIOB->BSRR = (1<<LCD_RS); /* RS = 1 for data */
   lcd_putValue(data);
}
/**************************
***************************/
void lcd_putValue (uint8_t value)// 8-bit
{
   GPIOA->BRR = 0xFF; /* clear PA0-PA7 */
   GPIOA->BSRR = value&0xFF; /* put value on PA0-PA7 */
   GPIOB->BSRR = (1<<LCD_EN); /* EN = 1 for H-to-L pulse */
   delay_us(2); /* make EN pulse wider */
   GPIOB->BRR = (1<<LCD_EN); /* EN = 0 for H-to-L pulse */
   delay_us(100); /* wait */
}



