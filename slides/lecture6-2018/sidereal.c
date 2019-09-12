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
  vector c;
  c.x = a.y*b.z - a.z*b.y;
  c.y = a.z*b.x - a.x*b.z;
  c.z = a.x*b.y - a.y*b.x;
  return c;
}

void lin(vector v1, vector v2)
{
    printf("l3 %e %e %e %e %e %e\n",v1.x,v1.y,v1.z,v2.x,v2.y,v2.z);
}

void lit_ring (vector cen, double r, vector dir, vector v, double r1, double g1, double b1, double r2, double g2, double b2)
{
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
  int lastcol=-1;

  for (double th=0; th<=2*M_PI; th+=thstep)
  {
    vector first, second;
    first=(v1*sin(th+thstep/2)+v2*cos(th+thstep/2));
    second=v;
    
    //printf("!Vector from center of globe to point on edge: %f %f %f\n",first.x,first.y,first.z);
    //printf("!Vector from center of globe to origin: %f %f %f\n",second.x,second.y,second.z);
    //printf("!Inner product: %f\n",first*second);
     
    if ( first*second > 0 && lastcol != 1) {
      printf("C %e %e %e\n",r1,g1,b1); lastcol=1;}
    if ( first*second < 0 && lastcol != 2) {
      printf("C %e %e %e\n",r2,g2,b2); lastcol=2;}

    lin(cen+v1*sin(th)+v2*cos(th),cen+v1*sin(th+thstep)+v2*cos(th+thstep));
  }
}

