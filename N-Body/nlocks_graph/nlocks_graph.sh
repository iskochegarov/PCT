#!/usr/bin/gnuplot
set terminal png size 800,480 enhanced font 'Arial, 16'
set output 'exp1.png'

set style line 1 linecolor rgb 'red' linetype 1 linewidth 2
set style line 2 linecolor rgb 'blue' linetype 1 linewidth 2
set style line 3 linecolor rgb 'green' linetype 1 linewidth 2

set border linewidth 1
set key top left
set grid
set mytics 0
set format y "%.2f"
set xlabel "Chunk" font "Arial, 16"
set format x "%.0f" 
set ylabel "Time (sec)" font "Arial, 16"
set xtics font "Arial, 12"
set ytics font "Arial, 12"
set rmargin 4
set tmargin 2
set mxtics 
set xrange [-10:520]
set xtics ( "" 0, "1" 1, "32" 32, "" 100, "" 200, "" 300, "" 400, "" 500, "512" 512) font "Arial, 12"

plot "static.dat" using 1:2 title "schedule static" with linespoints ls 1,\
     "dynamic.dat" using 1:2 title "schedule dynamic" with linespoints ls 2,\
     "guided.dat" using 1:2 title "schedule guided" with linespoints ls 3,
      
     