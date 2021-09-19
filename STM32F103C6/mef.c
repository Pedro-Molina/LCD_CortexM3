#include "mef.h"


typedef enum {cerrado,abierto,ingresar_contra,denegado} state_name;
	
//constantes

//Variables Privadas
static state_name actual_state;
static uint8_t time_state= 0;
static uint8_t hora=0,min=0,seg=0,cantTiempo = 9;
static uint8_t stringTime[8]= {'1','0',':','0','0',':','0','0'};
static uint8_t clave[4] = {'4','3','2','1'},clavePos=0;

//funciones privadas
void actualizarTiempo(void);
void prepararHora(void);
void processAbierto(void);
void processCerrado(void);
void processDenegado(void);
void processIngresarContra(void);
uint8_t verificarDato(void);
void compararContra(uint8_t);

void MEF_Init(){
	actual_state = cerrado;
}


void MEF_Update(){
	
	if (++cantTiempo == 10){	//actualizo cada 1s
		actualizarTiempo();
		prepararHora();
		cantTiempo =0;
	}
	switch(actual_state){
		case cerrado:
			processCerrado();
		break;
		case abierto:
			processAbierto();
		break;
		case denegado:
			processDenegado();
		break;
		case ingresar_contra:
			processIngresarContra();
		break;
	}
}

void prepararHora(){
	//stringTime[0] = ((hora/10)% 10) + '0';
	//stringTime[3] = ((min/10)% 10) + '0';
	//stringTime[6] = ((seg/10)% 10) + '0';
	//stringTime[1] = ((hora)% 10) + '0';
	//stringTime[4] = ((min)% 10) + '0';
	//stringTime[7] = ((seg)% 10) + '0';
	//imprimir la hora en el led
	lcd_gotoXY(0, 0);
	lcd_string(stringTime, 8);
	
}
void actualizarTiempo(){
	if(++seg == 60)
	{
		seg = 0;
		if(++min == 60)
		{
			min =0;
			if(++hora == 24)
			{
				hora=0;
			}
		}
	}
}


void processCerrado(){
	uint8_t numero = verificarDato();
	if (time_state++ == 0){
		//imprimir cerrado
		lcd_gotoXY(0, 1);
		lcd_string("CERRADO " , 8);
	}
	if (numero){
		actual_state  = ingresar_contra;
		lcd_gotoXY(0, 1);
		lcd_string("        " , 8);
		compararContra(numero);
		time_state = 0;
	}
}

void processAbierto(){
	lcd_gotoXY(0, 1);
	lcd_string("ABIERTO "  , 8);
	GPIOB -> ODR |= 0x0002;
	if(++time_state == 5){
		actual_state = cerrado;
		time_state = 0;
		GPIOB -> ODR &= 0xFFFD;
	}
}

void processDenegado(){
	if(++time_state == 2){
		actual_state = cerrado;
		time_state = 0;
	}
}

void processIngresarContra(){
	uint8_t nuevoNum = verificarDato();
	if (nuevoNum){
		compararContra(nuevoNum);
	}
}

uint8_t verificarDato(){
	uint8_t dato ;
	KEYPAD_Update (&dato);
	if (('0'<=dato) && (dato <= '9')){
		return dato;
	}
	return 0;
}

void compararContra(uint8_t nuevoNum){
	if (nuevoNum == clave[clavePos]){
			//imprimir * en la posicion clavePos
			lcd_gotoXY(clavePos, 1);
			lcd_string ("*",1);
			if (clavePos == 3){
				actual_state = abierto;
				clavePos = 0;
			}else{
				clavePos++;
			}
		}else{
				actual_state = denegado;
				clavePos =0;
				lcd_gotoXY(0, 1);
				lcd_string("DENEGADO" , 8);
			}
}
