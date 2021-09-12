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
#define MAX 10000002
//********************************************************************************
//DECLARACION DE ESTRUCTURAS
//********************************************************************************
int arbol[MAX][3];
/*
Estructura del árbol:
Índices del árbol:        [0]     ,      [1]     ,      [2]     ,...,[i],...,[n-3],[n-2],[n-1]
Contendido del árbol:[[0],[1],[2]], [[0],[1],[2]], [[0],[1],[2]],...
Contenido de cada nodo en el árbol <<[[0],[1],[2]]>>:
    [0]:valor del nodo
    [1]:índice del hijo derecho
    [2]:índice del hijo izquierdo
Los hijos de la derecha son mayores o iguales a su padre, los de la derecha estrictamente menores a su  padre
*/
//*****************************************************************
//VARIABLES GLOBALES
//*****************************************************************
int datos[MAX];
int sig_espacio_disponible=0;
int n=0; 	//n determina el tamaño del algorito dado por argumento al ejecutar
//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
void tree_to_array();
void tree_insert();
void tree_sort();
//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************
int main (int argc, char* argv[])
{	
	//******************************************************************	
	//Variables del main
	int numero;//Variable receptora de los números en el archivo 10millones.txt
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

	for(i=0;i<n;i++){
        scanf("%u",&numero);
        datos[i]=numero;
    }
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
void tree_insert(int numero){
    //Valores dinámicos que describen a un nodo
    int indice_nodo_concurrente=0;
    while (1){
        if(numero>arbol[indice_nodo_concurrente][0]){//El nuevo valor es mayor al del nodo en revisión
            if(arbol[indice_nodo_concurrente][1]==-1){//¿El nodo en revisión no tiene hijo derecho?
                arbol[indice_nodo_concurrente][1]=sig_espacio_disponible;//Apuntar al siguiente espacio disponible
                arbol[sig_espacio_disponible][0]=numero;//Guardar en ese espacio el nuevo número
                arbol[sig_espacio_disponible][1]=-1;//Indicar que no tiene hijo derecho
                arbol[sig_espacio_disponible][2]=-1;//Indicar que no tiene hijo izquierdo
                sig_espacio_disponible++;
                break;//Se logró acomodar el número, terminar la función insert
            }
            //El nodo en revisión sí tiene un hijo derecho, por tanto, buscar lugar en la rama derecha
            indice_nodo_concurrente=arbol[indice_nodo_concurrente][1];
            continue;
        }
        else{//El nuevo valor es menor o igual al del nodo en revisión
            if(arbol[indice_nodo_concurrente][2]==-1){//¿El nodo en revisión no tiene hijo izquierdo?
                arbol[indice_nodo_concurrente][2]=sig_espacio_disponible;//Apuntar al siguiente espacio disponible
                arbol[sig_espacio_disponible][0]=numero;//Guardar en ese espacio el nuevo número
                arbol[sig_espacio_disponible][1]=-1;//Indicar que no tiene hijo derecho
                arbol[sig_espacio_disponible][2]=-1;//Indicar que no tiene hijo izquierdo
                sig_espacio_disponible++;
                break;//Se logró acomodar el número, terminar la función insert
            }
            //El nodo en revisión sí tiene un hijo izquierdo, por tanto, buscar lugar en la rama derecha
            indice_nodo_concurrente=arbol[indice_nodo_concurrente][2];
            continue;
        }
    }
}

void tree_to_array(){
    int trace_back[n+1];//Pila para registrar el camino recorrido hasta uno nodo dado un padre (registra índices del arreglo arbol)
    int indice_trace_back=0;//Índice que apunta al padre concurrente en el arreglo trace_back

    int indice_datos=0;//Índice del arreglo de datos (se rempazarán los datos anteriores con los del árbol)
    int padre_concurrente;//Variable auxiliar para evitar calcular trace_back[indice_trace_back] muchas veces
    int padre_anterior;//Variable auxiliar para evitar calcular trace_back[indice_trace_back-1] muchas veces

    trace_back[0]=0;//Meter la raíz del árbol a la pila
    while (1){

        padre_concurrente=trace_back[indice_trace_back];
        padre_anterior=trace_back[indice_trace_back-1];

        if(arbol[padre_concurrente][0]==-1){//Si el nodo ya ha sido revisado, omitir una 2da revisión
            if(indice_datos>=n)//¿Ya llenamos los datos?
                return;

            //Aun faltan datos que agregar
            if(arbol[padre_anterior][1]==padre_concurrente){//Si el hijo derecho del padre anterior = nodo en revisión
                arbol[padre_anterior][1]=-1;//cortar la rama derecha de ese padre
                arbol[padre_anterior][0]=-1;//indicar que el padre anterior se terminó de revisar
            }
            else//el hijo izquierdo del padre anterior = nodo en revisión
                arbol[padre_anterior][2]=-1;//cortar la rama izquierda de ese padre

            indice_trace_back--;//Regresar al nodo padre del que está en revisión
            continue;
        }

        if(arbol[padre_concurrente][2]!=-1){//¿El nodo tiene hijo izquierdo?
            trace_back[++indice_trace_back]=arbol[padre_concurrente][2];//Moverse a su hijo izquierdo
            continue;
        }
        //El nodo no tiene hijo izquierdo
        datos[indice_datos]=arbol[padre_concurrente][0];//devolver el dato del nodo en revisión 
        indice_datos++;//Moverse al siguiente nodo de "Datos" para remplazar su valor (si aplica) 

        if(arbol[padre_concurrente][1]!=-1){//¿El nodo tiene hijo derecho?
            trace_back[++indice_trace_back]=arbol[padre_concurrente][1];//Moverse a su hijo derecho
            continue;
        }

        //El nodo no tiene hijo derecho

        if(indice_datos>=n)//¿Ya llenamos los datos?
            return;

        arbol[padre_concurrente][0]=-1;
    }
}

void tree_sort(){
    //Organizar los datos en el árbol
        //Iniciamos el árbol con el primer dato de la lista
        arbol[sig_espacio_disponible][0]=datos[0];
        //Asignamos valores de índices imposibles como hijos de la raíz para indicar que no tiene hijos aun
        arbol[sig_espacio_disponible][1]=-1; arbol[sig_espacio_disponible][2]=-1;
        sig_espacio_disponible++;
        for(int i=1;i<n;i++)
            tree_insert(datos[i]);

    //Recolectar los datos en InOrden deontro de el arreglo original
        tree_to_array();
    //Imprimir el resultado final
        for(int i=0;i<n;i++){
            printf("%d\n",datos[i]);
        }
}