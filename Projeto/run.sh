#!/bin/bash
#
# VitorMazon
#

#Obtém o número de linhas do arquivo
#N=$(wc -l curva.dat | cut -d c -f1)

gcc filtro.c -lm -o prog
./prog 20 > filtro20.dat
mv janelamento.dat janelamento20.dat
mv impulso.dat impulso20.dat
#./prog 70 > test.dat
#mv janelamento.dat janelamento70.dat
#mv impulso.dat impulso70.dat
#./prog 200 > test.dat
#mv janelamento.dat janelamento200.dat
#mv impulso.dat impulso200.dat
rm janelamento.dat
rm impulso.dat
