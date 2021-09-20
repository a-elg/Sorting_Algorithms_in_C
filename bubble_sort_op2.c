/*****************************************************************
(C)Septiembre 2021

EQUIPO: Ponys Salvajes
INTEGRANTES DEL EQUIPO: 
López Gracia Angel Emmanuel 
López Hernández Lissete 
Martínez Martínez Fernando 
Martínez Ortiz Fabiola Yahel	
  VERSIÓN: 1.0
DESCRIPCIÓN: Implementación del algoritmo de ordenamiento por el método de la burbuja en su segunda versión optimizada. Mide el tiempo de ejecución del algoritmo. Se toman los valores de entrada del archivo .txt con los 10 millones de números.

CURSO: Análisis de algoritmos
COMPILACIÓN: "gcc main.c tiempo.x  -o main” 
  EJECUCIÓN: "./main n" (Linux y MAC OS)
*****************************************************************/

//LIBRERIAS INCLUIDAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
//*****************************************************************

//DEFINICIÓN DE CONSTANTES
#define true 1
#define false 0
//*****************************************************************

//VARIABLES GLOBALES
//n determina el tamaño del algorito dado por argumento al ejecutar
int n; 	
//*****************************************************************

//DECLARACIÓN DE FUNCIONES (PROTOTIPOS)
/*prototipo para la función que implementa el algoritmo de ordenamiento por el método de la burbuja tradicional*/
void bubbleSortOp2();
//*****************************************************************

//PROGRAMA PRINCIPAL 
int main (int argc, char* argv[]){	
	//Variables del main	
	int *datos;
	int i;
	//Variables para medición de tiempos
	double utime0, stime0, wtime0,utime1, stime1, wtime1;
	
	/* RECEPCIÓN Y DECODIFICACIÓN DE ARGUMENTOS */
	//Condicional *if* se ejecuta en caso de no introducirse exactamente 2 argumentos (Cadena de ejecución y cadena=n)
	if (argc!=2){ //Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
		printf("\nIndicar el tamanio del algoritmo, por favor - Ejemplo: [user@equipo]$ %s 100 < numeros10millones.txt\n",argv[0]);
		exit(1);
	}else //Tomar el segundo argumento como tamaño del algoritmo
		n=atoi(argv[1]);

	//Asignacion de memoria dinamica para el arreglo de numeros a ordenar
	if ((datos = malloc(sizeof(int)*n)) == NULL)
		perror("La asignacion dinamica no se realizo correctamente");

	//Llenado del arreglo
	for(i=0;i<n;i++){
        scanf("%d",&datos[i]);
    }
	//*****************************************************************

	//INICIAR EL CONTEO DEL TIEMPO PARA LAS EVALUACIONES DE RENDIMIENTO	
	uswtime(&utime0, &stime0, &wtime0);
	
	//ALGORITMO	
	//Llamada a la función del algoritmo
	bubbleSortOp2(datos);

	//EVALUAR LOS TIEMPOS DE EJECUCIÓN 
	uswtime(&utime1, &stime1, &wtime1);
	
	//Comprobar números ordenados (imprimir arreglo ordenado)
	/*for(i=0; i<n; i++)
		printf("%d\n", datos[i]);

	//Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	*/

	//FORMATO PARA OBTENER TIEMPO DE EJECUCIÓN 
	printf("Insrt %15.10e  %21.10e %21.10e %21.10f%% \n", wtime1 - wtime0,utime1 - utime0,stime1 - stime0,100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));

	//Finaliza programa
	exit (0);	
}

//DEFINICIÓN DE FUNCIONES 
//************************************************************************

/*FUNCIÓN QUE IMPLEMENTA EL ALGORITMO DE BURBUJA EN SU SEGUNDA VERSIÓN OPTIMIZADA*/
/* Recibe: Arreglo de enteros datos[]*/
/* Devuelve: void */
void bubbleSortOp2(int datos[]){//Ordenamiento Burbuja optimizacion 2
	int cambios = true;
	int i=0, j, aux;
    while(i<=n-2 && cambios!=false){ //Mientras haya cambios y no se sobrepase el tamaño del arreglo
        cambios = false;//Si se mantiene este valor entonces no hubo cambios
        for(j=0; j<=n-2-i; j++){ //Compara por pares excepto los números mayores de cada iteración
            if(datos[j] > datos[j+1]){ //Si un número es mayor que su subsiguiente se realiza el intercambio
                aux = datos[j];
                datos[j] = datos[j+1];
                datos[j+1] = aux;
                cambios = true; //Si llega aqui significa que hubo cambios
            }
        }
        i++;
    }
}