rm basic_DNA_reg.x ; gcc -O3 basic_DNA_reg.c -o basic_DNA_reg.x -lm ; ./basic_DNA_reg.x; gnuplot multiplot_flux.gnu ; gv histon_flux.ps & gnuplot multiplot_netflux.gnu ; gv histon_netflux.ps & gnuplot multiplot5.gnu ; gv histon5.ps& 