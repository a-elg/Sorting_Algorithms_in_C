/*****************************************************************
(C)Septiembre 2021

EQUIPO: Ponys Salvajes
INTEGRANTES DEL EQUIPO: 
López Gracia Angel Emmanuel 
López Hernández Lissete 
Martínez Martínez Fernando 
Martínez Ortiz Fabiola Yahel	
  VERSIÓN: 1.0
DESCRIPCIÓN: Implementación del algoritmo de ordenamiento por el método de la burbuja en su primera optimización. Mide el tiempo de ejecución del algoritmo. Se toman los valores de entrada del archivo .txt con los 10 millones de números.

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

//VARIABLES GLOBALES
int n; 	//n determina el tamaño del algorito dado por argumento al ejecutar

//DECLARACIÓN DE FUNCIONES (PROTOTIPOS)
/*prototipo para la función que implementa el algoritmo de ordenamiento por selección*/
void bubbleSortOp1();
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
	if ((datos = malloc(sizeof(int) * n)) == NULL)
		perror("La asignacion dinamica no se realizo correctamente");
	//Llenado del arreglo
	for (i = 0; i < n; i++){
		scanf("%d", &datos[i]);
	}	
	//*****************************************************************
	
	//INICIAR EL CONTEO DEL TIEMPO PARA LAS EVALUACIONES DE RENDIMIENTO	
	uswtime(&utime0, &stime0, &wtime0);
	
	//ALGORITMO	
	//Llamada a la función del algoritmo
	bubbleSortOp1(datos);

	//EVALUAR LOS TIEMPOS DE EJECUCIÓN 
	uswtime(&utime1, &stime1, &wtime1);
	
	//Comprobar números ordenados (imprimir arreglo ordenado)
	/*for (i = 0; i < n; i++)
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

/*FUNCIÓN QUE IMPLEMENTA EL ALGORITMO DE BURBUJA EN SU PRIMERA VERSIÓN OPTIMIZADA*/
/* Recibe: Arreglo de enteros datos[]*/
/* Devuelve: void */
void bubbleSortOp1(int datos[]){//Ordenamiento Burbuja optimizacion 1
    int i, j, aux;
    for(i=0; i<=n-2; i++){ //Se repite por cada elemento del arreglo
        for(j=0; j<=n-2-i; j++){ //Se comparan en pares el arrego sin comparar los mayores de cada iteración
			//Si un número es mayor que su subsiguiente se realiza el intercambio
            if(datos[j] > datos[j+1]){
                aux = datos[j];
                datos[j] = datos[j+1];
                datos[j+1] = aux;
            }
        }
    }
}