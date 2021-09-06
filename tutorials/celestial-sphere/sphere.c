#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct 
{
  double x;
  double y;
  double z;
} vector;

vector operator+(vector a, vector b)
{
  static vector c;
  c.x=a.x+b.x;
  c.y=a.y+b.y;
  c.z=a.z+b.z;
  return c;
}

vector operator-(vector a, vector b)
{
  static vector c;
  c.x=a.x-b.x;
  c.y=a.y-b.y;
  c.z=a.z-b.z;
  return c;
}

vector operator*(double b, vector a)
{
  static vector c;
  c.x=a.x*b;
  c.y=a.y*b;
  c.z=a.z*b;
  return c;
}

vector operator/(vector a, double b)
{
  static vector c;
  c.x=a.x/b;
  c.y=a.y/b;
  c.z=a.z/b;
  return c;
}

vector operator*(vector a, double b)
{
  static vector c;
  c.x=a.x*b;
  c.y=a.y*b;
  c.z=a.z*b;
  return c;
}

double operator*(vector a, vector b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

double norm(vector a)
{
  return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

double normsq(vector a)
{
  
  return a.x*a.x + a.y*a.y + a.z*a.z;
}

vector cross(vector a, vector b)
{
  //printf("crossing:: %e %e %e and %e %e %e\n",a.x,a.y,a.z,b.x,b.y,b.z);
  vector c;
  c.x = a.y*b.z - a.z*b.y;
  c.y = a.z*b.x - a.x*b.z;
  c.z = a.x*b.y - a.y*b.x;
//  printf("result: %e %e %e\n",c.x,c.y,c.z);
  return c;
}

void lin(vector v1, vector v2)
{
    printf("l3 %e %e %e %e %e %e\n",v1.x,v1.y,v1.z,v2.x,v2.y,v2.z);
}

void ring(vector cen, double r, vector dir)
{
    printf("ring %e %e %e %e %e %e %e %e %d %d\n", cen.x,cen.y,cen.z,dir.x,dir.y,dir.z,r,r*0.007,80,40);
    return;
 // printf("!ring: center is %e %e %e, dir is %e %e %e, rad is %e\n",cen.x,cen.y,cen.z,dir.x,dir.y,dir.z,r);
  vector v1,v2,vr;
  double thstep=M_PI/20.0;
  vr.x=3.14159;
  vr.y=28;
  vr.z=67;
  
  v1=cross(dir,vr);
  v2=cross(dir,v1);
//  printf("orthog vectors: %e %e %e and %e %e %e\n",v1.x,v1.y,v1.z,v2.x,v2.y,v2.z);
  v1=v1 / norm(v1) * r;
  v2=v2 / norm(v2) * r;
  
  for (double th=0; th<=2*M_PI; th+=thstep)
  {
    lin(cen+v1*sin(th)+v2*cos(th),cen+v1*sin(th+thstep)+v2*cos(th+thstep));
  }
}

void globe(vector cen, vector pole, vector eq, double r, double g, double b, double a)
{
  printf("C4 %e %e %e %e\n",r,g,b,a);
  
  double latlines=6;// draw five latitude lines on each side

  double rad=norm(pole);

  for (double f=-1; f<=1;f+=2.0/latlines)
  {
    ring(cen+pole*f, rad*sqrt(1-f*f), pole);
  }

  eq=eq/norm(eq)*rad;

  vector perp;
  perp=cross(pole,eq);
  perp=perp/norm(perp)*rad;

  for (double th=0; th<2*M_PI; th+=M_PI/latlines)
  {
    ring(cen, rad, eq*cos(th) + perp*sin(th));
  }
}
  
void rotate_y(vector &v, double th)
{
  v.x = v.x*cos(th)+v.z*sin(th);
  v.z = v.z*cos(th)-v.x*sin(th);
}

void rotate_z(vector &v, double th)
{
  v.x = v.x*cos(th)+v.y*sin(th);
  v.y = v.y*cos(th)-v.x*sin(th);
}

void plane(vector cen, double r, vector orth, vector x)
{
  int nlines=10;
  vector y=cross(orth,x);
  x=cross(orth,y);
  x=x/norm(x)*r;
  y=y/norm(y)*r;

  for (double i=-1;i<1.00001;i+=2.0/nlines)
  {
    lin(cen+x*i+y,cen+x*i-y); 
    lin(cen+y*i+x,cen+y*i-x); 
  }
}
  

int main(int argc, char **argv)
{
  double obsang=0.5;
  double clat=0;

  if (argc>=2) clat=atof(argv[1]);
  if (argc>=3) obsang=M_PI/2-atof(argv[2])*M_PI/180;
  
  vector v1,v2;
  vector zv;
  int nstars=2000;
  zv.x=zv.y=zv.z=0;

  vector star[nstars];
  double b[nstars];  
  double r[nstars];
  vector color[nstars];

  for (int i=0;i<nstars;i++)
  {
    r[i]=drand48()*0.02;
    b[i]=drand48()*1;
    star[i].x=drand48()-.5;
    star[i].y=drand48()-.5;
    star[i].z=drand48()-.5;
    star[i]=star[i]/norm(star[i])*4;
    color[i].x=1.0 * b[i];
    color[i].y=1.0 * b[i];
    color[i].z=0.5 * b[i];
  }
  
  color[0].x = 0.0;
  color[0].y = 1.0;
  color[0].z = 0.0;

  r[0]=0.2;
  star[0].x=0;
  star[0].y=cos((clat+5)*M_PI/180)*4;
  star[0].z=sin((clat+5)*M_PI/180)*4;
  
  color[1].x = 1.0;
  color[1].y = 0.0;
  color[1].z = 1.0;
  r[1]=0.2;
  star[1].x=0;
  star[1].y=cos((clat+46)*M_PI/180)*4;
  star[1].z=sin((clat+46)*M_PI/180)*4;
  
  vector v1r;
  vector obs;
  obs.x=sin(obsang)*0.4;
  obs.y=0;
  obs.z=cos(obsang)*0.4;

  v1.x=1;
  v1.y=0;
  v1.z=0;
  v1r=v1;
  v2.x=0;
  v2.y=0;
  v2.z=1;
  vector vtemp;
  double rotrate = 0.002;
  
  vector zhat=zv; zhat.z=1;
  printf("font large\n");
  while (1)
  {
     printf("C 1 1 1\n");
     printf("c3 0 0 4 0.1\n");
     printf("t3 0 0 4.8\nNorth Star\n");
     lin(zv,v2*4);
//     globe(zv,v2*0.4,v1,3,3,6,1.0);
     printf("C 0.2 0.3 0.7\n");
     printf("c3 0 0 0 0.4\n");
     globe(zv,v2*4,v1r,0.3,0.2,0.1,1.0);
//     printf("C 0.5 0.2 0.2\n");
     
//     plane(zv,5,v2,v1);
     rotate_z(v1r,rotrate);
     
     printf("C 0 1 0\n");
     ring(star[0].z*zhat,hypot(star[0].x,star[0].y),zhat);
     printf("C 1 0 1\n");
     ring(star[1].z*zhat,hypot(star[1].x,star[1].y),zhat);


     double zdot = sin((clat+46)*M_PI/180)*4;
     double rdot = cos((clat+46)*M_PI/180)*4;
     double rad=0.1;

     printf("C 0.2 0.2 1\n");
     printf("c3 %e %e %e %e\n",rdot,0.,zdot,rad);
     printf("C 1 1 0\n");
     printf("c3 %e %e %e %e\n",0.,-rdot,zdot,rad);
     printf("C 1 0.2 0\n");
     printf("c3 %e %e %e %e\n",0.,rdot,zdot,rad);
     printf("C 0.7 0.7 0.7\n");
     printf("c3 %e %e %e %e\n",-rdot,0.,zdot,rad);
     

     zdot = sin((clat+5)*M_PI/180)*4;
     rdot = cos((clat+5)*M_PI/180)*4;
     rad=0.1;

     printf("C 0.2 0.2 1\n");
     printf("c3 %e %e %e %e\n",rdot,0.,zdot,rad);
     printf("C 1 1 0\n");
     printf("c3 %e %e %e %e\n",0.,-rdot,zdot,rad);
     printf("C 1 0.2 0\n");
     printf("c3 %e %e %e %e\n",0.,rdot,zdot,rad);
     printf("C 0.7 0.7 0.7\n");
     printf("c3 %e %e %e %e\n",-rdot,0.,zdot,rad);
     


     for (int i=0;i<nstars;i++)
     {
//       if (i>0)  { if (star[i]*obs > 0) printf("C %e %e %e\n",b[i],b[i],0.0); else printf("C4 %e %e %e %e\n",b[i]/2,b[i]/2,b[i]/2,0.2); }
  //     if (i==0) { if (star[i]*obs > 0) printf("C %e %e %e\n",b[i],b[i],0.0); else printf("C4 %e %e %e %e\n",b[i]/2,b[i]/2,b[i]/2,0.2); }
       if (star[i]*obs > 0) 
	   printf("C4 %e %e %e %e\n",color[i].x,color[i].y,color[i].z,1.0); 
       else 
	   printf("C4 %e %e %e %e\n",color[i].x*0.2, color[i].y*0.2, color[i].z*1,0.4);

       printf("c3 %e %e %e %e\n",star[i].x,star[i].y,star[i].z,r[i]);
       if (i==0)
       for (double rtemp=0;rtemp<r[i];rtemp+=r[i]*0.1)
         printf("c3 %e %e %e %e\n",star[i].x,star[i].y,star[i].z,rtemp);

       rotate_z(star[i],rotrate);
       star[i]=star[i]/norm(star[i])*4.0;
     }
     
     printf("C 1 1 1\n");
     printf("c3 %e %e %e %e\n",obs.x,obs.y,obs.z,0.1);
     printf("C 0.5 0 0\n");
     plane(zv,5,obs,v1);

     vtemp=cross(cross(obs,v2),obs);

     vtemp=vtemp/norm(vtemp)*8;
     printf("F\n");
   }
}

