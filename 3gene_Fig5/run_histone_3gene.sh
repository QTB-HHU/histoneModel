rm 3gene_histone_reg.x ; gcc -O3 3gene_histone_reg.c -o 3gene_histone_reg.x -lm ; ./3gene_histone_reg.x; gnuplot multiplot_flux_plasmid.gnu ; gv histon_flux.ps & gnuplot multiplot_netflux_plasmid.gnu ; gv histon_netflux.ps & gnuplot multiplot5_plasmid.gnu ; gv histon5.ps&

