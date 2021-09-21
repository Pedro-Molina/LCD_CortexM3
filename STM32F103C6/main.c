/* Main.c file generated by New Project wizard
 *
 * Created:   mi�. sep. 15 2021
 * Processor: STM32F103C6
 * Compiler:  Keil for ARM
 */

#include <stm32f103x6.h>
#include "lcd.h"
#include <stdint.h>
#include "delay.h"
#include "teclado.h"
#include "mef.h"
#include "timer.h"

int main (void)
 {  
	RCC->APB2ENR |= 0xFC;     /* Enable clocks for GPIO ports */
	GPIOA->CRL = 0x33333333;/* PA0-PA7 as outputs */
	GPIOA->CRH = 0x44444333;
	GPIOB->CRL = 0x44444434;
	tecladoInit();
	lcd_init();
	MEF_Init();
	timer_init();
	while (1) { 
		if (timer_getFlag()){
			MEF_Update();
			timer_resetFlag();
		}
    }
}   

