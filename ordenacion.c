/**
 *
 * Descripcion: Implementacion de funciones de ordenacion
 *
 * Fichero: ordenacion.c
 * Autores: Victoria Pelayo e Ignacio Rabuñal
 * Version: 1.1
 * Fecha: 12-10-2017
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "ordenacion.h"
#include "permutaciones.h"


/** Definicion de funciones privadas*/

int medio(int *tabla, int ip, int iu,int *pos);

int medio_stat (int* tabla, int ip, int iu, int* pos);

int medio_avg(int *tabla, int ip, int iu, int *pos);

int quicksort(int* tabla, int ip, int iu, pfunc_medio metodo);

int partir(int* tabla, int ip, int iu, int *pos, pfunc_medio metodo);

/***************************************************/
/* Funcion: BubbleSort Fecha: 12-10-2017           */
/* Autores: Victoria Pelayo e Igacio Rabuñal       */
/*                                                 */
/* Ordena números de menor a mayor de una tabla    */
/* dada entre la posicion ip e iu                  */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: tabla que se va a ordenar           */
/* int ip: posición desde donde se va a ordenar    */
/* int iu: posición hasta donde se va a ordenar    */
/* Salida:                                         */
/* int: numero de veces que se ha realizado la ob  */
/***************************************************/
int BubbleSort(int* tabla, int ip, int iu){

	int ob = 0;
	int i;
	int flag = 1;

	i = iu;

	if (tabla == NULL) return ERR;

	while (flag == 1 && i >= ip + 1) {
		int j;

		flag = 0;

		for (j = ip; j <= i - 1; j++){
			ob++;

			if (tabla[j] > tabla[j+1]){

				swap(&tabla[j], &tabla[j + 1]);

				flag = 1;
			}
		}

		i--;
	}

	return ob;
}

/***************************************************/
/* Funcion: merge Fecha: 22-10-2017           */
/* Autores: Victoria Pelayo e Igacio Rabuñal       */
/*                                                 */
/* Ordena números de menor a mayor de una tabla    */
/* dada entre la posicion ip e iu                  */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: tabla que se va a ordenar           */
/* int ip: posición desde donde se va a ordenar    */
/* int iu: posición hasta donde se va a ordenar    */
/* int imedio: posicion media de la tabla, a ambos */
/* lados ya esta respectivamente ordenada.         */
/* Salida:                                         */
/* ob: numero de veces que se ha realizado la ob*/
/***************************************************/
int merge(int* tabla, int ip, int iu, int imedio){

	int *aux = NULL;
	int i = ip;
	int k = 0;
	int j = imedio +1;
	int ob = 0;

	aux = (int*)malloc(sizeof(aux[0]) * (iu - ip + 1));

	if(aux == NULL) return ERR;

	while (i <= imedio && j<= iu){

		ob++;

		if (tabla[i] < tabla[j]){
			aux[k] = tabla[i];
			i++;
		}

		else{
			aux[k] = tabla[j];
			j++;
		}

		k++;
	}

	if(i > imedio){
		while(j <= iu){

			aux[k] = tabla[j];

			k++;
			j++;
		}
	}

	else if(j > iu){
		while( i <= imedio){

			aux[k] = tabla[i];

			k++;
			i++;
		}
	}

	tabla+=ip;

	for(i = 0; i < k; i++){
		tabla[i] = aux[i];
	}

	tabla-=ip;

	free(aux);

	return ob;
}

/***************************************************/
/* Funcion: mergesort  Fecha: 22-10-2017           */
/* Autores: Victoria Pelayo e Igacio Rabuñal       */
/*                                                 */
/* Ordena números de menor a mayor de una tabla    */
/* dada entre la posicion ip e iu. Para ello va a  */
/* llamar a otra funcion.Es un algoritmo recursivo */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: tabla que se va a ordenar           */
/* int ip: posición desde donde se va a ordenar    */
/* int iu: posición hasta donde se va a ordenar    */
/* Salida:                                         */
/* ob:numero de veces que se ha realizado la ob */
/***************************************************/
int mergesort(int* tabla, int ip, int iu){

	int M = (iu + ip)/2;
	int ob = 0;

	if (ip == iu) return ob;

	ob += mergesort(tabla, ip, M);
	ob += mergesort(tabla, M + 1, iu);
	ob += merge (tabla, ip, iu, M);

	return ob;
}

/***************************************************/
/* Funcion: medio Fecha: 10-11-2017                */
/* Autores: Victoria Pelayo e Igacio Rabuñal       */
/*                                                 */
/* OElige como pivote el elemento de la primera    */
/* posicion.                                       */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: tabla que se va a ordenar           */
/* int ip: posición desde donde se va a ordenar    */
/* int pos: posición del pivote                    */
/* Salida:                                         */
/* int: numero de veces que se ha realizado la ob  */
/***************************************************/
int medio(int *tabla, int ip, int iu,int *pos){

	*pos = ip;

	return 0;
}

/***************************************************/
/* Funcion: medio_avg Fecha: 10-11-2017            */
/* Autores: Victoria Pelayo e Igacio Rabuñal       */
/*                                                 */
/* OElige como pivote el elemento del medio        */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: tabla que se va a ordenar           */
/* int ip: posición desde donde se va a ordenar    */
/* int pos: posición del pivote                    */
/* Salida:                                         */
/* int: numero de veces que se ha realizado la ob  */
/***************************************************/
int medio_avg(int *tabla, int ip, int iu, int *pos){

	*pos = (ip + iu) / 2;

	return 0;
}

