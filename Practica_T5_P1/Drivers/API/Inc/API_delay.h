/*
 * API_delay.h
 *
 *  Created on: Jul 4, 2024
 *      Author: rpalma
 */

/*
 * Definicion de la Libreria
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

/*
 * Incluir las librerias necesarias para los tipos especificos
 */

#include <stdbool.h>
#include <stdint.h>


// Definicion de estructura y tipos iniciales de nuestra libreria
typedef uint32_t tick_t;
typedef bool bool_t;
typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;


// Definicion Funciones y Procedimiento de la Libreria
void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );


#endif /* API_INC_API_DELAY_H_ */
