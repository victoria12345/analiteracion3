/**
 *
 * Descripcion: Implementacion de funciones de tiempo
 *
 * Fichero: tiempos.c
 * Autors: Victoria Pelayo e Ignacio Rabuñal
 * Version: 1.1
 * Fecha: 12-10-2017
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "tiempos.h"
#include <time.h>
#include "ordenacion.h"
#include "permutaciones.h"
#include <limits.h>
#include <math.h>

/***************************************************/
/* Funcion:tiempo_medio_ordenacion Fecha:12-10-2017*/
/* Autores: Victoria Pelayo e Igacio Rabuñal       */
/*                                                 */
/* Ordena tablas mediante un metodo pasado.        */
/*                                                 */
/* Entrada:                                        */
/* pfunc_ordena metodo: metodo que se va a usar    */
/* para ordenar las tablas                         */
/* int n_perms: numero de permutaciones a generar y*/
/* ordenar                                         */
/* int N: tamaño de las permutaciones              */
/* PTIEMPO ptiempo: estructura ptiempo que guardara*/
/* los resultados                                  */
/* Salida:                                         */
/* short: OK si se ordenan y ERR si algo falla     */
/***************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo,
                              int n_perms,
                              int N,
                              PTIEMPO ptiempo)
{
	clock_t ini,fin;
	int** perms= (int**)genera_permutaciones(n_perms,N);
	int i;

	if (perms == NULL) return ERR;

	ptiempo->N = N;
	ptiempo->min_ob = INT_MAX;
	ptiempo->max_ob = 0;
	ptiempo->medio_ob = 0;


	ini = clock( );

	for( i=0; i < n_perms; i++){
		int ob = metodo(perms[i], 0, N - 1);

		if(ob == ERR){

			for(i=0; i < n_perms; i++) free(perms[i]);

			free(perms);

			return ERR;
		}

		if (ob < ptiempo->min_ob) ptiempo->min_ob = ob;

		if (ob > ptiempo->max_ob) ptiempo->max_ob = ob;

		ptiempo->medio_ob += ob;
	}

	fin = clock();

	ptiempo->medio_ob /= n_perms;
	ptiempo->tiempo = (double)(fin - ini)/ n_perms / CLOCKS_PER_SEC;

	for(i=0; i < n_perms; i++) free(perms[i]);

	free(perms);

	return OK;
}

/***************************************************/
/* Funcion:tiempo_medio_ordenacion Fecha:12-10-2017*/
/* Autores: Victoria Pelayo e Igacio Rabuñal       */
/*                                                 */
/* Escribe en el fichero  los tiempos medios, y los*/
/* numeros promedio, minimo y maximo de veces que  */
/* se ejecuta la OB,del algoritmo metodo al ordenar*/
/* n_perm de tamaños desde num_min a num_max       */
/* separados por un incremento incr                */
/*                                                 */
/* Entrada:                                        */
/* pfunc_ordena metodo: metodo que se va a usar    */
/* char* fichero: nombre del fichero donde se va a */
/* escribir                                        */
/* int num_min: tamaño minimo de las permutaciones */
/* int max: tamaño maximo de las permutaciones     */
/* int incr: incremento entre los tamaños de las   */
/* permutaciones                                   */
/* Salida:                                         */
/* short: OK si se escribe y ERR si algo falla     */
/***************************************************/

short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero,
                                int num_min, int num_max,
                                int incr, int n_perms){
	int n = ((num_max - num_min) / incr) + 1;
	int j, tamanio;

	PTIEMPO tiempos = (PTIEMPO)malloc(n * sizeof(tiempos[0]));

	if(tiempos == NULL) free(tiempos);

	for (j = 0,tamanio = num_min; tamanio <= num_max; j++, tamanio+=incr){
		short codigo = tiempo_medio_ordenacion(metodo, n_perms, tamanio, &tiempos[j]);

		if (codigo == ERR){

			free(tiempos);

			return ERR;
		}
	}

	if (guarda_tabla_tiempos(fichero, tiempos, n) == ERR) return ERR;

	free(tiempos);

	return OK;
}

