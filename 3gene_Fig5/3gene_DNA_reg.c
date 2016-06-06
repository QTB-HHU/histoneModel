/*   start with"    
rm 3gene_DNA_reg.x ; gcc -O3 3gene_DNA_reg.c -o 3gene_DNA_reg.x -lm ; ./3gene_DNA_reg.x; gnuplot multiplot_flux_plasmid.gnu ; gv histon_flux.ps & gnuplot multiplot_netflux_plasmid.gnu ; gv histon_netflux.ps & gnuplot multiplot5_plasmid.gnu ; gv histon5.ps&   "*/

//   original name:   DNAreg_H2Ben_pl_H3_v5exp_Sondemand.c


#include <stdio.h>
#include <math.h>
//  #include "nr.h"
#include <time.h>


long d,dd;
/*
double gauss(){
double r;
r=(double)gasdev(&d);
return r;
}
*/

int main(){
long step,limit;
 double Me2bold,Me2bnew,Mp2bold,Mp2bnew,Me3old,Me3new;
 double He2bold,He2bnew,Hp2bold,Hp2bnew,He3old,He3new;
 double Dold,Dnew;
 double f1e2b,f1p2b,f1e3,f2e2b,f2p2b,f2e3,f3e2b,f3p2b,f3e3,f4e2b,f4p2b,f4e3,f5,f6e,f6p; /*  all fluxes separately  */
double delta_t,current_time;
 double S,Vme2b,Vmp2b,Vme3,IY,n1,gambase,gamind,KY,n2,k3,delta,V5m,V5,k6;
double A0,A1,A2,A3,A4;    /*  histone binding sites (DNA) on off for experimental data   */
 double S0,S1,S2,S3,S4,S5,S6;
 double totnDNAe,totnDNAp;
 double sumMe2b,sumMp2b,sumMe3,sumHe2b,sumHp2b,sumHe3;
 double sumHe2bfree,sumHp2bfree,sumHe3free;

 FILE *d1,*d2,*d3,*d4;

 /*
d=time(NULL);
d=-d;
d=d%1000;
 
 d=-93;
 dd=d;
*/

/* PARAMETERS */

 //S=1.0;
 Vme2b=15;
 // Vmp2b=0.05;
 Vmp2b=0.05;
 Vme3=Vme2b;
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
 // k6=0.001;
 k6=1.0/5000000;


//   data from 1h set for V5
A0=2470;      //  unit 1/s
A1=0.000361;  //  unit 1/s
A2=25200;     //  unit s
A3=0.00126;   //  unit 1/s
A4=-11500;    //  unit s

/*
//   data from 45 min set for V5
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
 //  S2=29000000;   //   unit new DNA -  decay phase DNA, dependent 
 S2=31000000;
 // S2=35000000;   //   unit s
 S3=0.001;   //  unit   1/s  -  rise phase, time dependent
 // S4=-10000;   // unit s  -  rise phase, time depenedent
 S4=-6000;   // unit s  -  rise phase, time depenedent

 S5=0.001; //  unit 1/s  -  decay phase, time depenendent
 // S6=42000;  //   unit s  -  decay phase, time depenendent
 S6=55000;  //   unit s  -  decay phase, time depenendent

 d1=fopen("zr_all.dat","w");
 d2=fopen("par.dat","w");
 d3=fopen("flux.dat","w");
 d4=fopen("netflux.dat","w");
 
 delta_t=0.01;
 
 // limit=6000000;
 limit=8640000;
 // limit=5400000;
 //limit=25000000;

 /* INITIAL CONDITIONS */
 Me2bold=10.0;
 // Mp2bold=278.0;
 // Mp2bold=55.56;
 Mp2bold=Vmp2b/gambase;
 Me3old=10.0;
 He2bold=100.0;
 // Hp2bold=27777.0;
 // Hp2bold=5555.55;
 Hp2bold=(k3*Vmp2b)/(gambase*delta);
 He3old=100.0;
 Dold=0.0;
 totnDNAe=0.0;
 totnDNAp=0.0;
 sumMe2b=0.0;sumMp2b=0.0;sumMe3=0.0;sumHe2b=0.0;sumHp2b=0.0;sumHe3=0.0;
 sumHe2bfree=0.0;sumHp2bfree=0.0;sumHe3free=0.0;

/*
 Hold=200.0*ran1(&d);
 Mold=100000*ran1(&d);
 Dold=10000*ran1(&d);
*/

 printf("seed %ld\n",dd);
 printf("initial conditions: endog. H2B histon protein=%.2lf, plasmid H2B histon protein=%.2lf, endog. H3 histon protein=%.2lf, endog. H2B histon mRNA=%.2lf, plasmid H2B histon mRNA=%.2lf, endog. H3 histon mRNA=%.2lf, histone binding sites (DNA)=%.2lf, total new DNA=%.2lf with endog. H2B, total new DNA=%.2lf with plasmid H2B,\n",He2bold,Hp2bold,He3old,Me2bold,Mp2bold,Me3old,Dold,totnDNAe,totnDNAp);

 current_time=0.0;
 f1e2b=0.0; f1p2b=0.0; f1e3=0.0; f2e2b=0.0; f2p2b=0.0; f2e3=0.0; f3e2b=0.0; f3p2b=0.0; f3e3=0.0; f4e2b=0.0; f4p2b=0.0; f4e3=0.0; f5=0.0; f6e=0.0; f6p=0.0;
 // S=0.0; V5=0.0;
 S = S0 / ((exp(S1*(totnDNAe+totnDNAp - S2))+1.0) * (exp(S5*(current_time - S6))+1.0) * (exp(S3*(-current_time - S4))+1.0));
 V5 = A0 / ((exp(A1*(current_time - A2))+1.0)*(exp(A3*(-current_time - A4))+1.0));

 fprintf(d1,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",current_time,Me2bold,Mp2bold,Me3old,He2bold,Hp2bold,He3old,Dold,totnDNAe,totnDNAp,totnDNAe+totnDNAp);  
 fprintf(d2,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %.10lf\n",current_time,S,Vme2b,Vmp2b,Vme3,IY,n1,gambase,gamind,KY,n2,k3,delta,V5,k6);  
 fprintf(d3,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",current_time,f1e2b,f1p2b,f1e3,f2e2b,f2p2b,f2e3,f3e2b,f3p2b,f3e3,f4e2b,f4p2b,f4e3,f5,f6e,f6p);  
 fprintf(d4,"%lf %lf %lf %lf %lf %lf %lf %lf\n",current_time,f1e2b-f2e2b,f1p2b-f2p2b,f1e3-f2e3,f3e2b-f4e2b-f6e,f3p2b-f4p2b-f6p,f3e3-f4e3-f6e-f6p,f5-f6e-f6p);
 
 for(step=1;step<=limit;step++){ /* start stepwise integration */
   if(step%(limit/10)==0)  printf("%ld from %ld\n",step,limit);  
  

   S = S0 / ((exp(S1*(totnDNAe+totnDNAp - S2))+1.0) * (exp(S5*(current_time - S6))+1.0) * (exp(S3*(-current_time - S4))+1.0));

   // S=S0;

   /* experimental V5  */

    V5 = A0 / ((exp(A1*(current_time - A2))+1.0)*(exp(A3*(-current_time - A4))+1.0));

    //    if(current_time>S6) V5=0.0;   //   to prevent DNA accumulation after SLBP switched off, V5 in principle very little on for ever
    if(current_time>S6) V5=V5*exp(0.0001*(-current_time+S6));   //   to prevent DNA accumulation after SLBP switched off, V5 in principle very little on for ever


  /* all fluxes / velocities separately */  
    //   f1e2b=S*Vme2b/(1+pow(((He2bold+Hp2bold)/IY),n1));
   f1e2b=S*Vme2b*pow(Dold,n1)/(pow(KY,n1)+pow(Dold,n1));
   f1p2b=Vmp2b;
   //    f1e3=S*Vme3/(1+pow((He3old/IY),n1));
   f1e3=S*Vme3*pow(Dold,n1)/(pow(KY,n1)+pow(Dold,n1));

   //   f2e2b=(gambase+gamind*pow((He2bold+Hp2bold),n2)/(pow(KY,n2)+pow((He2bold+Hp2bold),n2)))*Me2bold;
   f2e2b=(gambase+gamind/(1.0+pow(Dold/IY,n2)))*Me2bold;
   f2p2b=gambase*Mp2bold;
   //   f2e3=(gambase+gamind*pow(He3old,n2)/(pow(KY,n2)+pow(He3old,n2)))*Me3old;
   f2e3=(gambase+gamind/(1.0+pow(Dold/IY,n2)))*Me3old;
    
    //f1=S*Vm*pow(Dold,n1)/(pow(KY,n1)+pow(Dold,n1));
   //f2=(gambase+gamind/(1.0+pow(Dold/IY,n2)))*Mold;

   f3e2b=k3*Me2bold;
   f3p2b=k3*Mp2bold;
   f3e3=k3*Me3old;
   
   f4e2b=delta*He2bold;
   f4p2b=delta*Hp2bold;
   f4e3=delta*He3old;

   f5=V5;
   //if(current_time>=Don && current_time <= Doff)  f5=V5;
   //else f5=0.0;

   f6e=k6*He2bold*He3old*Dold;
   f6p=k6*Hp2bold*He3old*Dold;
   
   Me2bnew = Me2bold + (f1e2b-f2e2b)*delta_t;
   Mp2bnew = Mp2bold + (f1p2b-f2p2b)*delta_t;
   Me3new = Me3old + (f1e3-f2e3)*delta_t;

   He2bnew = He2bold + (f3e2b-f4e2b-f6e)*delta_t;
   Hp2bnew = Hp2bold + (f3p2b-f4p2b-f6p)*delta_t;
   He3new = He3old + (f3e3-f4e3-f6e-f6p)*delta_t;

   Dnew = Dold + (f5-f6e-f6p)*delta_t;

   totnDNAe+=f6e*delta_t;
   totnDNAp+=f6p*delta_t;
 
   current_time+=delta_t;   

   He2bold=He2bnew;
   Hp2bold=Hp2bnew;
   He3old=He3new;

   Me2bold=Me2bnew;
   Mp2bold=Mp2bnew;
   Me3old=Me3new;

   Dold=Dnew;
  
// integration over mRNA's
   sumMe2b+=Me2bold*delta_t;
   sumMp2b+=Mp2bold*delta_t;
   sumMe3+=Me3old*delta_t;

// integration over free histone proteins
   sumHe2bfree+=He2bold*delta_t;
   sumHp2bfree+=Hp2bold*delta_t;
   sumHe3free+=He3old*delta_t;
   
   // integration over built-in histone proteins
   sumHe2b+=totnDNAe*delta_t;
   sumHp2b+=totnDNAp*delta_t;
   sumHe3+=(totnDNAe+totnDNAp)*delta_t;
   /*
   // integration over free and built-in histone proteins
     sumHe2b+=(totnDNAe+He2bold)*delta_t;
     sumHp2b+=(totnDNAp+Hp2bold)*delta_t;
     sumHe3+=(totnDNAe+totnDNAp+He3old)*delta_t;
   */
 
   if(step%100==0){
     fprintf(d1,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",current_time,Me2bold,Mp2bold,Me3old,He2bold,Hp2bold,He3old,Dold,totnDNAe,totnDNAp,totnDNAe+totnDNAp);  
     fprintf(d2,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %.10lf\n",current_time,S,Vme2b,Vmp2b,Vme3,IY,n1,gambase,gamind,KY,n2,k3,delta,V5,k6);  
     fprintf(d3,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",current_time,f1e2b,f1p2b,f1e3,f2e2b,f2p2b,f2e3,f3e2b,f3p2b,f3e3,f4e2b,f4p2b,f4e3,f5,f6e,f6p);  
     fprintf(d4,"%lf %lf %lf %lf %lf %lf %lf %lf\n",current_time,f1e2b-f2e2b,f1p2b-f2p2b,f1e3-f2e3,f3e2b-f4e2b-f6e,f3p2b-f4p2b-f6p,f3e3-f4e3-f6e-f6p,f5-f6e-f6p);
   }
 }    /* end stepwise integration */

 printf("final conditions: endog. H2B histon protein=%.2lf, plasmid H2B histon protein=%.2lf, endog. H3 histon protein=%.2lf, endog. H2B histon mRNA=%.2lf, plasmid H2B histon mRNA=%.2lf, endog. H3 histon mRNA=%.2lf, histone binding sites (DNA)=%.2lf, total new DNA=%.2lf with endog. H2B, total new DNA=%.2lf with plasmid H2B,\n",He2bold,Hp2bold,He3old,Me2bold,Mp2bold,Me3old,Dold,totnDNAe,totnDNAp);

 printf("\nfinished calculation over %lf time units (sec), i.e. %lf h\n",current_time, current_time/3600);
 printf("integrals over full integration time %lf h:\n",current_time/3600);
 printf("endogenous H2B mRNA sumMe2b=%lf\n",sumMe2b);
 printf("plasmid H2B mRNA sumMp2b=%lf\n",sumMp2b);
 printf("endogenous H3 mRNA sumMe3=%lf\n\n",sumMe3);

printf("sum endogenous H2B protein built-in DNA sumHe2b*10^-9 = %lf\n",sumHe2b/1000000000);
 printf("sum plasmid H2B protein built-in DNA sumHp2b*10^-9 = %lf\n",sumHp2b/1000000000);
 printf("sum endogenous H3 protein built-in DNA sumHe3*10^-9 = %lf\n\n",sumHe3/1000000000);

 printf("sum free endogenous H2B protein sumHe2bfree*10^-9 = %lf\n",sumHe2bfree/1000000000);
 printf("sum free plasmid H2B protein sumHp2bfree*10^-9 = %lf\n",sumHp2bfree/1000000000);
 printf("sum free endogenous H3 protein sumHe3free*10^-9 = %lf\n\n",sumHe3free/1000000000);

 printf("sum built-in and free endogenous H2B protein sumHe2b + sumHe2bfree*10^-9 = %lf\n",(sumHe2b + sumHe2bfree)/1000000000);
 printf("sum built-in and free plasmid H2B protein sumHp2b + sumHp2bfree*10^-9 = %lf\n",(sumHp2b + sumHp2bfree)/1000000000);
 printf("sum built-in and free endogenous H3 protein sumHe3 + sumHe3free*10^-9 = %lf\n\n",(sumHe3 + sumHe3free)/1000000000);


 fclose(d1);
 fclose(d2);
 fclose(d3);
 fclose(d4);
}
