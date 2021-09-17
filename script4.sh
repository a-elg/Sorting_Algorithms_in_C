#!/bin/bash
#Compilacion de programas 
#gcc bubble_sort.c tiempo.c-o bubble
#gcc gcc bubble_sort_op1.c tiempo.c -o bubble1
#gcc gcc bubble_sort_op2.ctiempo.c  -o bubble2
gcc insertion_sort.c tiempo.c -o insertion
#gcc selection_sort.c tiempo.c -o selection
#gcc shell_sort.c tiempo.c -o shell
#gcc tree_sort.c tiempo.c -o tree
#gcc merge_sort.c tiempo.c -o merge
#gcc quick_sort.c tiempo.c -o quick

n=(100 1000 5000 10000 50000 100000 200000 400000 600000 800000 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000)

#Ejecucion
for n in ${n[@]}
do
./quick $n < numeros10millones.txt >> punto4Quick.txt
./insertion $n < numeros10millones.txt >> punto4Insrt.txt
./merge $n < numeros10millones.txt >> punto4Merge.txt
./shell $n < numeros10millones.txt >> punto4Shell.txt
./tree $n < numeros10millones.txt >> punto4Tree.txt
./bubble1 $n < numeros10millones.txt >> punto4Bubb1.txt
./bubble $n < numeros10millones.txt >> punto4Bubbl.txt
./bubble2 $n < numeros10millones.txt >> punto4Bubb2.txt
./selection $n < numeros10millones.txt >> punto4Select.txt
done
