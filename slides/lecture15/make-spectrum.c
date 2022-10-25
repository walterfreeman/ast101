#include <stdio.h>
#include <math.h>

double ampl(double l, double t)
{
  double a=1.0/(l*l*l*l*l) * 1.0/(exp(1240/(l*8.617e-5*t))-1);
  return a;
}

int main(int argc, char **argv)
{
  double x,y;
  printf("#h 0.7 y 0 5\n");
  double t=5600;
  int shift;
  for (shift = 0; shift < argc/3; shift++)
  {
  
  t=atof(argv[1+shift*3]);
  double a=atof(argv[2+shift*3])*1e34*0.75;

  double lmax;
  if (t < 1000) lmax = 20000; else lmax = 2000;

  for (x=0;x<lmax;x+=1)
  {
    y=ampl(x,t)*a / pow (t,5)*4;
    printf("%e %e\n",x,y);
  }
  printf("#\n%e %e \"%s\"\n",2.85e6/t,0.1+a*14.0/1e35,argv[3*shift+3]);
   
  }

  printf("#ls 1.2 lxs 1.2 lys 1.2\n");
  printf("#lx \"Wavelength (nm)\"\n");
  printf("#ly \"Energy output (arbitrary units)\"\n");
  printf("#cm 1 m 2\n");
  printf("390 0\n390 4.5\n#\n700 0\n700 4.5\n#cs 1 cm 1 m 1\n380 4.6 \"Visible range\"\n");
}
