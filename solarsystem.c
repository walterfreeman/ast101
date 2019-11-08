#include <math.h>
#include "vector.h"
#include <stdio.h>
#include <time.h>

int N = 3000;
int ntrails=0;
double rmin = 0.5;
double rmax = 10;
double rconst=0.2;
double rpower = 0.35;
double zspread=0.1;

int istime(int delay) 
{ 
  static int nextdraw=0; 
  if (clock() > nextdraw) 
  { 
    nextdraw = clock() + delay * CLOCKS_PER_SEC/1000.0; 
    return 1; 
  } 
  return 0; 
} 


int main(void)
{
  vector s[N], v[N], color[N];
  double m[N],rad[N];
  double G = 4*M_PI*M_PI;
  double msun = 1;
  double dt = 2e-3;
  int trlind[N];
  double menclosed=1;
  int stepcount=0,framecount=0;
  for (int i=0; i<N; i++)
  {
    double r=rmin + (double)i/N * (rmax-rmin);
    m[i] = 0.15/N;
    menclosed += m[i];
    printf("!placing particle %d at radius %e; total mass enclosed now %e\n",i,r,menclosed);
    trlind[i]=-1;
    double angle = drand48() * 2*M_PI;
    s[i] = vector(r * cos(angle), r * sin(angle), drand48()*r*zspread*2 - (r * zspread));
    v[i] = sqrt(G*(menclosed) / mag(s[i])) * ((s[i] ^ vector(0,0,1)/mag(s[i]))) * (drand48()*0.1 + 0.95);
    color[i] = vector(drand48()*0.7 + 0.3, drand48()*0.7 + 0.3, drand48()*0.7 + 0.3);
    rad[i] = pow(m[i],rpower)*rconst;
  
  }

  s[0]=vector(0,0,0);
  v[0]=vector(0,0,0);
  m[0]=1;
  rad[0] = pow(m[0],rpower)*rconst;
  color[0]=vector(1,1,0);

  vector ptot(0,0,0),vcom;
  double mtot=0;

  for (int i=0; i<N; i++)
  {
    ptot += v[i] * m[i];
    mtot += m[i];
  }
  vcom = ptot/mtot;
  for (int i=0; i<N; i++)
    v[i] -= vcom;


  while (1)
  {
    
  if (istime(50) || framecount == 10)
  {
    printf("C 1 1 1\n");
    printf("T -0.9 -0.9\nstepcount = %d(%d) \t planetesimals remaining %d\n",stepcount,framecount,N);
    framecount=0;
    for (int i=0; i<N; i++)
    {
      if (trlind[i] == -1 && m[i] > (1.3/N))
      {
        printf("!Body %d has grown large enough to leave a trail; assigning it number %d\n",i,ntrails);
        trlind[i]=ntrails;
        ntrails++;
      }
      printf("C %.2e %.2e %.2e\n",color[i].x,color[i].y,color[i].z);
      if (trlind[i] != -1) printf("ct3 %d %e %e %e %e\n",trlind[i],s[i].x,s[i].y,s[i].z,rad[i]);
      else           printf("c3 %e %e %e %e\n",s[i].x,s[i].y,s[i].z,rad[i]);
    }
    printf("F\n");
  }
   stepcount++; framecount++;
    for (int i=0; i<N; i++)
      s[i] += v[i] * dt*0.5;


    for (int i=0; i<N; i++)
      for (int j=i+1; j<N; j++)
      {
        vector rij = s[j]-s[i];
        double r = mag(rij);

        vector F = G*m[i]*m[j]*rij/(r*r*r);
        v[i] += F/m[i] * dt;
        v[j] -= F/m[j] * dt;
      }


    for (int i=0; i<N; i++)
      s[i] += v[i] * dt*0.5;
    
    for (int i=0; i<N; i++)
      for (int j=i+1; j<N; j++)
      {
        if (mag(s[i] - s[j]) < rad[i]+rad[j])
        {
          // put combined particle in i, swap j to N, reduce N
          s[i] = (s[i]*m[i] + s[j]*m[j])/(m[i]+m[j]);
          v[i] = (v[i]*m[i] + v[j]*m[j])/(m[i]+m[j]);
          m[i]=m[i]+m[j];
          if (m[j] > m[i]) trlind[i]=trlind[j];
          rad[i]=pow(m[i],rpower)*rconst;
          s[j]=s[N-1];
          v[j]=v[N-1];
          trlind[j]=trlind[N-1];
          rad[j]=rad[N-1];
          color[j]=color[N-1];
          m[j]=m[N-1];
          N--;
          printf("!Collision between %d and %d; %d particles remain\n",i,j,N-1);
        }
      }
    for (int i=0; i<N; i++)
    {
      if (mag(s[i]) > rmax*2)
      {
        printf("!planetesimal %d escaped.\n",i);
          s[i]=s[N-1];
          v[i]=v[N-1];
          trlind[i]=trlind[N-1];
          rad[i]=rad[N-1];
          color[i]=color[N-1];
          m[i]=m[N-1];
          N--;
   vector ptot(0,0,0),vcom;
  double mtot=0;

  for (int j=0; j<N; j++)
  {
    ptot += v[j] * m[j];
    mtot += m[j];
  }
  vcom = ptot/mtot;
  for (int j=0; j<N; j++)
    v[j] -= vcom;


    }
   
    }  
  }

}

