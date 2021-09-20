#!/bin/bash
#Compilacion de programas 
gcc bubble_sort.c tiempo.c-o bubble
gcc gcc bubble_sort_op1.c tiempo.c -o bubble1
gcc gcc bubble_sort_op2.ctiempo.c  -o bubble2
gcc insertion_sort.c tiempo.c -o insertion
gcc selection_sort.c tiempo.c -o selection
gcc shell_sort.c tiempo.c -o shell
gcc tree_sort.c tiempo.c -o tree
gcc merge_sort.c tiempo.c -o merge
gcc quick_sort.c tiempo.c -o quick
#Ejecucion
./quick 500000 < numeros10millones.txt >> punto3.txt
./insertion 500000 < numeros10millones.txt >> punto3.txt
./bubble 500000 < numeros10millones.txt >> punto3.txt
./bubble1 500000 < numeros10millones.txt >> punto3.txt
./bubble2 500000 < numeros10millones.txt >> punto3.txt
./selection 500000 < numeros10millones.txt >> punto3.txt
./shell 500000 < numeros10millones.txt >> punto3.txt
./tree 500000 < numeros10millones.txt >> punto3.txt
./merge 500000 < numeros10millones.txt >> punto3.txt