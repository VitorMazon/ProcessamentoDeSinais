#!/bin/bash
#
# VitorMazon
#

#Obtém o número de linhas do arquivo
#N=$(wc -l curva.dat | cut -d c -f1)

gcc filtro.c -lm
./a.out > filtro30.dat
mv janelamento.dat janelamento30.dat
mv impulso.dat impulso30.dat
#./prog 70 > test.dat
#mv janelamento.dat janelamento70.dat
#mv impulso.dat impulso70.dat
#./prog 200 > test.dat
#mv janelamento.dat janelamento200.dat
#mv impulso.dat impulso200.dat
rm janelamento.dat
rm impulso.dat
