#ifndef TECLADO_H_
#define TECLADO_H_

#include <stdint.h>
#include <stm32f103x6.h>
//#include "stm32f10x.h"

uint8_t KEYPAD_Update (uint8_t *);
void tecladoInit(void);

#endif /* TECLADO_H_ */

