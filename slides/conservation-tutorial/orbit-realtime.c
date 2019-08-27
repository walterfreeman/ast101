#include <stdio.h>
#include <math.h>

void box(double x1, double y1, double x2, double y2)
{
  printf("l %e %e %e %e\n",x1,y1,x1,y2);
  printf("l %e %e %e %e\n",x1,y2,x2,y2);
  printf("l %e %e %e %e\n",x2,y2,x2,y1);
  printf("l %e %e %e %e\n",x2,y1,x1,y1);
}

int main(void)
{
  double x=1,y=0,vx=0,vy=3;


  int rbmax=1000;
  double xrb[rbmax],yrb[rbmax],Trb[rbmax],Urb[rbmax];
  double GM=4*M_PI*M_PI;
  double T, U;
  double xo=-1,yo=0,xm=3e-3,ym=1;
  double Tmin=999, Tmax=0, Umin=999, Umax=-999;
  double r,t, dt=2e-7,rbd=3e-3,tlast=0;
  int rbl=0,frame,fs=10000;
  for (int i=0; i<rbmax; i++)
  {
    xrb[i]=x; yrb[i]=y; Trb[i]=0; Urb[i]=0;
  }

  for (t=0; 1; t+=dt)
  {
    x += vx*dt/2;
    y += vy*dt/2;
    r=hypot(x,y);
    vx -= x*GM/(pow(r,3.01))*dt;
    vy -= y*GM/(pow(r,3.01))*dt;
    x += vx*dt/2;
    y += vy*dt/2;
    r=hypot(x,y);
    U=-GM/r;
    T=0.5*vx*vx+0.5*vy*vy;
    if (U>Umax) Umax=U;
    if (T>Tmax) Tmax=T;

    if (U<Umin) Umin=U;
    if (T<Tmin) Tmin=T;

    if (t - tlast > rbd)
    { 
      tlast+=rbd;
      rbl=rbl-1; if (rbl == -1) rbl=rbmax-1;
      Trb[rbl]=T; 
      Urb[rbl]=U; 
      xrb[rbl]=x; 
      yrb[rbl]=y; 
    }

    if (++frame % fs == 0)
    {
      printf("C 0.5 0.5 0.5\n");
      box (xo, -0.1, xo-rbmax*xm, 1.1);
      box (xo, 1.1, xo-rbmax*xm, 2.3);
//      printf("T %e %e\nKinetic\n",xo-rbmax*xm*.7,2.4);
     printf("C 1 0.4 0.4\n");
     printf("t -2.8 2.4\nPotential\n");
     printf("C 0.4 1 0.4\n");
     printf("t -2.9 -0.4\nKinetic\n");
    for (int i=0; i<rbmax-1; i++)
    {
      int j=(rbl + i) % rbmax;
      int k=(rbl + i + 1) % rbmax;
      if (yrb[j] == 0) continue;
      printf("C 0.5 0.5 0.5\n");
      printf("l %e %e %e %e\n",xrb[k],yrb[k],xrb[j],yrb[j]);

      double f=sqrt(((double)(rbmax-i)/rbmax));
      printf("C %e %e %e\n",1.0*f,0.4*f,0.4*f);
      printf("l %e %e %e %e\n",xo-(i)*xm,(Urb[j] - Umin) / (Umax-Umin)*ym + 1.2,
                               xo-(i+1)*xm,(Urb[k] - Umin) / (Umax-Umin)*ym + 1.2);
      
      printf("C %e %e %e\n",0.0,1.0*f,0.0);
      printf("l %e %e %e %e\n",xo-(i)*xm,(Trb[j] - Tmin) / (Tmax-Tmin)*ym,
                               xo-(i+1)*xm,(Trb[k] - Tmin) / (Tmax-Tmin)*ym);
      
    }
    printf("C 1 1 1\n");
    printf("c %e %e 0.05\n",x,y);
    printf("C 1 1 0\n");
    printf("c 0 0 0.07\n");
    printf("T -0.7 -0.5\nTotal energy = %.13f\n",T+U);
    printf("T -0.7 -0.6\nPosition: x=%f, y=%f\tVelocity: x=%f, y=%f\n",x,y,vx,vy);
    printf("F\n");
    }
  }
}
