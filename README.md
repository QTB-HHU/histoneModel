# Modelling histone gene expression during DNA replication

This repository provides the source code with which the simulations presented in the manuscript
"MODELING ROBUST FEEDBACK CONTROL MECHANISMS THAT ENSURE RELIABLE COORDINATION OF HISTONE GENE EXPRESSION WITH DNA REPLICATION" by 
Christopher, Hameister, Corrigal, Ebenhöh, Müller and Ullner (exact reference will be provided soon) have been performed.

All software is provided as is without any warranty. All software is published under the Gnu Public Licence 3.0 (see LICENSE)
and is free to by used and modified in any way. If used or modified, please cite the above publication.



## Instructions 

The files are organised in three folders.

### The simple model, folder `basic_Fig2`

The C-programs generate the data as shown in Figure 2. The parameter are set as in the paper and the supplementary material stated. The program basic_histone_reg.c generates the data of the basic histone feedback loop model under normal S-phase condition and the other C-program basic_DNA_reg.c generates the data for the alternative model, the basic DNA coupled model under normal S-phase conditions.

The user will need a C-compiler, e.g. `gcc` and must compile the code, e.g.:

```
gcc -O3 basic_histone_reg.c -o basic_histone_reg.x -lm
```
(histone feedback loop model)

```
gcc -O3 basic_DNA_reg.c -o basic_DNA_reg.x -lm 
```
(DNA coupled model)

Running the programs `*.x` result in four data files:

```
 zr_all.dat
 par.dat
 flux.dat
 netflux.dat
```

containing time series for the dynamical variables, the parameter, the fluxes and the net fluxes, respectively. Please note, running the programs will replace the previous results and both programs write into the same file, i.e. will replace results each other.

The data file can be plotted with e.g. gnuplot and the three included scripts

```
 gnuplot multiplot_flux.gnu
 gnuplot multiplot_netflux.gnu 
 gnuplot multiplot5.gnu
```

generate postscript files:

```
histon_flux.ps
histon_netflux.ps
histon5.ps
```

All in one run in a command line in the terminal with ghost script to show the resulting postscript files:

histone feedback loop model:

```
rm basic_histone_reg.x ; gcc -O3 basic_histone_reg.c -o basic_histone_reg.x -lm ; ./basic_histone_reg.x; gnuplot multiplot_flux.gnu ; gv histon_flux.ps & gnuplot multiplot_netflux.gnu ; gv histon_netflux.ps & gnuplot multiplot5.gnu ; gv histon5.ps&  
```


DNA coupled model:

```
rm basic_DNA_reg.x ; gcc -O3 basic_DNA_reg.c -o basic_DNA_reg.x -lm ; ./basic_DNA_reg.x; gnuplot multiplot_flux.gnu ; gv histon_flux.ps & gnuplot multiplot_netflux.gnu ; gv histon_netflux.ps & gnuplot multiplot5.gnu ; gv histon5.ps& 
```

or use the following bash scripts for the same commands:

```
run_histone_basic.sh

run_DNA_basic.sh
```

### Inhibiting DNA replication - folder `basic_block_Fig3`

The C-programs in this folder generate the data as shown in Figure 3 and resemble the numerical results of the block experiments (inhibition of DNA synthesis during S-phase). The parameters are set as stated in the paper and the supplementary material. The block happens at time point `t=15000 s`.

The four C-programs

```
basic_V5block_histone_reg.c
basic_V5block_DNA_reg.c
basic_V1block_histone_reg.c
basic_V1block_DNA_reg.c
```

generate data for the V5 block in the histone feedback loop and DNA coupled model and the V1 in both models. Compilation and plotting is organised as for the basic models with normal S-phase (Figure 2). The auxiliary gnuplot scripts are included in the folder. The four bash scripts can be used to compile the C-programs, run the simulations, generate the postscript files with gnuplot and open the ps-files with ghostview.

```
run_histone_V5block.sh
run_DNA_V5block.sh
run_histone_V1block.sh
run_DNA_V1block.sh
```

Please note, running the programs will replace the previous results. All four programs write into the same file, i.e. will replace results each other.

Please note the V1 block simulations require a significant shorter integration step as predefined in the C programs. The programs run significant longer than the V5 block simulation and the simulations in the other folders. For further simulations the simple Euler algorithm should be replaced by more sophisticated routine. We kept the simple and not optimal Euler routine to preserve the same structure and routine in all provided codes.

### Extended model with 3 genes - folder `3gene_Fig5`

The C-programs generate the data as shown in Figure 5 B and C. The parameter are set as in the paper and the supplementary material stated. The program `3gene_histone_reg.c` generates the data of the extended histone feedback loop model under normal S-phase condition and the other C-program `3gene_DNA_reg.c` generates the data for the alternative model, the extended DNA coupled model under normal S-phase conditions.

The user will need a C-compiler, e.g. `gcc` and must compile the code, e.g.:

```
gcc -O3 3gene_histone_reg.c -o 3gene_histone_reg.x -lm
```
(histone feedback loop model)

```
gcc -O3 3gene_DNA_reg.c -o 3gene_DNA_reg.x -lm
```
(DNA coupled model)

Running the programs *.x result in four data files:

```
 zr_all.dat
 par.dat
 flux.dat
 netflux.dat
```

containing time series for the dynamical variables, the parameter, the fluxes and the net fluxes, respectively. Please note, running the programs will replace the previous results and both programs write into the same file, i.e. will replace results each other.

The data file can be plotted with e.g. gnuplot and the three included scripts

```
multiplot_flux_plasmid.gnu
multiplot_netflux_plasmid.gnu 
multiplot5_plasmid.gnu
```

generate postscript files:

```
histon_flux.ps
histon_netflux.ps
histon5.ps
```


All in one run in a command line in the terminal with ghost script to show the resulting postscript files:

histone feedback loop model:

```
rm 3gene_histone_reg.x ; gcc -O3 3gene_histone_reg.c -o 3gene_histone_reg.x -lm ; ./3gene_histone_reg.x; gnuplot multiplot_flux_plasmid.gnu ; gv histon_flux.ps & gnuplot multiplot_netflux_plasmid.gnu ; gv histon_netflux.ps & gnuplot multiplot5_plasmid.gnu ; gv histon5.ps& 
```

DNA coupled model:

```
rm 3gene_DNA_reg.x ; gcc -O3 3gene_DNA_reg.c -o 3gene_DNA_reg.x -lm ; ./3gene_DNA_reg.x; gnuplot multiplot_flux_plasmid.gnu ; gv histon_flux.ps & gnuplot multiplot_netflux_plasmid.gnu ; gv histon_netflux.ps & gnuplot multiplot5_plasmid.gnu ; gv histon5.ps& 
```

or use the following bash scripts for the same commands:

```
run_histone_3gene.sh

run_DNA_3gene.sh
```
