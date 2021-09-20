#!/bin/bash
#Compilacion de programas 
gcc bubble_sort.c tiempo.c -o bubble
gcc bubble_sort_op1.c tiempo.c -o bubble1
gcc bubble_sort_op2.c tiempo.c  -o bubble2
gcc insertion_sort.c tiempo.c -o insertion
gcc selection_sort.c tiempo.c -o selection
gcc shell_sort.c tiempo.c -o shell
gcc tree_sort.c tiempo.c -o tree
gcc merge_sort.c tiempo.c -o merge
gcc quick_sort.c tiempo.c -o quick

n=(100 1000 2500 5000 6500 7500 40000 50000 60000 70500 100000 120500 190600 200000 250000 300000 350000 400000 450000 500000)

#Ejecucigon
for q in ${n[@]}
do
./quick $q < numeros10millones.txt >> punto4Quick.txt
done
for m in ${n[@]}
do
./merge $m < numeros10millones.txt >> punto4Merge.txt
done
for t in ${n[@]}
do
./tree $t < numeros10millones.txt >> punto4Tree.txt
done
for s in ${n[@]}
do
./shell $s < numeros10millones.txt >> punto4Shell.txt
done
for i in ${n[@]}
do
./insertion $i < numeros10millones.txt >> punto4Insrt.txt
done
for sel in ${n[@]}
do
./selection $sel < numeros10millones.txt >> punto4Select.txt
done
for n2 in ${n[@]}
do
./bubble2 $n2 < numeros10millones.txt >> punto4Bubb2.txt
done
for n1 in ${n[@]}
do
./bubble1 $n1 < numeros10millones.txt >> punto4Bubb1.txt
done
for n in ${n[@]}
do
./bubble $n < numeros10millones.txt >> punto4Bubbl.txt
done

