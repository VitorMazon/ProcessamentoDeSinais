set terminal pdf enhanced font "Times New Roman"
unset key
set grid
set xlabel "Frequência"
set ylabel "Amplitude"
set title "Sinal de entrada"
set xrange [0:]
set output "Entrada.pdf"

plot "curva.dat" w l
set output


set xlabel "Amostra"
set output "fft.pdf"
set xrange [*:2200]
set yrange [-0.01:]
set title "Impulso (domínio tempo)"

plot "fft.dat" w l
set output
