/*****************************************************************
(C)Septiembre 2021

EQUIPO: Ponys Salvajes
INTEGRANTES DEL EQUIPO: 
López Gracia Angel Emmanuel 
López Hernández Lissete 
Martínez Martínez Fernando 
Martínez Ortiz Fabiola Yahel	
  VERSIÓN: 1.0
DESCRIPCIÓN: Implementación del algoritmo de ordenamiento por inserción. Mide el tiempo de ejecución del algoritmo. Se toman los valores de entrada del archivo .txt con los 10 millones de números.

CURSO: Análisis de algoritmos
COMPILACIÓN: "gcc [nombre_del_programa].c tiempo.x  -o main” 
  EJECUCIÓN: "./main n" (Linux y MAC OS)
*****************************************************************/


//LIBRERIAS INCLUIDAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
//*****************************************************************

//DECLARACIÓN DE FUNCIONES (PROTOTIPOS)
/*prototipo para la función que implementa el algoritmo de ordenamiento por inserción*/
void insert_sort(int A[], int n);
//*****************************************************************

//PROGRAMA PRINCIPAL
int main(int argc, char *argv[]){
	//Variables del main
	int *arreglo; //Arreglo que almacena los numeros a ordenar
	int numero;	  //Variable receptora de los números en el archivo 10millones.txt
	int i, j;	  //Variables para los loops
	//Variables para medición de tiempos
	double utime0, stime0, wtime0, utime1, stime1, wtime1; 

	/* RECEPCIÓN Y DECODIFICACIÓN DE ARGUMENTOS */
	//Condicional *if* se ejecuta en caso de no introducirse exactamente 2 argumentos (Cadena de ejecución y cadena=n)
	if (argc != 2)	{
		printf("\nIndicar el tamanio del algoritmo, por favor - Ejemplo: [user@equipo]$ %s 100 < numeros10millones.txt\n", argv[0]);
		exit(1);
	} else //Tomar el segundo argumento como tamaño del algoritmo
		numero = atoi(argv[1]); //Conversion de la cadena de la consola a numero

	//Asignacion de memoria dinamica para el arreglo de numeros a ordenar
	if ((arreglo = malloc(sizeof(int) * numero)) == NULL)
		perror("La asignacion dinamica no se pudo realizar correctamente");
	//Llenado del arreglo
	for (i = 0; i < numero; i++){
		scanf("%d", &arreglo[i]);
	}	
	//*****************************************************************
	
	//INICIAR EL CONTEO DEL TIEMPO PARA LAS EVALUACIONES DE RENDIMIENTO	
	uswtime(&utime0, &stime0, &wtime0);
	
	//ALGORITMO	
	//Llamada a la función del algoritmo
	insert_sort(arreglo, numero);

	//EVALUAR LOS TIEMPOS DE EJECUCIÓN 
	uswtime(&utime1, &stime1, &wtime1);

	//Comprobar números ordenados (imprimir arreglo ordenado)
	/*for (i = 0; i < numero; i++)
		printf("%d\n", arreglo[i]);
	
	//Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n", wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n", utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10f s\n", stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");

	//Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n", wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n", utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10e s\n", stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	*/

	//FORMATO PARA OBTENER TIEMPO DE EJECUCIÓN 
	printf("Insrt %15.10e  %21.10e %21.10e %21.10f%% \n", wtime1 - wtime0,utime1 - utime0,stime1 - stime0,100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));

	//Finaliza programa
	exit(0);
}

//DEFINICIÓN DE FUNCIONES
//************************************************************************
/*FUNCIÓN QUE IMPLEMENTA EL ALGORITMO DE INSERCIÓN*/
/* Recibe: Arreglo de enteros A[], entero n */
/* Devuelve: void */void insert_sort(int A[], int n) {
	int i, j, temp;
	for (i = 0; i < n; i++) {
		j = i;
		temp = A[i]; //Se almacena un valor del arreglo en la variable temp
		//Si el valor de temp es menor a su anterior y temp no es el primer elemento del arreglo
		while (j > 0 && temp < A[j - 1])  {
			A[j] = A[j - 1]; //El elemento inmediato se recorre a su siguiente posicion
			j--;
		}
		A[j] = temp; //temp toma la posicion de su previo elemento anterior
	}
}
