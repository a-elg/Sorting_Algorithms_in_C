//*****************************************************************
//Curso: Análisis de algoritmos
//(C) Enero 2013
//ESCOM-IPN
//Ejemplo de medición de tiempo en C y recepción de parametros en C bajo UNIX
//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n" (Linux y MAC OS)
//*****************************************************************

//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
//*****************************************************************
//DEFINICION DE CONSTANTES DEL PROGRAMA
//*****************************************************************

//********************************************************************************
//DECLARACION DE ESTRUCTURAS
//********************************************************************************

//*****************************************************************
//VARIABLES GLOBALES
//*****************************************************************

//ul n; 	//n determina el tamaño del algorito dado por argumento al ejecutar
//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
/*Funcion que implementa el algortimo de ordenamiento Insersion, recibe el arreglo que almacena los valores a ordenar y el tamaño del arreglo (numero de valores a ordenar)*/
void insert_sort(int A[], int n);
//*****************************************************************
//PROGRAMA PRINCIPAL
//*****************************************************************
int main(int argc, char *argv[])
{
	//******************************************************************
	//Variables del main
	int *arreglo; //Arreglo que almacena los numeros a ordenar
	int numero;	  //Variable receptora de los números en el archivo 10millones.txt
	int i, j;	  //Variables para los loops
	//******************************************************************
	double utime0, stime0, wtime0, utime1, stime1, wtime1; //Variables para medición de tiempos

	//******************************************************************
	//Recepción y decodificación de argumentos
	//******************************************************************

	//Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
	if (argc != 2)
	{
		printf("\nIndicar el tamanio del algoritmo, por favor - Ejemplo: [user@equipo]$ %s 100 < numeros10millones.txt\n", argv[0]);
		exit(1);
	}
	//Tomar el segundo argumento como tamaño del algoritmo
	else
		numero = atoi(argv[1]); //Conversion de la cadena de la consola a numero

	//Asignacion de memoria dinamica para el arreglo de numeros a ordenar
	if ((arreglo = malloc(sizeof(int) * numero)) == NULL)
		perror("La asignacion dinamica no se pudo realizar correctamente");
	/*lee los numeros del archivo indicado en consola y los almacena en el arreglo*/
	for (i = 0; i < numero; i++)
	{
		scanf("%d", &arreglo[i]);
	}

	//******************************************************************
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	//******************************************************************
	uswtime(&utime0, &stime0, &wtime0);
	//******************************************************************

	//******************************************************************
	//Algoritmo
	//******************************************************************
	//Llamada a la funcion
	insert_sort(arreglo, numero);
	//******************************************************************

	//******************************************************************
	//Evaluar los tiempos de ejecución
	//******************************************************************
	uswtime(&utime1, &stime1, &wtime1);

	/*arreglo ya ordenado*/
	for (i = 0; i < numero; i++)
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
	//******************************************************************

	//Terminar programa normalmente
	exit(0);
}

//************************************************************************
//DEFINICIÓN DE FUNCIONES
//************************************************************************
/*Funcion del algortimo de ordenamiento por insercion */
void insert_sort(int A[], int n)
{
	int i, j, temp;
	for (i = 0; i < n; i++)
	{
		j = i;
		temp = A[i]; //Se almacena un valor del arreglo en la variable temp
		//Si el valor de temp es menor a su anterior y temp no es el primer elemento del arreglo
		while (j > 0 && temp < A[j - 1])
		{
			A[j] = A[j - 1]; //El elemento inmediato se recorre a su siguiente posicion
			j--;
		}
		A[j] = temp; //temp toma la posicion de su previo elemento anterior
	}
}
