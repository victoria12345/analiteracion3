/**
 *
 * Descripcion: Implementacion de funciones de generacion de permutaciones
 *
 * Fichero: permutaciones.c
 * Autores: Victoria Pelayo e Ignacio Rabuñal
 * Version: 1.1
 * Fecha: 21-09-2017
 *
 */
#include <stdio.h>
#include <string.h>

void swap (int *a, int *b){
	int temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
	
	return;
}

#include "permutaciones.h"

/***************************************************/
/* Funcion: aleat_num Fecha: 21-09-2017            */
/* Autores: Victoria Pelayo e Igacio Rabuñal       */
/*                                                 */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/* Salida:                                         */
/* int: numero aleatorio                           */
/***************************************************/
int aleat_num(int inf, int sup){
	
	return inf + (rand() % (sup - inf + 1));
}

/***************************************************/
/* Funcion: genera_perm Fecha: 21-10-2017          */
/* Autores: Victoria Pelayo e Ignacio Rabuñal      */
/*                                                 */
/* Rutina que genera una permutacion               */
/* aleatoria                                       */
/*                                                 */
/* Entrada:                                        */
/* int n: Numero de elementos de la                */
/* permutacion                                     */
/* Salida:                                         */
/* int *: puntero a un array de enteros            */
/* que contiene a la permutacion                   */
/* o NULL en caso de error                         */
/***************************************************/
int* genera_perm(int N){	
	int i;
  	int* perm = (int *) malloc(N * sizeof(perm[0]));

	if (perm == NULL) 
		return NULL;

	for(i=0; i < N; i++)
		perm[i] = i + 1;
	
	for(i=0; i < N; i++)
		swap (&perm[i], &perm[aleat_num(i, N - 1)]);
	
	return perm;
}

/***************************************************/
/* Funcion: genera_permutaciones Fecha: 21-09-2017 */
/* Autores: Victoria Pelayo e Ignacio Rabuñal      */
/*                                                 */
/* Funcion que genera n_perms permutaciones        */
/* aleatorias de tamanio elementos                 */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: Numero de permutaciones            */
/* int N: Numero de elementos de cada              */
/* permutacion                                     */
/* Salida:                                         */
/* int**: Array de punteros a enteros              */
/* que apuntan a cada una de las                   */
/* permutaciones                                   */
/* NULL en caso de error                           */
/***************************************************/
int** genera_permutaciones(int n_perms, int N){
	int i;
	int **perms=(int**)malloc(n_perms*sizeof(perms[0]));
	
	if(perms == NULL) return NULL;

	for(i=0;i<n_perms;i++){
		
		perms[i]=genera_perm(N);
		
		if (perms[i]==NULL){
			int j;
			
			for (j=0;j<i;j++) free(perms[j]);
			
			free(perms);
		}
	}
	return perms;
}
