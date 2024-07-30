/*
 * API_debounce.c
 *
 *  Created on: Jul 12, 2024
 *      Author: rpalma
 */


#include "API_debounce.h"
#include "API_delay.h"

// defincion de variables que seran utilizadas en la libreria
static debounceState_t statePulse = BUTTON_UP;
static delay_t delayLed;
bool_t keyState=0;

// Funcion que devuelve si la boton se encuentra encendido
bool_t readKey(void){

	if(keyState==true){
		keyState=0;
		return true;
	}
	return false;

}

// Funcion de incializacion
void debounceFSM_init(){ // debe cargar el estado inicial
	statePulse = BUTTON_UP;
}

// Funcion de cambio de estado y implementacion de maquina de estado finitos
void debounceFSM_update(){ // debe leer las entradas, resolver la logica de entrada para la maquina de estados de la solcitud de rebote

	switch(statePulse){
			case BUTTON_UP:
				if(BSP_PB_GetState(BUTTON_USER)){
					statePulse=BUTTON_FALLING;
					delayInit(&delayLed,DELAY_TIME);
				}
				break;
			case BUTTON_FALLING:
				// Si se presiono el boton
				if(delayRead(&delayLed)){
					if(!BSP_PB_GetState(BUTTON_USER))
						statePulse=BUTTON_UP;
					else {
						 buttonPressed();
						 statePulse=BUTTON_DOWN;
					}
				}
				break;
			case BUTTON_DOWN:
				if(!BSP_PB_GetState(BUTTON_USER)){
					statePulse=BUTTON_RAISING;
					delayInit(&delayLed,DELAY_TIME);
				}
				break;
			case BUTTON_RAISING:
				if(delayRead(&delayLed)){
					if(BSP_PB_GetState(BUTTON_USER))
						statePulse=BUTTON_DOWN;
					else {
						buttonReleased();
						statePulse=BUTTON_UP;
					}
				}
				break;
			default:
				debounceFSM_init();
				break;
		}

}

//
void buttonPressed(){// debe invertir el estado del boton
	keyState = 1;
}
void buttonReleased(){ // debe invertir el estado del boton
	keyState = 0;
}

