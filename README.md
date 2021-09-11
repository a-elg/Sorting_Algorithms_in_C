# Algoritmos de Ordenamiento

## Descripción: 
Se presentan 9 algoritmos de ordenamiento (7 más 2 optimizaciones de uno).
Para evaluar los algoritmos se colocaron banderas para medir el tiempo de ejecución, así mismo se cuenta con un archivo con números aleatorios llamado numeros10millones.txt, del cual se extraen diversas cantidades de números para probar en cada algoritmo.

## Requerimientos
1. Compilar y ejecutar en sistemas UNIX (Linux/MacOS)
1. Compilador gcc

## Instrucciones
1. Descargar el archivo del algoritmo deseado
1. En la misma carpeta donde se encuentre ese archivo, colocar los siguientes archivos:
    1. tiempo.c
    1. tiempo.h
    1. numeros10millones.txt
1. Compilar librerías y archivo principal:
    1. `gcc -c tiempo.c`
    1. `gcc <algortimo>_sort.c tiempo.o -o <algortimo>_sort`
1. Ejecutar el archivo principal: `./<algortimo>_sort <número de valores a recolectar del archivo numeros10millones.txt> < numeros10millones.txt`
