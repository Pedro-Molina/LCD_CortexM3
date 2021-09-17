#include "teclado.h"
#include <stdint.h>

static const uint8_t teclado[4][4] = {
	{'7','8','9','A'},
	{'4','5','6','B'},
	{'1','2','3','C'},
	{'*','0','#','D'}
};

void tecladoInit(){
	//pongo las filas como salida y columnas como entrada
	//pongo los bits de salida en 0 y los de entrada en pull-up 1
	
		GPIOB->CRL = 0x88882222;
}



uint8_t KEYPAD_Scan(uint8_t *key){

	uint8_t i;
	const uint16_t aux[4]={0x7F00,0xBF00,0xDF00,0xEF00}; //{F1,F2,F3,F4} -> aux[i] implica 0 en Fila i
	uint8_t result = 0, column;
	int fila=-1;
	for(i=0; i<4; i++){		//busco si alguna columna esta en 0
		if ((GPIOB->IDR&(1<<i)) == 0){
			column = i;
			result = 1;
			break;
		}
	}
	
	if (result){
		for(i=0; i<4 ; i++){
			GPIOB->ODR = aux[i];
			if ((GPIOB->IDR&(1<<column)) == 0){	//miro si la fila coincide con la columna que encontre
				fila = i;
				break;
			}
		}
		*key = teclado[column][fila];
	}
	//vuelvo a poner PORTD como estaba antes
	GPIOB->ODR = 0x0F00;
	return result;
}


uint8_t KEYPAD_Update (uint8_t *pkey)
{
	static uint8_t Old_key;
	uint8_t Key; 
	static int Last_valid_key=0xFF; // no hay tecla presionada
	if(!KEYPAD_Scan(&Key)) {
		Old_key=0xFF; // no hay tecla presionada
		Last_valid_key=0xFF;
		return 0;
	}
	if(Key==Old_key) { //2da verificacin
		if(Key!=Last_valid_key){ //evita mltiple deteccin
			*pkey=Key;
			Last_valid_key = Key;
			return 1;
		}
	}
	Old_key=Key; //1era verificacin
	return 0;
}



