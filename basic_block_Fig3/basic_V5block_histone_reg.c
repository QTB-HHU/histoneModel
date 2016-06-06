/*   start with"    
rm basic_V5block_histone_reg.x ; gcc -O3 basic_V5block_histone_reg.c -o basic_V5block_histone_reg.x -lm ; ./basic_V5block_histone_reg.x; gnuplot multiplot_flux.gnu ; gv histon_flux.ps & gnuplot multiplot_netflux.gnu ; gv histon_netflux.ps & gnuplot multiplot5.gnu ; gv histon5.ps&   "*/

//   original name:  DNAcf_shist_v5expdyn2_Sondemand.c


#include <stdio.h>
#include <math.h>
// #include "nr.h"
#include <time.h>


long d,dd;
/*
//  only necessary for random number 
double gauss(){
double r;
r=(double)gasdev(&d);
return r;
}
*/

int main(){
long step,limit;
double Hold,Hnew,Mold,Mnew,Dold,Dnew;
double f1,f2,f3,f4,f5,f6; /*  all fluxes separately  */
double delta_t,current_time;
double S,Vtcmax,IY,n1,gambase,gamind,KY,n2,k3,delta,V5m,V5,k6;

double A0,A1,A2,A3,A4;    /*  histone binding sites (DNA) on off for experimental data   */
 double S0,S1,S2,S3,S4,S5,S6;
 double totnDNA;

 FILE *d1,*d2,*d3,*d4;

 /*
d=time(NULL);
d=-d;
d=d%1000;
 
 d=-93;
 dd=d;
*/

 /* INITIAL CONDITIONS */
 
 //  Mold=0.0;Hold=0.0;Dold=0.0;
 Mold=10.0;Hold=100.0;Dold=0.0;totnDNA=0.0;
 //Mold=100.0;Hold=100.0;Dold=100.0;

/*
 Hold=200.0*ran1(&d);
 Mold=100000*ran1(&d);
 Dold=10000*ran1(&d);
*/

 //printf("seed %ld\n",dd);
 printf("\nbasic histone feedback loop model, normal S-phase\n");
 printf("initial conditions: histon protein=%.2lf, histon mRNA=%.2lf, histone binding sites (DNA)=%.2lf, total new DNA=%.2lf\n",Hold,Mold,Dold,totnDNA);


/* PARAMETERS */

 //S=1.0;
 Vtcmax=15;
 //IY=1000.0;
 KY=1240;
 n1=1.0;
 gambase=0.00018;    /*   measured value   */
 // gambase=0.0002;  /* guessed/literature value */
 // gamind=0.001;  /* guessed/literature value */
 gamind=0.00067;    /*   measured value   */
 //KY=1000;
 IY=1240;
 n2=1.0;
 k3=1*1.0;
 delta=1*0.01;
 V5m=1200;
 k6=0.001;


//   data from 1h set for V5 (exp. 1)
A0=2470;      //  unit 1/s
A1=0.000361;  //  unit 1/s
A2=25200;     //  unit s
A3=0.00126;   //  unit 1/s
A4=-11500;    //  unit s


/*
//   data from 45 min set for V5 (exp. 2)
A0=1330;      //  unit 1/s
A1=0.00037;  //  unit 1/s
A2=36400;     //  unit s
A3=0.000833;   //  unit 1/s
A4=-10800;    //  unit s
*/

//  parameter to controll SLBP S
 S0=1.0;      //  unit 1/s
 //S1=0.00000004;   //  unit 1/s
 S1=0.0000003;   //  unit  1/#new DNA -  decay phase, DNA dependent 
 S2=29000000;   //   unit new DNA -  decay phase DNA, dependent 
 // S2=35000000;   //   unit s
 S3=0.001;   //  unit   1/s  -  rise phase, time dependent
 S4=-10000;   // unit s  -  rise phase, time depenedent
 
 S5=0.001; //  unit 1/s  -  decay phase, time depenendent
 S6=42000;  //   unit s  -  decay phase, time depenendent

 d1=fopen("zr_all.dat","w");
 d2=fopen("par.dat","w");
 d3=fopen("flux.dat","w");
 d4=fopen("netflux.dat","w");
 
 delta_t=0.01;
 
 limit=6000000;
 // limit=5400000;
 //limit=25000000;


 current_time=0.0;
 f1=0.0; f2=0.0; f3=0.0; f4=0.0; f5=0.0; f6=0.0;
 
 fprintf(d1,"%lf %lf %lf %lf %lf\n",current_time,Mold,Hold,Dold,totnDNA);  
 fprintf(d2,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",current_time,S,Vtcmax,IY,n1,gambase,gamind,KY,n2,k3,delta,V5,k6);  
 fprintf(d3,"%lf %lf %lf %lf %lf %lf %lf\n",current_time,f1,f2,f3,f4,f5,f6);  
 fprintf(d4,"%lf %lf %lf %lf\n",current_time,f1-f2,f3-f4-f6,f5-f6);
 
 for(step=1;step<=limit;step++){ /* start stepwise integration */
   if(step%(limit/10)==0)  printf("%ld from %ld\n",step,limit);  
  

    S = S0 / ((exp(S1*(totnDNA - S2))+1.0) * (exp(S5*(current_time - S6))+1.0) * (exp(S3*(-current_time - S4))+1.0));

   // S=S0;

   /* experimental V5  */

    V5 = A0 / ((exp(A1*(current_time - A2))+1.0)*(exp(A3*(-current_time - A4))+1.0));

    if(current_time>15000) V5=0.0;   //  HU block during S-phase


  /* all fluxes / velocities separately */  
   f1=S*Vtcmax/(1+pow((Hold/IY),n1));
   //  if(current_time>15000) f1=0.0;   //  ActD block during S-phase
   f2=(gambase+gamind*pow(Hold,n2)/(pow(KY,n2)+pow(Hold,n2)))*Mold;
   //f1=S*Vtcmax*pow(Dold,n1)/(pow(KY,n1)+pow(Dold,n1));
   //f2=(gambase+gamind/(1.0+pow(Dold/IY,n2)))*Mold;
   f3=k3*Mold;
   f4=delta*Hold;
   f5=V5;
   f6=k6*Hold*Dold;
   
   Mnew = Mold + (f1-f2)*delta_t;
   Hnew = Hold + (f3-f4-f6)*delta_t;
   Dnew = Dold + (f5-f6)*delta_t;
   totnDNA+=f6*delta_t;
 
   current_time+=delta_t;   

   Hold=Hnew;
   Mold=Mnew;
   Dold=Dnew;
  

   if(step%100==0){
     fprintf(d1,"%lf %lf %lf %lf %lf\n",current_time,Mnew,Hnew,Dnew,totnDNA);  
     fprintf(d2,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",current_time,S,Vtcmax,IY,n1,gambase,gamind,KY,n2,k3,delta,V5,k6);  
     fprintf(d3,"%lf %lf %lf %lf %lf %lf %lf\n",current_time,f1,f2,f3,f4,f5,f6);  
     fprintf(d4,"%lf %lf %lf %lf\n",current_time,f1-f2,f3-f4-f6,f5-f6);  
   }
 }    /* end stepwise integration */


 fclose(d1);
 fclose(d2);
 fclose(d3);
 fclose(d4);
}
