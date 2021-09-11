//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis de algoritmos
//(C) Enero 2013
//ESCOM-IPN
//Ejemplo de medición de tiempo en C y recepción de parametros en C bajo UNIX
//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n" (Linux y MAC OS)
//*****************************************************************
 
//LIBRERIAS INCLUIDAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"

//Definicion de constantes
#define true 1
#define false 0

//VARIABLES GLOBALES
int n; 	//n determina el tamaño del algorito dado por argumento al ejecutar

//DECLARACIÓN DE FUNCIONES
void bubbleSortOp2();

//PROGRAMA PRINCIPAL 
int main (int argc, char* argv[]){	
	int numero;//Variable receptora de los números en el archivo 10millones.txt
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	int i; //Variables para loops
	
	//Recepción y decodificación de argumentos
	if (argc!=2){ //Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
		printf("\nIndicar el tamanio del algoritmo, por favor - Ejemplo: [user@equipo]$ %s 100 < numeros10millones.txt\n",argv[0]);
		exit(1);
	}else //Tomar el segundo argumento como tamaño del algoritmo
		n=atoi(argv[1]);

	//Crear el arreglo de tamaño n
	int * datos = (int*)malloc(sizeof(int)*n);

	//Llenar el arreglo
	for(i=0;i<n;i++){
        scanf("%d",&numero);
        datos[i]=numero;
    }

	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	uswtime(&utime0, &stime0, &wtime0);
	
	//Algoritmo
	bubbleSortOp2(datos);

	//Evaluar los tiempos de ejecución 
	uswtime(&utime1, &stime1, &wtime1);
	
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


	//Comprobar números ordenados (imprimir arreglo ordenado)
	for(i=0; i<n; i++){
		printf("%d\n", datos[i]);
	}

	//Terminar programa normalmente	
	exit (0);	
}

//DEFINICIÓN DE FUNCIONES 
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