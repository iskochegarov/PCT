#!/usr/bin/gnuplot
set terminal png size 800,480 enhanced font 'Arial, 16'
set output 'QS_1m_bt.png'

set style line 1 linecolor rgb 'red' linetype 1 linewidth 2
set style line 2 linecolor rgb 'blue' linetype 1 linewidth 2
set style line 3 linecolor rgb 'green' linetype 1 linewidth 2
set style line 4 linecolor rgb 'black' linetype 1 linewidth 2

set border linewidth 1
set key top left
set grid
set mytics 0
set format y "%.1f"
set xlabel "Threads \n\n QuickSort \n n = 1.000.000" font "Arial, 16"
set format x "%.0f" 
set ylabel "Speedup" font "Arial, 16"
set xtics font "Arial, 12"
set ytics font "Arial, 12"
set rmargin 4
set tmargin 2 
set mxtics

plot "1m10k.dat" using 1:2 title "Threashold = 10000" with linespoints ls 1,\
     "1m25k.dat" using 1:2 title "Threashold = 25000" with linespoints ls 2,\
     "1m40k.dat" using 1:2 title "Threashold = 40000" with linespoints ls 3,\
     "linear.dat" using 1:2 title "Linear Speedup" with linespoints ls 4,
      
     