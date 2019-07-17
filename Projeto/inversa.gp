set terminal pdf enhanced font "Times New Roman"
unset key
set grid
set xlabel "Frequência"
set ylabel "Amplitude"
set xrange [0:]
set title "Sinal filrado para M=30"
set output "Filtro30.pdf"
plot "mag30.dat" w l
set output


set title "Sinal filtrado para M=70"
set output "Filtro70.pdf"
plot "mag70.dat" w l
set output


set title "Sinal filtrado para M=200"
set output "Filtro200.pdf"
plot "mag200.dat" w l
set output

set key left
set title "Comparação dos sinais filtrados"
set output "Magnitude.pdf"
plot "mag30.dat" w l lw 1.5 t "M=30", "mag70.dat" w l lw 1.5 t "M=70", "mag200.dat" w l lw 1.5 t "M=200"
set output
