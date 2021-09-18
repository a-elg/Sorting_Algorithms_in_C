#!/bin/bash

#Compilación de programas
gcc bubble_sort.c tiempo.c -o bubble
gcc bubble_sort_op1.c tiempo.c -o bubble1
gcc bubble_sort_op2.c tiempo.c -o bubble2
gcc insertion_sort.c tiempo.c -o insertion
gcc selection_sort.c tiempo.c -o selection
gcc tree_sort.c tiempo.c -o tree
gcc shell_sort.c tiempo.c -o shell
gcc merge_sort.c tiempo.c -o merge
gcc quick_sort.c tiempo.c -o quick

#Ejecución de programas
./bubble 500000 < numeros10millones.txt > bubbleTimept3.txt
./bubble1 500000 < numeros10millones.txt > bubble1Timept3.txt
./bubble2 500000 < numeros10millones.txt > bubble2Timept3.txt
./insertion 500000 < numeros10millones.txt > insertionTimept3.txt
./selection 500000 < numeros10millones.txt > selectionTimept3.txt
./tree 500000 < numeros10millones.txt >> treeTimept3.txt
./shell 500000 < numeros10millones.txt > shellTimept3.txt
./merge 500000 < nume   ros10millones.txt > mergeTimept3.txt
./quick 500000 < numeros10millones.txt > quickTimept3.txt

#Ejecuctar script en bash como ./script.sh