void ring (vector cen, double r, vector dir)
{
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

void globe(vector cen, vector pole, vector eq, double r, double g, double b, int n)
{
  printf("C %e %e %e\n",r,g,b);
  
  double latlines=n;// draw five latitude lines on each side

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

void lit_globe(vector cen, vector pole, vector eq, double r1, double g1, double b1, double r2, double g2, double b2, int n)
{
  
  double latlines=n;// draw five latitude lines on each side

  double rad=norm(pole);

  for (double f=-1; f<=1;f+=2.0/latlines)
  {
    lit_ring(cen+pole*f, rad*sqrt(1-f*f), pole,cen,r1,g1,b1,r2,g2,b2);
    //ring(cen+pole*f, rad*sqrt(1-f*f), pole);
    // need to actually pull the code from ring to shade each line
  }

  eq=eq/norm(eq)*rad;

  vector perp;
  perp=cross(pole,eq);
  perp=perp/norm(perp)*rad;

  for (double th=0; th<2*M_PI; th+=M_PI/latlines)
  {
    lit_ring(cen, rad, eq*cos(th) + perp*sin(th),cen,r1,g1,b1,r2,g2,b2);
  }
}
   
void rotate_y(vector &v, double th)
{
  v.x = v.x*cos(th)+v.z*sin(th);
  v.z = v.z*cos(th)-v.x*sin(th);
}

void rotate_z(vector &v, double th)
{
  static vector vtemp;
  
  vtemp.x = v.x*cos(th)-v.y*sin(th);
  vtemp.y = v.y*cos(th)+v.x*sin(th);
  v=vtemp;
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
  
void arrow (vector o, vector v, double r, double g, double b)
{
  printf("C %f %f %f\n",r,g,b);
  lin(o,o+v);
  // generate two vectors orthogonal to v

  vector x,y;
  x.x=12; x.y=36; x.z=107;

  y=cross(v,x); y=y/norm(y)*norm(v);
  x=cross(v,y); x=x/norm(x)*norm(v);

  
  for (double th=0; th<2*M_PI; th+=0.5)
  {
    lin(o+v, o+v*0.8+sin(th)*x*0.1+cos(th)*0.1*y);
    x=x;
  }
}

vector rotate_arb(vector v, vector a, double th)
{
  vector res; res.x=res.y=res.z=0;
  a=a/norm(a);
  
    
  res.x += v.x * (cos(th) + a.x*a.x*(1-cos(th)));
  res.y += v.y * (cos(th) + a.y*a.y*(1-cos(th)));
  res.z += v.z * (cos(th) + a.z*a.z*(1-cos(th)));

  res.x += v.y * (a.x*a.y*(1-cos(th)) - a.z * sin(th));
  res.y += v.z * (a.y*a.z*(1-cos(th)) - a.x * sin(th));
  res.z += v.x * (a.z*a.x*(1-cos(th)) - a.y * sin(th));

  res.x += v.z * (a.x*a.z*(1-cos(th)) + a.y * sin(th));
  res.y += v.x * (a.y*a.x*(1-cos(th)) + a.z * sin(th));
  res.z += v.y * (a.z*a.y*(1-cos(th)) + a.x * sin(th));


  return res;
}

int main(int argc, char **argv)
{
  double phantom_after;
  double stop_after;
  double angle=0;
  double axialtilt=0;

  double obsang=0.5;
  double clat=0;
  vector zv;
  zv.x=zv.y=zv.z=0;

  double sec_per_day=1;
  double sec_per_year=10;
  int axis=1;
  if (argc <= 1)
  {
    fprintf(stderr, "Usage: <this> <sec per day> <sec per year> <axial tilt> <ghost after n sidereal days> <stop after n sidereal days> <draw axis?> <draw lines?>\n"); 
    exit(0);
  }
  
  sec_per_day=atof(argv[1]);
  sec_per_year=atof(argv[2]);
  axialtilt=atof(argv[3]);
  phantom_after=atof(argv[4]);
  stop_after=atof(argv[5]);
  axis=atoi(argv[6]);
  int lines=atoi(argv[7]);

  printf("!%.3f seconds per day\n",sec_per_day);
  printf("!%.3f seconds per year\n",sec_per_year);
  printf("!%.3f degrees axial tilt\n",axialtilt);
  printf("!%.3f sidereal days until ghost\n",phantom_after);
   

  vector phantom_init_earth;
  vector phantom_init_earth_or;
  vector phantom_earth;
  vector phantom_earth_or;
  int phantom=0;
  double ang=0,ang2=0;
  double Rconst=10;

  vector zhat=zv; zhat.z=1;
  vector xhat=zv; xhat.x=1;
  vector yhat=zv; yhat.y=1;
 
  vector earth_or;
  earth_or.x=-cos(axialtilt/180.*M_PI);
  earth_or.y=0;
  earth_or.z=sin(axialtilt/180.*M_PI);
 
  vector rotax;
  rotax.x=sin(axialtilt/180.*M_PI);
  rotax.z=cos(axialtilt/180.*M_PI);
  rotax.y=0;

  vector earth;
  earth.x=1;
  earth.y=0;
  earth.z=0; 
  double rarrow=1, barrow=1, garrow=1;
  phantom_init_earth=earth;
  phantom_init_earth_or=earth_or;
  double rdark=0.5,gdark=0.3,bdark=0.2,rlit=1,glit=1,blit=1;
  int phantomflag=0;
  while (1)
  {
 //   globe(zv, zhat*0.1, xhat,1,1,0,13);
    printf("C 1 0 0\n");
    ring(zv,1,zhat);
    printf("c3 %e %e %e %e\n",earth.x, earth.y, earth.z, 0.05);
//    lit_globe(earth, zhat*0.1, earth_or, rdark,gdark,bdark,rlit,glit,blit,13);
    printf("F\n");
    rotate_z(earth, 1.0/sec_per_year*2*M_PI/60);
    ang += 1.0/sec_per_year*2*M_PI/60;
    ang2 += 1.0/sec_per_day*2*M_PI/60;
//    rotate_z(earth_or, 1.0/sec_per_day*2*M_PI/60);
    earth_or=rotate_arb(earth_or, rotax, 1.0/sec_per_day*2*M_PI/60);
    earth=earth/norm(earth);
  //  earth_or=earth_or/norm(earth_or);

    if (phantom_after)
    {
      lit_globe(phantom_init_earth, zhat*0.1,phantom_init_earth_or, 0.3,0.2,0.1,0.6,0.6,0.6,13);
      globe(phantom_init_earth+phantom_init_earth_or*0.1,zhat*0.04, phantom_init_earth_or,0.5,0.5,0,13);
      arrow(phantom_init_earth+phantom_init_earth_or*0.1,phantom_init_earth_or*0.3,1,1,1);
      if (axis) arrow(earth+rotax*0.1,rotax*0.3,0,0.5,0);
    }  

    if (ang2/(2*M_PI) > phantom_after && phantomflag==0) 
    {
      phantom_earth_or=earth_or; phantom_earth=earth; phantomflag=1;
    }

    if (ang2/(2*M_PI) > phantom_after && phantom_after)
    {
      lit_globe(phantom_earth, zhat*0.1,phantom_earth_or, 0.5,0.2,0.2,1,0.5,0.5,8);
      globe(phantom_earth+phantom_earth_or*0.1,zhat*0.04, phantom_earth_or,0.3,0.1,0,6);
      arrow(phantom_earth+phantom_earth_or*0.1,phantom_earth_or*0.3,1,0.5,0.5);
      if (axis) arrow(earth+rotax*0.1,rotax*0.3,0,0.5,0);
    }  
    if (ang2/(2*M_PI) / ( (sec_per_year/sec_per_day) / (sec_per_year / sec_per_day - 1)) > stop_after && stop_after) 
    {
      sec_per_year=sec_per_day=1e10;
      rlit=0.0;glit=1;blit=0;rdark=0;gdark=0.4;bdark=0;
      rarrow=0.6; garrow=0.6; barrow=1;
    }

// draw observer
    globe(earth+earth_or*0.1,zhat*0.04, earth_or,1,1,0,6);
// draw arrow in direction of observer
    arrow(earth+earth_or*0.1,earth_or*0.3,rarrow,garrow,barrow);
// draw rotation axis
    if (axis) arrow(earth+rotax*0.1,rotax*0.3,0,1,0);

// write constellation names at r=Rconst 
   
   vector Vc=zv;
   Vc.x=6; 
   
   ring(zv,6,zhat); 


  }
}

