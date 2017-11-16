/**
 *
 * Descripcion: Funciones de cabecera para ordenacion
 *
 * Fichero: ordenacion.h
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2016
 *
 */

#ifndef ORDENACION_H
#define ORDENACION_H

/* constantes */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

/* definiciones de tipos */
typedef int (* pfunc_ordena)(int*, int, int);
typedef int (*pfunc_medio)(int*, int, int, int*);

/* Funciones */

int BubbleSort(int* tabla, int ip, int iu);

int merge(int* tabla, int ip, int iu, int imedio);

int mergesort(int* tabla, int ip, int iu);

int quicksort1(int* tabla, int ip, int iu);

int quicksort2(int* tabla, int ip, int iu);

int quicksort3(int* tabla, int ip, int iu);

#endif
