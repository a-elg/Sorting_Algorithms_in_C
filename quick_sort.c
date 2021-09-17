//*****************************************************************
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
//*****************************************************************

//DECLARACIÓN DE FUNCIONES (PROTOTIPOS)
/*prototipo para la función que se encarga de llamar a las funciones pivote y swap, que ordenan progresivamente el arreglo, comenzando de un pivote, posteriormente ordenando la seccion con numeros menores a ese pivote, finalizando con la seccion con numeros mayores al pivote inicial. Recibe el arreglo a ordenar, la primera y ultima posicion del arreglo */
void quick_sort(int A[], int p, int fin);
/*prototipo para la función  que se encarga de mover los indices j e i al recorrer el arreglo, el movimiento de los indices se da en funcion de comparaciones. El indice i recorre el arreglo de izquierda a derecha comparando si los numeros encontrados son menores al pivote, y el indice j recorre el arreglo de derecha a izquierda comparando si los numeros encontrados son mayores al pivote, en caso de que dichas condiciones se cumplan i se incrementara en una unidad y j se decrementara en una unidad, al encontrar una pareja que valores que no cumplan las condiciones se llama a la funcion swap*/
int pivote(int A[], int p, int fin);
/*prototipo para la función  que se encarga de intercambiar dos numeros en un arreglo, recibe un arreglo A[], un indice i, un indice j. LOs indices indican las posiciones del arreglo cuyos valores se intercambiaran*/
int swap(int A[], int i, int j);
//*****************************************************************

//PROGRAMA PRINCIPAL
int main(int argc, char *argv[]){
	//Variables del main
	int numero;	  //Variable receptora de los números en el archivo 10millones.txt
	int *arreglo; //Arreglo que almacena los numeros a ordenar
	int i, j;	  //indices de inicio (i) y final (j) que recorren el arreglo en busca de numeros mayores y menores que el pivote. i tambien se usa en loops
	 //Variables para medición de tiempos
	double utime0, stime0, wtime0, utime1, stime1, wtime1;
	
	/* RECEPCIÓN Y DECODIFICACIÓN DE ARGUMENTOS */
	//Condicional *if* se ejecuta en caso de no introducirse exactamente 2 argumentos (Cadena de ejecución y cadena=n)
	if (argc != 2) {
		printf("\nIndicar el tamanio del algoritmo, por favor - Ejemplo: [user@equipo]$ %s 100 < numeros10millones.txt\n", argv[0]);
		exit(1);
	} else //Tomar el segundo argumento como tamaño del algoritmo
		numero = atoi(argv[1]); //Conversion de la cadena de la consola a numero
	
	//Asignacion de memoria dinamica para el arreglo de numeros a ordenar
	if ((arreglo = malloc(sizeof(int) * numero)) == NULL) //asignacion dinamica para el arreglo de numeros
		perror("No se concreto la asignacion de memoria para 'arreglo'");
	
	//Llenado del arreglo
	for (i = 0; i < numero; i++)
		scanf("%d", &arreglo[i]);

	//*****************************************************************
	
	//INICIAR EL CONTEO DEL TIEMPO PARA LAS EVALUACIONES DE RENDIMIENTO	
	uswtime(&utime0, &stime0, &wtime0);
	
	//ALGORITMO	
	//Llamada a la función del algoritmo
	quick_sort(arreglo, 0, numero - 1); //llamada de la función, recibe el arreglo, pos inicial y pos final

	//EVALUAR LOS TIEMPOS DE EJECUCIÓN 
	uswtime(&utime1, &stime1, &wtime1);

	//Comprobar números ordenados (imprimir arreglo ordenado)
	/*for(i=0; i<n; i++)
		printf("%d\n", datos[i]);
	
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

/*FUNCIÓN QUE EJECUTA EL ORDENAMIENTO QUICK SORT*/
/* Recibe: Arreglo de enteros A[], posición inicial del arreglo p (que será el pivote inicial), y la ultima posición del arreglo (fin)*/
/* Devuelve: void */
void quick_sort(int A[], int p, int fin) {
	int j;
	if (p < fin) {
		j = pivote(A, p, fin);	   //Ordena con repecto al pivote inicial
		quick_sort(A, p, j - 1);   //Ordena los elementos menores al pivote inicial
		quick_sort(A, j + 1, fin); // Ordeno los elementos mayores al pivote final
	}
}

/*FUNCIÓN QUE RELIZA LAS COMPARACIONES RESPECTO AL PIVOTE*/
/* Recibe: Arreglo de enteros A[], posición inicial del arreglo p (que será el pivote inicial), y la ultima posición del arreglo (fin)*/
/* Devuelve: entero j (posición del arreglo en j) */
int pivote(int A[], int p, int fin) {
	int piv, i, j;
	piv = A[p]; //Asignacion del pivote
	i = p + 1;	//Asignacion del indice i que se recorre al buscar numeros menores al pivote
	j = fin;	//Asignacion del indice j que se recorre al buscar numeros mayores al pivote
	while (1) 	{
		//Cuando el valor del arreglo leido sea menor al pivote y el indice i sea menor al final del arreglo
		while (A[i] <= piv && i < fin) 	{
			i++; //Continua con el siguiente valor del arreglo
		}
		//Cuando el valor del arreglo leido sea mayor al pivote
		while (A[j] > piv) 	{
			j--; //Continua con el anterior valor del arreglo
		}
		//Si el indice i es menor al indice j
		if (i < j)	{
			swap(A, i, j); //Intercambia los valores encontrados
		}
		// si no
		else {
			swap(A, p, j); //el pivote s eintercambia por el valor de la posicion de j

			return j; //regresa la posicion de j
		}
	}
}

/*FUNCIÓN QUE REALIZA EL INTERCAMBIO DE LOS VALORES EN EL ARREGLO*/
/* Recibe: Arreglo de enteros A[], entero i (primer valor a intercambiar) y entero j (segundo valor a intercambiar)*/
/* Devuelve: entero */
int swap(int A[], int i, int j) {
	int temp = A[j]; //almacenamiento de A[j] en una variable temporal
	A[j] = A[i];	 // El valor de i es asignado a j
	A[i] = temp;	 //El valor de j es asignado a i
}