/***************************************************/
/* Funcion:tiempo_medio_ordenacion Fecha:12-10-2017*/
/* Autores: Victoria Pelayo e Igacio Rabuñal       */
/*                                                 */
/* Escribe en un fichero los datos                 */
/*                                                 */
/* Entrada:                                        */
/* char* fichero: nombre del fichero               */
/* PTIEMPO timepo: tiene los datos de la           */
/* realizacion del algortimo varias veces          */
/* int n_tiempos: numero de veces que se realizo   */
/* el algoritmo                                    */
/* PTIEMPO ptiempo: estructura ptiempo que guardara*/
/* los resultados                                  */
/* Salida:                                         */
/* short: OK si se escribe y ERR si algo falla     */
/***************************************************/

short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int n_tiempos){
	int i;

	FILE *f = fopen(fichero,"w");
	if (f == NULL) return ERR;

	for (i = 0; i < n_tiempos; i++){
		fprintf(f, "%d\t%f\t%f\t%d\t%d\n", tiempo[i].N,tiempo[i].tiempo,tiempo[i].medio_ob,tiempo[i].max_ob,tiempo[i].min_ob);
	}
	fclose(f);

	return OK;
}

short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, char orden, int N, int n_veces, PTIEMPO ptiempo){
  clock_t ini,fin;
  int i, ppos;
  PDICC diccionario;
  int *perm, *claves;

  diccionario = ini_diccionario(N, orden);

  if(diccionario == NULL)
    return ERR;

  perm = (int*)genera_perm(N);

  if(perm == NULL){
    libera_diccionario(diccionario);

    return ERR;
  }

  claves = (int*)malloc(n_veces*N*sizeof(claves[0]));

  if(claves == NULL){
    free(perm);
    libera_diccionario(diccionario);

    return ERR;
  }

  insercion_masiva_diccionario(diccionario, perm, N);

  generador(claves, n_veces*N, N);

  ptiempo->N = N;
  ptiempo->n_elems = n_veces;
	ptiempo->min_ob = INT_MAX;
	ptiempo->max_ob = 0;
	ptiempo->medio_ob = 0;


	ini = clock( );

  for(i = 0; i < n_veces*N; i++){
		int ob = busca_diccionario(diccionario, claves[i], &ppos ,metodo);

		if(ob == ERR){
      libera_diccionario(diccionario);
			free(claves);
      free(perm);

			return ERR;
		}

		if (ob < ptiempo->min_ob)
      ptiempo->min_ob = ob;

		if (ob > ptiempo->max_ob)
      ptiempo->max_ob = ob;

		ptiempo->medio_ob += ob;
	}

  fin = clock();

	ptiempo->medio_ob /= (n_veces*N);
	ptiempo->tiempo = (double)(fin - ini)/ (n_veces*N) / CLOCKS_PER_SEC;

  free(claves);
  free(perm);
  libera_diccionario(diccionario);

	return OK;
}


short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, int orden, char* fichero, int num_min, int num_max, int incr, int n_veces){
  int n = ((num_max - num_min) / incr) + 1;
	int j, tamanio;

	PTIEMPO tiempos = (PTIEMPO)malloc(n * sizeof(tiempos[0]));

	if(tiempos == NULL)
    return ERR;

	for (j = 0,tamanio = num_min; tamanio <= num_max; j++, tamanio += incr){
		short codigo = tiempo_medio_busqueda(metodo, generador, orden, tamanio, n_veces, &tiempos[j]);

		if (codigo == ERR){

			free(tiempos);

			return ERR;
		}
	}

	if (guarda_tabla_tiempos(fichero, tiempos, n) == ERR){

    free(tiempos);

    return ERR;
  }

	free(tiempos);

	return OK;
}
