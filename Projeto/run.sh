#!/bin/bash
#
# VitorMazon
#

#Obtém o número de linhas do arquivo
N=$(wc -l curva.dat | cut -d c -f1)

gcc filtro.c -o prog
./prog $N > test.dat

