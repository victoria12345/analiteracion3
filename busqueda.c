/**
 *
 * Descripcion: Implementacion funciones para busqueda
 *
 * Fichero: busqueda.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 11-11-2016
 *
 */

#include "busqueda.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

/**
 *  Funciones de geracion de claves
 *
 *  Descripcion: Recibe el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               iran de 1 a max. Las claves se devuelven en
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 */

/**
 *  Funcion: generador_claves_uniforme
 *               Esta fucnion genera todas las claves de 1 a max de forma
 *               secuencial. Si n_claves==max entonces se generan cada clave
 *               una unica vez.
 */
void generador_claves_uniforme(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) claves[i] = 1 + (i % max);

  return;
}

/**
 *  Funcion: generador_claves_potencial
 *               Esta funcion genera siguiendo una distribucion aproximadamente
 *               potencial. Siendo los valores mas pequenos mucho mas probables
 *               que los mas grandes. El valor 1 tiene una probabilidad del 50%,
 *               el dos del 17%, el tres el 9%, etc.
 */
void generador_claves_potencial(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) {
    claves[i] = (1+max) / (1 + max*((double)rand()/RAND_MAX));
  }

  return;
}

PDICC ini_diccionario (int tamanio, char orden){
  PDICC pdicc = NULL;

  pdicc = (PDICC)malloc(sizeof(pdicc[0]));

  if(pdicc == NULL)
    return NULL;

  pdicc->tabla = (int*)malloc(sizeof(pdicc->tabla[0]) * tamanio);

  if(pdicc->tabla == NULL)
    return NULL;

  pdicc->tamanio = tamanio;

  pdicc->orden = orden;

  pdicc->n_datos = 0;



  return pdicc;
}

void libera_diccionario(PDICC pdicc){
  if(pdicc == NULL)
    return;

  if(pdicc->tabla == NULL){
    free(pdicc);
    return;
  }

  free(pdicc->tabla);
  free(pdicc);
}

int inserta_diccionario(PDICC pdicc, int clave){
  int ob = 0;
  int i = 0;

  i = 0;

  pdicc->tabla[pdicc->n_datos] = clave;
  pdicc->n_datos ++;

  if(pdicc->orden == 1){

    i = pdicc->n_datos - 1;

    if(i > 0){
      while (pdicc->tabla[i] < pdicc->tabla[i - 1]){
        swap(&pdicc->tabla[i], &pdicc->tabla[i -1]);
        i--;
        if(i == 0)
        break;
      }
    }
}

  return ob;
}

int insercion_masiva_diccionario (PDICC pdicc,int *claves, int n_claves){
  int i;
  int ob = 0;

  for(i = 0; i < n_claves; i++){
    ob+=inserta_diccionario(pdicc, claves[i]);
  }

  return ob;
}

int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo){
	if(pdicc == NULL)
    return NO_ENCONTRADO;

  return metodo(pdicc->tabla, 0, pdicc->n_datos, clave, ppos);
}


int bbin(int *tabla,int P,int U,int clave,int *ppos){
  int ob = 0;
  int m = 0;

  while (P <= U){
    m = (P + U)/2;

    ob++;

    if(clave == tabla[m]){
      *ppos = m;
      return ob;
    }

    else if (clave > tabla[m]){
      P = m + 1;
    }
    else{
      U = m - 1;
    }
  }
  return NO_ENCONTRADO;
}

int blin(int *tabla,int P,int U,int clave,int *ppos){
  int i = 0;
  int ob = 0;

  while (P < U){
    ob++;

    if(tabla[i] == clave){
      *ppos = i;
      return ob;
    }
    i++;
  }

  *ppos = NO_ENCONTRADO;

  return NO_ENCONTRADO;
}


int blin_auto(int *tabla,int P,int U,int clave,int *ppos){
  int ob = 0;
  int i = 0;

  while (P < U){
    ob++;

    if(tabla[i] == clave){
      if(i > 0){
        *ppos = i - 1;

        swap(&tabla[i], &tabla[i] - 1);

        return ob;
      }
      *ppos = i;

      return ob;
    }
    i++;
  }

  *ppos = NO_ENCONTRADO;

  return NO_ENCONTRADO;
}