/***************************************************/
/* Funcion: medio_stat Fecha: 10-11-2017           */
/* Autores: Victoria Pelayo e Igacio Rabuñal       */
/*                                                 */
/* Elige como pivote el elemento que se encuentra  */
/* en medio de los tres que se le pasa.            */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: tabla que se va a ordenar           */
/* int ip: posición desde donde se va a ordenar    */
/* int pos: posición del pivote                    */
/* Salida:                                         */
/* int: numero de veces que se ha realizado la ob  */
/***************************************************/
int medio_stat (int* tabla, int ip, int iu, int* pos){

	int im = (ip + iu)/2;
	int ob = 0;

	ob++;

	if (tabla[ip] <= tabla[im]){
		ob++;

		if(tabla[iu] <= tabla[im]){
			ob++;

			if(tabla[ip] <= tabla[iu]){
				*pos = iu;
			}

			else *pos = ip;
		}

		else *pos = im;
	}

	else {
		ob++;

		if(tabla[im] <= tabla[iu]){
			ob++;

			if(tabla[iu] <= tabla[ip]){
				*pos = iu;
			}

			else  *pos = ip;
		}

		else *pos = im;
	}

	return ob;
}

/***************************************************/
/* Funcion: partir Fecha: 10-11-2017               */
/* Autores: Victoria Pelayo e Igacio Rabuñal       */
/*                                                 */
/* Funcion recursiva de QuickSort. Ordena el pivote*/
/* obtenido mediante a la llamada a una función.   */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: tabla que se va a ordenar           */
/* int ip: posición desde donde se va a ordenar    */
/* int pos: posición del pivote                    */
/* pfunc_medio metodo: devuelve el pivote          */
/* Salida:                                         */
/* int: numero de veces que se ha realizado la ob  */
/***************************************************/
int partir(int* tabla, int ip, int iu, int *pos, pfunc_medio metodo){

	int k;
	int i;
	int ob = 0;

	ob = metodo(tabla,ip,iu,pos);

	*pos = ip;

	k = tabla[*pos];

	swap(&tabla[ip], &tabla[*pos]);

	*pos = ip;

	for(i = ip + 1; i <= iu; i++ ){

		ob++;

		if(tabla[i] < k){
			(*pos)++;

			swap(&tabla[i], &tabla[*pos]);
		}
	}

	swap(&tabla[ip], &tabla[*pos]);

	return ob;

}

/***************************************************/
/* Funcion: partir Fecha: 10-11-2017               */
/* Autores: Victoria Pelayo e Igacio Rabuñal       */
/*                                                 */
/* QuickSort ordena una tabla                      */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: tabla que se va a ordenar           */
/* int ip: posición desde donde se va a ordenar    */
/* int pos: posición del pivote                    */
/* pfunc_medio metodo: devuelve el pivote          */
/* Salida:                                         */
/* int: numero de veces que se ha realizado la ob  */
/***************************************************/
int quicksort(int* tabla, int ip, int iu, pfunc_medio metodo){

	int pos = 0;
	int ob = 0;

	if(ip > iu) return ERR;

	else if(ip == iu) return ob;

	else{

		ob += partir(tabla, ip, iu, &pos, metodo);

		if( ip < pos - 1)
			ob += quicksort(tabla, ip, pos - 1, metodo);

		if( pos + 1 < iu)
			ob += quicksort(tabla, pos + 1, iu, metodo);
	}

	return ob;
}

/**
* Estas funciones han sido creadas para llamarlas desde ejercicio5.c
*/

/***************************************************/
/* Funcion: quicksort1 Fecha: 11-11-2017           */
/* Autores: Victoria Pelayo e Igacio Rabuñal       */
/*                                                 */
/* Llama a QuickSort utilizando medio              */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: tabla que se va a ordenar           */
/* int ip: posición desde donde se va a ordenar    */
/* int pos: posición del pivote                    */
/* pfunc_medio metodo: devuelve el pivote          */
/* Salida:                                         */
/* int: numero de veces que se ha realizado la ob  */
/***************************************************/
int quicksort1(int* tabla, int ip, int iu){

	return quicksort(tabla,ip,iu,medio);
}

/***************************************************/
/* Funcion: quicksort2 Fecha: 11-11-2017           */
/* Autores: Victoria Pelayo e Igacio Rabuñal       */
/*                                                 */
/* Llama a QuickSort utilizando medio_avg          */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: tabla que se va a ordenar           */
/* int ip: posición desde donde se va a ordenar    */
/* int pos: posición del pivote                    */
/* pfunc_medio metodo: devuelve el pivote          */
/* Salida:                                         */
/* int: numero de veces que se ha realizado la ob  */
/***************************************************/
int quicksort2(int* tabla, int ip, int iu){

	return quicksort(tabla,ip,iu,medio_avg);
}

/***************************************************/
/* Funcion: quicksort3 Fecha: 11-11-2017           */
/* Autores: Victoria Pelayo e Igacio Rabuñal       */
/*                                                 */
/* Llama a QuickSort utilizando medio_stat         */
/*                                                 */
/* Entrada:                                        */
/* int* tabla: tabla que se va a ordenar           */
/* int ip: posición desde donde se va a ordenar    */
/* int pos: posición del pivote                    */
/* pfunc_medio metodo: devuelve el pivote          */
/* Salida:                                         */
/* int: numero de veces que se ha realizado la ob  */
/***************************************************/
int quicksort3(int* tabla, int ip, int iu){

	return quicksort(tabla,ip,iu, medio_stat);
}
