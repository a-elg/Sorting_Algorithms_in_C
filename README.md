###Algoritmos de Ordenamiento

##Descripción: 
Se presentan 9 algoritmos de ordenamiento (7 más 2 optimizaciones de uno).
Para evaluar los algoritmos se colocaron banderas para medir el tiempo de ejecución, así mismo se cuenta con un archivo con números aleatorios llamado numeros10millones.txt, del cual se extraen diversas cantidades de números para probar en cada algoritmo.

##Requerimientos
Compilar y ejecutar en sistemas UNIX (Linux/MacOS)
Compilador gcc

##Instrucciones
1.Descargar el archivo del algoritmo deseado
2.En la misma carpeta donde se encuentre ese archivo, colocar los siguientes archivos:
    a)tiempo.c
    b)tiempo.h
    c)numeros10millones.txt
3.Compilar librerías y archivo principal:
    a)`gcc -c tiempo.c`
    b)`gcc <algortimo>_sort.c tiempo.o -o <algortimo>_sort`
4.Ejecutar el archivo principal: `./<algortimo>_sort <número de valores a recolectar del archivo numeros10millones.txt> < numeros10millones.txt`
