set term post port color solid 12
set out 'histon5.ps'
set multiplot
set size 1.0, 0.17
set grid
#set nokey


set pointsize 0.5
#set linestyle 1 lt 7 lw 3 pt 6 ps 1.0

set xlabel 'time / sec'
set ylabel 'variable(t)'

#set format y "%.3f"
#set format y ""

#set xrange [0.05: 0.25]
#set yrange [0.0:.4]
set mxtics 2
set mytics 2
#set xtics ("0.06" 0.06, "8" 0.08, "0.1" 0.1, "" 0.12, "0.14" 0.14,\
           "" 0.16, "0.18" 0.18, "" 0.2, "0.22" 0.22, "" 0.24)

#set xtics ("6" 0.06, "8" 0.08, "10" 0.1, "12" 0.12, "14" 0.14,\
           "16" 0.16, "18" 0.18, "20" 0.2, "22" 0.22, "24" 0.24)
#set xtics ("1000" 1000, "2000" 2000, "3000" 3000, "4000" 4000, "5000" 5000)

set origin 0.0,0.0;  plot [0:30000] [] "par.dat" u 1:2 w l title "S";
set origin 0.0,0.16;  plot [0:30000] [] "par.dat" u 1:12 w l title "V5";
set origin 0.0,0.32;  plot [0:30000] [] "zr_all.dat" u 1:2 w l title "R";
set origin 0.0,0.48;  plot [0:30000] [] "zr_all.dat" u 1:($3/1000) w l title "H/1000"; 
set origin 0.0,0.64;  plot [0:30000] [] "zr_all.dat" u 1:4 w l title "D"; 
set origin 0.0,0.8;  plot [0:30000] [] "zr_all.dat" u 1:($5/10000000) w l title "T /10^7"; 


#pause -1

#set size 1.2, 0.6

replot

