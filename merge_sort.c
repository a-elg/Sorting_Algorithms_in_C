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
#include <math.h>
#include "tiempo.h"

//DEFINICION DE CONSTANTES DEL PROGRAMA
#define MAX 100

//DECLARACION DE ESTRUCTURAS
typedef unsigned int ui;
typedef unsigned long ul;

//VARIABLES GLOBALES
ul n; 	//n determina el tamaño del algorito dado por argumento al ejecutar

//DECLARACIÓN DE FUNCIONES
void mergeSort();
void merge();

//PROGRAMA PRINCIPAL 
int main (int argc, char* argv[]){	
	ui numero;//Variable receptora de los números en el archivo 10millones.txt
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	ul i; //Variables para loops
	
	//Recepción y decodificación de argumentos
	if (argc!=2){ //Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
		printf("\nIndicar el tamanio del algoritmo, por favor - Ejemplo: [user@equipo]$ %s 100 < numeros10millones.txt\n",argv[0]);
		exit(1);
	}else //Tomar el segundo argumento como tamaño del algoritmo
		n=strtoul(argv[1],NULL,10);

	//Crear el arreglo de tamaño n
	ui * datos = (ui*)malloc(sizeof(ui)*n);

	//Llenar el arreglo
	for(i=0;i<n;i++){
        scanf("%u",&numero);
        datos[i]=numero;
    }

	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	uswtime(&utime0, &stime0, &wtime0);
	
	//Algoritmo
	mergeSort(datos, 0, n-1);

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
		printf("%u\n", datos[i]);
	}

	//Terminar programa normalmente	
	exit (0);	
}

//DEFINICIÓN DE FUNCIONES 
void mergeSort(ui A[], ui p, ui r){ //p es el principio, q la mitad y r el final -> [P| |q| |r] ->r=n-1
    ui q;
    if(p<r){ //No puede ser el principio y el final iguales, en caso contrario la lista es de 1 elemento
        q = floor((p+r)/2);
        mergeSort(A, p, q); //Lado izquierdo
        mergeSort(A, q+1, r); //Lado derecho
        merge(A, p, q, r); //Ordena las sublistas
    }
}

void merge(ui *A, ui p, ui q, ui r){
    ui l=r-p+1; //longitud de la lista a mezclar
    ui i=p; //indice que itera lista izquierda
    ui j=q+1; //indice que itera lista derecha
	ui * c = (ui*)malloc(sizeof(ui)*l); //lista auxiliar de tamaño l

    ui k=0;
    for(k=0; k<l; k++){ //Se va llenando ordenadamente la lista auxiliar
        if(i<=q && j<=r){ //mientras haya elementos que iterar en ambas listas
            if(A[i]<A[j]){ //Si el elemento de la lista izquierda es menor al de la lista derecha
                c[k] = A[i]; //Se coloca el elemento de la lista izquierda
                i++; //Aumenta el iterador de la lista izquierda
            }else{
                c[k] = A[j]; //Se coloca el elemento de la lista derecha
                j++; //Se aumenta el iterador de la lista derecha
            }
        }else{ //En alguna de las listas ya no hay elementos a iterar
            if(i<=q){ //Si sobraron elementos en la lista izquierda
                c[k] = A[i]; //Se van pasando los elementos de la lista izquierda
                i++; //Se aumenta el iterador de la lista izquierda
            }else{ //Se aumenta el iterador de la lista izquierda
                c[k] = A[j]; //Se van pasando los elementos de la lista derecha
                j++; //Sobraron elementos en la lista derecha
            }
        }
    }
	// memcpy(A+p-r, c, sizeof(ui)*l);
    // A[p-r] = *c; //Se coloca la sublista ordenada en la lista original
	// for(k=0; k<l; k++){
	// 	A[p-r+k] = c[k];
	// }
	A[r-p] = *c;
}