//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
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
#include <math.h>
#include <string.h>
#include "tiempo.h"
//*****************************************************************
//DEFINICION DE CONSTANTES DEL PROGRAMA
//*****************************************************************
//#define MAX 100
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
//prototipo para la función que implementa el algoritmo de ordenamiento shell
void shell_sort(int A[], int n);
//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************
int main (int argc, char* argv[])
{	
	//******************************************************************	
	//Variables del main
	int *arreglo;
	int numero;
	int i, j;
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	//ul i; //Variables para loops
	//******************************************************************	
	//Recepción y decodificación de argumentos
	//******************************************************************	

	//Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
	if (argc!=2){
		printf("\nIndicar el tamanio del algoritmo, por favor - Ejemplo: [user@equipo]$ %s 100 < numeros10millones.txt\n",argv[0]);
		exit(1);
	} 
	//Tomar el segundo argumento como tamaño del algoritmo
	else
		numero=atoi(argv[1]);

	//Asignacion de memoria dinamica para el arreglo de numeros a ordenar
	if ((arreglo = malloc(sizeof(int) * numero)) == NULL)
		perror("No se pudo solicitar memoria para el arreglo");
	/*lee los numeros del archivo indicado en consola y los almacena en el arreglo*/
	for (i = 0; i < numero; i++){
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
	shell_sort(arreglo, numero);
	//******************************************************************

	//******************************************************************	
	//Evaluar los tiempos de ejecución 
	//******************************************************************
	uswtime(&utime1, &stime1, &wtime1);

	/*arreglo ordenado*/
	for (i = 0; i < numero; i++)
		printf("%d\n", arreglo[i]);
	
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
	//******************************************************************

	//Terminar programa normalmente	
	exit (0);	
}

//************************************************************************
//DEFINICIÓN DE FUNCIONES 
//************************************************************************

void shell_sort(int A[], int n){
	int i, k, b, temp;

	/*definimos el salto como k*/
	k = trunc(n/2); 
	/*se harán las iteraciones hasta que el salto sea mayor o igual a 1*/
	while (k >= 1){
		b = 1;
		while (b!= 0){
			b=0;
			for(i = k; i <= n-1; i++){
				if (A[i-k] > A[i]){
					/*Se guarda el menor valor en variable temporal*/
					temp = A[i];
					/*Se hace primer intercambio: mayor se acomoda en donde estaba menor valor*/
					A[i] = A[i-k];
					/*Segundo intercambio: menor se acomoda en donde estaba mayor valor*/
					A[i-k] = temp;
					b=b+1;
				}
			}
		}
		/*Al terminar el recorrido del arreglo con salto = k, se vuelve a dividir ese salto y realiza un nuevo recorrido*/
		k=trunc(k/2);
	}
}	
