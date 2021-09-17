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
//*****************************************************************

//VARIABLES GLOBALES
int n; 	//n determina el tamaño del algorito dado por argumento al ejecutar
//*****************************************************************

//DECLARACIÓN DE FUNCIONES (PROTOTIPOS)
/*prototipo para la función que implementa el algoritmo de ordenamiento por mezcla*/
void mergeSort();
/*prototipo para la función que realiza el ordenamiento y mezcla para las sublistas*/
void merge();
//*****************************************************************

//PROGRAMA PRINCIPAL 
int main (int argc, char* argv[]){	
	//Variables del main
	int *datos;
	int i;
	//Variables para medición de tiempos
	double utime0, stime0, wtime0,utime1, stime1, wtime1;

	
	//Recepción y decodificación de argumentos
	if (argc!=2){ //Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
		printf("\nIndicar el tamanio del algoritmo, por favor - Ejemplo: [user@equipo]$ %s 100 < numeros10millones.txt\n",argv[0]);
		exit(1);
	} else //Tomar el segundo argumento como tamaño del algoritmo
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
	mergeSort(datos, 0, n-1);

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

/*FUNCIÓN QUE IMPLEMENTA EL ALGORITMO MERGE*/
/* Recibe: Arreglo de enteros A[], el entero p (principio), q (la mitad) y r (el final -> [P| |q| |r] ->r=n-1*)/
/* Devuelve: void */
void mergeSort(int A[], int p, int r){ 
    int q;
    if(p<r){ //No puede ser el principio y el final iguales, en caso contrario la lista es de 1 elemento
        q = floor((p+r)/2); //Se obtiene la posicion en la mitad
        mergeSort(A, p, q); //Ordena lado izquierdo
        mergeSort(A, q+1, r); //Ordena lado derecho
        merge(A, p, q, r); //Une y ordena ambas sublistas
    }
}

/*FUNCIÓN QUE REALIZA EL ORDENAMIENTO Y MEZCLA DE DE LAS SUBLISTAS*/
/* Recibe: Arreglo de enteros datos[]*/
/* Devuelve: void */
void merge(int A[], int p, int q, int r){
    int l=r-p+1; //longitud de la lista a mezclar
    int i=p; //indice que itera lista izquierda
    int j=q+1; //indice que itera lista derecha
	int *c = (int*)malloc(sizeof(int)*l); //lista auxiliar de tamaño l

    int k;
    for(k=0; k<l; k++){ //Se llena ordenadamente la lista auxiliar
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
            }else{ //Sobraron elementos en la lista derecha
                c[k] = A[j]; //Se van pasando los elementos de la lista derecha
                j++; //Sobraron elementos en la lista derecha
            }
        }
    }

	for(k=0; k<l; k++){//Se coloca la sublista ordenada en la lista original
		A[p+k] = c[k];
	}
}