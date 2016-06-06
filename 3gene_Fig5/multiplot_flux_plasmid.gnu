set term post port color solid 12
set out 'histon_flux.ps'
set multiplot
set size 1.0, 0.2
set grid
#set nokey


set pointsize 0.5
#set linestyle 1 lt 7 lw 3 pt 6 ps 1.0

set xlabel 'time'
set ylabel 'variable(t)'

#set format y "%.3f"
#set format y ""

#set xrange [0.05: 0.25]
#set yrange [0.0:.4]
set mxtics 3
set mytics 2
#set xtics ("0.06" 0.06, "8" 0.08, "0.1" 0.1, "" 0.12, "0.14" 0.14,\
           "" 0.16, "0.18" 0.18, "" 0.2, "0.22" 0.22, "" 0.24)

#set xtics ("6" 0.06, "8" 0.08, "10" 0.1, "12" 0.12, "14" 0.14,\
           "16" 0.16, "18" 0.18, "20" 0.2, "22" 0.22, "24" 0.24)
#set xtics ("1000" 1000, "2000" 2000, "3000" 3000, "4000" 4000, "5000" 5000)

set origin 0.0,0.0;  plot [0:60000] [] "flux.dat" u 1:2 w l title "f1e2b", "flux.dat" u 1:3 w l title "f1p2b", "flux.dat" u 1:4 w l title "f1e3", "flux.dat" u 1:5 w l title "f2e2b", "flux.dat" u 1:6 w l title "f2p2b", "flux.dat" u 1:7 w l title "f2e3";
set origin 0.0,0.2;  plot [0:60000] [] "flux.dat" u 1:8 w l title "f3e2b", "flux.dat" u 1:9 w l title "f3p2b", "flux.dat" u 1:10 w l title "f3e3";
set origin 0.0,0.4;  plot [0:60000] [] "flux.dat" u 1:11 w l title "f4e2b", "flux.dat" u 1:12 w l title "f4p2b", "flux.dat" u 1:13 w l title "f4e3";
set origin 0.0,0.6;  plot [0:60000] [] "flux.dat" u 1:14 w l title "f5"; 
set origin 0.0,0.8;  plot [0:60000] [] "flux.dat" u 1:15 w l title "f6e", "flux.dat" u 1:16 w l title "f6p"; 


#pause -1

#set size 1.2, 0.6

replot

