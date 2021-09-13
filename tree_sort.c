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
#include <string.h>
#include "tiempo.h"
//*****************************************************************
//DEFINICION DE CONSTANTES DEL PROGRAMA
//*****************************************************************
#define MAX 10000000
//********************************************************************************
//DECLARACION DE ESTRUCTURAS
//********************************************************************************
struct nodo_arbol{
    int valor;
    struct nodo_arbol *h_derecho;
    struct nodo_arbol *h_izquierdo;
}; typedef struct nodo_arbol nodo;
/*
    Árbol:
        a
       / \
     b    c

    b<=a
    c>a
*/
//*****************************************************************
//VARIABLES GLOBALES
//*****************************************************************
int datos[MAX];
int n; 	//n determina el tamaño del algorito dado por argumento al ejecutar
//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
void tree_sort();
nodo* inicializar(int dato);
void insertar(int dato,nodo* raiz);
void arbol_a_arreglo(nodo *raiz,int *indice);
//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************
int main (int argc, char* argv[])
{	
	//******************************************************************	
	//Variables del main
	//******************************************************************	
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	int i; //Variables para loops
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
		n=atoi(argv[1]);

	for(i=0;i<n;i++)
        scanf("%d",&datos[i]);
	//******************************************************************	
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	//******************************************************************	
	uswtime(&utime0, &stime0, &wtime0);
	//******************************************************************
	
	//******************************************************************	
	//Algoritmo
	//******************************************************************	
	tree_sort();
	//******************************************************************

	//******************************************************************	
	//Evaluar los tiempos de ejecución 
	//******************************************************************
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
	//******************************************************************

	//Terminar programa normalmente	
	exit (0);	
}

//************************************************************************
//DEFINICIÓN DE FUNCIONES 
//************************************************************************

void tree_sort(){
    //Tomamos el primer número como raíz
    nodo *raiz=inicializar(datos[0]);

    //Empecamos a insertar el resto de los números
    for(int i=1;i<n;i++)
        insertar(datos[i],raiz);

    int aux=0;//Variable que se pasa por referencia para poder ser editable en diversas llamadas de la misma funcíón
    arbol_a_arreglo(raiz,&aux);//Traspasar el arbol al arreglo original, pero ya con orden de menor a mayor

    //Imprimir el arreglo ya ordenado
    //for(int i=0;i<n;i++)
    //    printf("%d\n",datos[i]);
}

nodo* inicializar(int dato){
    //Apartar espacio para un nuevo nodo
    nodo *nuevo_nodo=(nodo*)malloc(sizeof(nodo));

    //Inicializamos los valores del nodo
    nuevo_nodo->valor=dato;
    nuevo_nodo->h_derecho=NULL;
    nuevo_nodo->h_izquierdo=NULL;

    //Regresar la dirección apartada
    return nuevo_nodo;
}

void insertar(int dato,nodo* raiz){
    if(dato>raiz->valor)//¿El dato es estritamente mayor que el del nodo en revisón?
        if(raiz->h_derecho==NULL){//¿No tiene hijo derecho?
            //Crear un nuevo nodo e inicializarlo
            nodo *nuevo_nodo=(nodo*)malloc(sizeof(nodo));
            nuevo_nodo->valor=dato;
            nuevo_nodo->h_derecho=NULL;
            nuevo_nodo->h_izquierdo=NULL;
            raiz->h_derecho=nuevo_nodo;
        }
        else//Sí tiene hijo derecho
            insertar(dato,raiz->h_derecho);//Repetir el ciclo, pero iniciando desde el hijo derecho

    else//El dato es menor o igual al dato del nodo en revisión
        if(raiz->h_izquierdo==NULL){//¿No tiene hijo izquierdo?
            //Crear un nuevo nodo e inicializarlo
            nodo *nuevo_nodo=(nodo*)malloc(sizeof(nodo));
            nuevo_nodo->valor=dato;
            nuevo_nodo->h_derecho=NULL;
            nuevo_nodo->h_izquierdo=NULL;
            raiz->h_izquierdo=nuevo_nodo;
        }
        else//Sí tiene hijo izquierdo
            insertar(dato,raiz->h_izquierdo);//Repetir el ciclo, pero iniciando desde el hijo izquierdo
}

void arbol_a_arreglo(nodo *raiz,int *indice){
    //Recorrer lo más a la izquierda posible (el más chico) y repetir el proceso
    if(raiz->h_izquierdo)
        arbol_a_arreglo(raiz->h_izquierdo,indice);
    
    //Se llegó al nodo más a la izquierda, guardar su dato e incrementar el índice del arreglo original
    datos[*indice]=raiz->valor;
    (*indice)=(*indice)+1;

    //Dirigirse al primer nodo de la derecha (más grande que el actual) y repetir el proceso
    if(raiz->h_derecho)
        arbol_a_arreglo(raiz->h_derecho,indice);
}
