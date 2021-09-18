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
#include <sys/resource.h>
#include "tiempo.h"
//*****************************************************************

//DEFINICION DE CONSTANTES DEL PROGRAMA
#define MAX 10000000
//*****************************************************************

//DECLARACION DE ESTRUCTURAS
struct nodo_arbol{ //Cada nodo tiene 2 hijo, un valor y un padre
    int valor;
    struct nodo_arbol *h_derecho;
    struct nodo_arbol *h_izquierdo;
    struct nodo_arbol *padre;
};typedef struct nodo_arbol nodo;
//*****************************************************************

//VARIABLES GLOBALES
int datos[MAX];//Arreglo de datos
int n; 	//n determina el tamaño del algorito dado por argumento al ejecutar
nodo *raiz; //raiz del árbol
//*****************************************************************

//DECLARACIÓN DE FUNCIONES (PROTOTIPOS)
/*prototipo para la función que crea un nodo (hoja) para ser insertado*/
nodo* crearNodo(int dato); 
/*prototipo para la función que inserta un valor en el árbol*/
void insertar(int dato); 
/*prototipo para la función que trasfiere los datos del árbol al arreglo original*/
void arbol_a_arreglo(); 
//*****************************************************************

//PROGRAMA PRINCIPAL 
int main (int argc, char* argv[]){	
	//Variables del main
	int numero;//Variable receptora de los números en el archivo 10millones.txt
	//Variables para medición de tiempos	
	double utime0, stime0, wtime0,utime1, stime1, wtime1; 
    //Variables para loops
	int i; 

	/* RECEPCIÓN Y DECODIFICACIÓN DE ARGUMENTOS */
	//Condicional *if* se ejecuta en caso de no introducirse exactamente 2 argumentos (Cadena de ejecución y cadena=n)
	if (argc!=2){
		printf("\nIndicar el tamanio del algoritmo, por favor - Ejemplo: [user@equipo]$ %s 100 < numeros10millones.txt\n",argv[0]);
		exit(1);
	} else //Tomar el segundo argumento como tamaño del algoritmo
		n=atoi(argv[1]);

	for(i=0;i<n;i++){
        scanf("%u",&numero);
        datos[i]=numero;
    }
	//*****************************************************************
	
	//INICIAR EL CONTEO DEL TIEMPO PARA LAS EVALUACIONES DE RENDIMIENTO	
	uswtime(&utime0, &stime0, &wtime0);
	
	//ALGORITMO	
	//Llamada a la función del algoritmo
	raiz=crearNodo(datos[0]);
    for (int i=1;i<n;i++){
        insertar(datos[i]);
    }
    arbol_a_arreglo(); 
    
	//EVALUAR LOS TIEMPOS DE EJECUCIÓN 
	uswtime(&utime1, &stime1, &wtime1);
	
    
	//Comprobar números ordenados (imprimir arreglo ordenado)
	/*for(i=0; i<n; i++)
		printf("%d\n", datos[i]);
	
	//Cálculo del tiempo de ejecución del programa
	/*printf("\n");
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
    */
    printf("Tree %15.10e  %21.10e %21.10e %21.10f%%\n", wtime1 - wtime0,utime1 - utime0,stime1 - stime0,100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	//Terminar programa normalmente	
	exit (0);	
}

//DEFINICIÓN DE FUNCIONES 
//************************************************************************

/*FUNCIÓN QUE CREA UN NODO (hoja) PARA SER INSERTADO*/
/* Recibe: entero dato*/
/* Devuelve: apuntador de tipo nodo */
nodo* crearNodo(int dato){
    //Apartar espacio para un nuevo nodo
    nodo *nuevo_nodo=(nodo*)malloc(sizeof(nodo));

    //Inicializamos los valores del nodo
    nuevo_nodo->valor=dato;
    nuevo_nodo->h_derecho=NULL;
    nuevo_nodo->h_izquierdo=NULL;
    nuevo_nodo->padre=NULL;

    //Regresar la dirección apartada
    return nuevo_nodo;
}

/*FUNCIÓN QUE INSERTA UN VALOR EN EL ÁRBOL*/
/* Recibe: entero dato*/
/* Devuelve: vacío */
void insertar(int dato){
    nodo*aux=raiz;
    nodo*nuevo_nodo=crearNodo(dato);
    while (1){
        if(dato>aux->valor){//¿El dato es estrictamente mayor que el del nodo en revisón?
            if(aux->h_derecho){//¿Tiene hijo derecho?
                aux=aux->h_derecho;//Repetir el ciclo, pero iniciando desde el hijo derecho
                continue;
            }
            else{//No tiene hijo derecho
                //Al nuevo nodo, conectarlo con una hoja, tanto de padre a hijo, como de hijo a padre
                aux->h_derecho=nuevo_nodo;
                nuevo_nodo->padre=aux;
                break;
            }
        }
        else{//El dato es menor o igual al dato del nodo en revisión
            if(aux->h_izquierdo){//¿Tiene hijo izquierdo?
                aux=aux->h_izquierdo;//Repetir el ciclo, pero iniciando desde el hijo izquierdo
                continue;
            }
            else{//No tiene hijo izquierdo
                //Al nuevo nodo, conectarlo con una hoja, tanto de padre a hijo, como de hijo a padre
                aux->h_izquierdo=nuevo_nodo;
                nuevo_nodo->padre=aux;
                break;
            }
        }
    }
    
}

/*FUNCIÓN QUE TRANSFIERE LOS DATOS DEL ÁRBOL AL ARREGLO ORIGINAL*/
/* Recibe: vacío*/
/* Devuelve: vacío */
void arbol_a_arreglo(){
    int indice_arreglo=0;
    int val_hijo;//Valor para identificar al hijo que se eliminará
    nodo*aux=raiz;
    while (indice_arreglo<n){
        //Recorrer lo más a la izquierda posible (el más chico) y repetir el proceso
        if(aux->h_izquierdo){
            aux=aux->h_izquierdo;
            continue;
        }
        
        //Se llegó al nodo más a la izquierda, guardar su dato e incrementar el índice del arreglo original
        if(aux->valor>0){//Si el valor es negativo, significa que ya lo habíamos registrado
            datos[indice_arreglo]=aux->valor;
            indice_arreglo++;
            aux->valor*=-1;//Marcar que ya se registró el dato
        }
        else{
            //Eliminar conexión entre padre e hijo
            if((aux->padre->h_izquierdo)&&(aux->padre->h_izquierdo->valor==aux->valor))
                aux->padre->h_izquierdo=NULL;
            else
                aux->padre->h_derecho=NULL;
            aux=aux->padre;  
            continue;  
        }

        //Dirigirse al primer nodo de la derecha (más grande que el actual) y repetir el proceso
        if(aux->h_derecho){
            aux=aux->h_derecho;
            continue;
        }
        
        //Eliminar conexión entre padre e hijo
        if((aux->padre->h_izquierdo)&&(aux->padre->h_izquierdo->valor==aux->valor))
            aux->padre->h_izquierdo=NULL;
        else
            aux->padre->h_derecho=NULL;

        aux=aux->padre;    
    }
}
