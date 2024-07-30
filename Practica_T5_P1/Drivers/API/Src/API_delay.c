/*
 * API_delay.c
 *
 *  Created on: Jul 4, 2024
 *      Author: rpalma
 */

#include "API_delay.h"
#include "stm32f4xx_hal.h"  		/* <- HAL include */


/*
 * Funcion:   delayInit
 * El proposito es inicializa un delay de inicio para cada uno de los componentes
 * @delay_t la estructura que almacena el delay
 * @tick_t la duracion del elemento
 * return none
 */
void delayInit( delay_t * delay, tick_t duration ){
	if(delay == NULL) return;
	delay->startTime=HAL_GetTick();
	delay->duration=duration;
	delay->running=false;

}


/*
 * Funcion:   delayRead
 * El proposito es la funcion lectura y establecimiento en base a las especificaciones
 * @delay_t la estructura que almacena el delay
 * return boolean
 */
bool_t delayRead( delay_t * delay ){

  if(delay == NULL) return false;
  if(!delay->running) {
     delay->startTime = HAL_GetTick();
     delay->running = true;
  }
  else if(HAL_GetTick() - delay->startTime >= delay->duration) {
     delay->running = false;
     return true;
  }
  return false;

}


/*
 * Funcion:   delayWrite
 * El proposito es la funcion escritura y establecimiento en base a las especificaciones
 * @delay_t la estructura que almacena el delay
 * @tick_t la duracion del elemento
 *
 */
void delayWrite( delay_t * delay, tick_t duration ){
  if(delay == NULL) return;
  delay->duration=duration;
}


