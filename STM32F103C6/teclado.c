#include "teclado.h"
#include <stdint.h>

static const uint8_t teclas[4][4] = {
	{'*','0','#','D'},
	{'1','2','3','C'},
	{'4','5','6','B'},
	{'7','8','9','A'}
	
};

void tecladoInit(){
	//pongo las filas como salida y columnas como entrada
	//pongo los bits de salida en 0 y los de entrada en pull-up 1
	GPIOB->CRH= 0x33338888;  
}



static uint8_t KEYPAD_Scan(uint8_t *key)
{
    const uint16_t aux[4]={0x7F00,0xBF00,0xDF00,0xEF00}; //{F1,F2,F3,F4} -> aux[i] implica 0 en Fila i
    uint8_t i;
    
    uint32_t temp =  GPIOB->ODR ;        //Guardo el estado anterior 
              /* PB8-PB11 as Outputs (FILAS) && PB12-PB15 as Inputs (COLUMNAS)*/
    
    //Barrido
    for(i=0;i<4;i++){
        GPIOB->ODR    = aux[i];                 //va poniendo un cero en cada fila para poder leerla
           
        if(~GPIOB->IDR & (1<<8)){        //Leo la entrada correspondiente del Keypad y hago un AND bit a bit con el PIN que me interesa del puerto.
            //Si entra al IF, Existe un 1 logico en el PIN deseado
            *key=teclas[i][0];
            return 1;
        }
        if(~GPIOB->IDR & (1<<9)){
            *key=teclas[i][1];
            return 1;
        }
        if(~GPIOB->IDR & (1<<10)){
            *key=teclas[i][2];
            return 1;
        }
        if(~GPIOB->IDR & (1<<11)){
            *key=teclas[i][3];
            return 1;
        }
    }
    
    GPIOB->ODR    = temp;
    return 0;
}

uint8_t KEYPAD_Update (uint8_t *pkey)
{
	static uint8_t Old_key;
	static uint8_t Key; 
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



