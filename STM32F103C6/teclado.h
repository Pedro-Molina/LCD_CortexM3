#ifndef TECLADO_H_
#define TECLADO_H_

#include <stdint.h>
#include <stm32f103x6.h>
//#include "stm32f10x.h"

   #define KEYPAD_PORT         GPIOB->CRH
    #define KEYPAD_PIN_IN     GPIOB->IDR            //Input Data Register
    #define KEYPAD_PIN_OUT     GPIOB->ODR        //Output Data Register
    
    #define KEYPAD_PORT0 (1<<8)    
    #define KEYPAD_PORT1 (1<<9)
    #define KEYPAD_PORT2 (1<<10)
    #define KEYPAD_PORT3 (1<<11)
    #define KEYPAD_PORT4 (1<<12)
    #define KEYPAD_PORT5 (1<<13)
    #define KEYPAD_PORT6 (1<<14)
    #define KEYPAD_PORT7 (1<<15)

uint8_t KEYPAD_Update (uint8_t *);
uint8_t KEYPAD_Scan (uint8_t *);
void tecladoInit(void);

#endif /* TECLADO_H_ */

