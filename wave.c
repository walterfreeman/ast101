#include <stdio.h>
#include <math.h>

int main(void)
{
  int N=80;
  int frame=0,frameskip=25;

  double y[N+1],v[N+1];
  
  for (int i=0;i<=N;i++)
  {
   y[i]=((double)(abs(i-40)))*0.5;
//    y[i]=N*0.1*sin(3*(double)i/N*M_PI);
    v[i]=0;
  }
 
  double dt=1e-3;
  for (double t=0; 1;t+=dt)
  {
//    for (int i=0;i<N+1;i++)
//      printf("i=%d pos=%e vel=%e\n",i,y[i],v[i]);

    for (int i=1;i<N;i++)
      y[i]+=v[i]*dt/2;
    
    for (int i=1;i<N;i++)
      v[i]+=(y[i-1]+y[i+1]-2*y[i]);
   
    for (int i=1;i<N;i++)
      y[i]+=v[i]*dt/2;
  
    frame++;

    if (frame%frameskip==0)
    {
    for (int i=0;i<N;i++)
      printf("l %d %e %d %e\n",i,y[i],i+1,y[i+1]);
    printf("F\n");
    }

  }
}
