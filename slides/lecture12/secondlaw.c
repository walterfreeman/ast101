#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct 
{
  double x;
  double y;
  double z;
} vector;

vector xhat,yhat,zhat,zvec;

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

typedef struct 
{
  vector r;
  vector v;
  double m; // mass in solar masses
  double size;
  vector color;
  vector eqline;
  vector rotax;
} planet;

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

planet init_planet(double r2, double r1, double mass, double size)
{
  planet p;

  vector origin=zvec;
  double GM=4*M_PI*M_PI;

  // easy stuff first
  p.size=size;
  p.rotax=zhat*size;
  p.eqline=xhat*size;
  p.m=mass;
  p.color=xhat+yhat+zhat;

  // start at aphelion
  p.r=xhat*r2+origin; // stick it here for now
  
  double E;
  E=-GM/(r2+r1);  
  printf("!Initializing planet: aphelion %e, perihelion %e, specific orbital energy %e\n",r2,r1,E);
  
  double L2;
  L2 = -(E*E*(r2-r1)*(r2-r1)-GM) / (2*E);

  printf("!Squared specific  angular momentum is %e\n",L2);
  p.v=yhat*sqrt(L2)/r2;
  printf("!Initial velocity is %e\n",sqrt(L2)/r2);

  return p;
}
  
 

int main(int argc, char **argv)
{
  xhat.x=1;
  xhat.y=0;
  xhat.z=0;
  yhat.x=0;
  yhat.y=1;
  yhat.z=0;
  zhat.x=0;
  zhat.y=0;
  zhat.z=1;
  zvec=xhat*0;
  double phantom_after;
  double stop_after;
  double angle=0;
  double axialtilt=0;
  double G=4*M_PI*M_PI;

  double obsang=0.5;
  double clat=0;
  vector zv;
  zv.x=zv.y=zv.z=0;

  double sec_per_day=1;
  double sec_per_year=10;
  int axis=1;
 
  planet ss[10];
  int nplanets=2;

  int rbl=0,ringbuf_size=2000;
  vector ringbuf[nplanets][ringbuf_size];
  int connect[nplanets][ringbuf_size];
  for (int i=0;i<ringbuf_size;i++)
  {
    for (int j=0;j<nplanets;j++)
    {
      ringbuf[j][i]=-137*(xhat+yhat+zhat);
      connect[j][i]=0;
    }
  }

  ss[0].size=0.1;
  ss[0].rotax=zhat*ss[0].size;
  ss[0].eqline=xhat*ss[0].size;
  ss[0].color=xhat+yhat+zhat*0.3;
  ss[0].m=1;
  ss[0].r=zvec;
  ss[0].v=zvec;

  ss[1].size=0.05;
  ss[1].rotax=zhat*ss[1].size;
  ss[1].eqline=xhat*ss[1].size;
  ss[1].color=xhat*0.5+yhat*0.5+zhat*1;
  ss[1].m=0.0000;
  ss[1].r=xhat*6;
  ss[1].v=yhat*2*M_PI*0.2;

  ss[2].size=0.04;
  ss[2].rotax=zhat*ss[2].size;
  ss[2].eqline=xhat*ss[2].size;
  ss[2].color=xhat;
  ss[2].m=0.0000;
  ss[2].r=xhat*1.5;
  ss[2].v=sqrt(G/ss[2].r.x)*yhat;

  ss[3].size=0.02;
  ss[3].rotax=zhat*ss[3].size;
  ss[3].eqline=xhat*ss[3].size;
  ss[3].color=xhat+zhat;
  ss[3].m=0.0000;
  ss[3].r=xhat*0.45;
  ss[3].v=sqrt(G/ss[3].r.x)*yhat;

  ss[4].size=0.05;
  ss[4].rotax=zhat*ss[4].size;
  ss[4].eqline=xhat*ss[4].size;
  ss[4].color=xhat+zhat+yhat;
  ss[4].m=0.0000;
  ss[4].r=xhat*0.728;
  ss[4].v=sqrt(G/ss[4].r.x)*yhat;

  ss[5].size=0.1;
  ss[5].rotax=zhat*ss[5].size;
  ss[5].eqline=xhat*ss[5].size;
  ss[5].color=xhat+zhat;
  ss[5].m=0.0000;
  ss[5].r=xhat*5.2;
  ss[5].v=sqrt(G/ss[5].r.x)*yhat;

  ss[6].size=0.08;
  ss[6].rotax=zhat*ss[6].size;
  ss[6].eqline=xhat*ss[6].size;
  ss[6].color=xhat+yhat;
  ss[6].m=0.0000;
  ss[6].r=xhat*10;
  ss[6].v=sqrt(G/ss[6].r.x)*yhat*0.95;
  
  ss[7].size=0.05;
  ss[7].rotax=zhat*ss[7].size;
  ss[7].eqline=xhat*ss[7].size;
  ss[7].color=xhat+zhat+yhat;
  ss[7].m=0.0000;
  ss[7].r=xhat*15;
  ss[7].v=sqrt(G/ss[7].r.x)*yhat*0.3;
  

double period[nplanets]; for (int i=0;i<nplanets;i++) period[i]=-1;
 


  double rhalf[nplanets],vhalf[nplanets];
  double tup=0;
  double tskip=0.02;
  double trbskip=0.02,trb=0;
  // solve solar system with Euler-Cromer

  double dt=1e-4;
 for (int i=0;i<nplanets;i++)
    {
      vector vnew = ss[i].r + ss[i].v * dt/2; // position update
    }



  for (double t=0;1;t+=dt)
  {
    for (int i=0;i<nplanets;i++)
    {
      for (int j=0;j<nplanets;j++)
      {
        if (i==j) continue;
        vector r;
        r=ss[i].r-ss[j].r;
        double rn=norm(r);
        ss[i].v = ss[i].v - G * ss[j].m / (rn*rn*rn) * r * dt;
      }
    }
    for (int i=0;i<nplanets;i++)
    {
      vector vnew = ss[i].r + ss[i].v * dt; // position update
      
      if ((vnew.y>0 && ss[i].r.y<0) && period[i]==-1) {period[i]=t; printf("!Planet %d has an orbital period of %e years\n",i,period[i]);}
      ss[i].r=vnew;
    }


   if (t>trb)
   {
    trb+=trbskip;
    rbl=(rbl+1)%ringbuf_size;
    for (int i=0;i<nplanets;i++)
    {
//     printf("!Assigning location %e,%e,%e to ringbuffer site %d\n",ss[i].r.x,ss[i].r.y,ss[i].r.z,(rbl)%ringbuf_size);
     ringbuf[i][(rbl)%ringbuf_size]=ss[i].r;
    
     // where are we in the period?
     connect[i][rbl%ringbuf_size]=0;
     if (period[i] > 0)
     {
       double tfrac=t/period[i];
       tfrac = tfrac-(int)tfrac;
       connect[i][rbl%ringbuf_size]=((int)(tfrac*10))%10;
   //    if (tfrac > 0.95 || tfrac < 0.05) connect[i][rbl%ringbuf_size]=1;
   //    if (tfrac > 0.45 && tfrac < 0.55) connect[i][rbl%ringbuf_size]=2;
     }
   }
   }     

    if (t>tup)
    {

    
     
     
    for (int i=nplanets-1;i>=0;i--)
    {
//     printf("!Drawing planet %d at %e,%e,%e; it has velocity %e,%e,%e\n",i,ss[i].r.x,ss[i].r.y,ss[i].r.z,ss[i].v.x,ss[i].v.y,ss[i].v.z);
      //arrow(ss[i].r,ss[i].v*0.1,1,0,0);
      vector r;
      r=ss[i].r-ss[0].r;
      double rn=norm(r);  
//      arrow(ss[i].r,-G * ss[0].m / (rn*rn*rn) * r*0.01,0,1,0);
//      globe(ss[i].r, ss[i].rotax, ss[i].eqline, ss[i].color.x, ss[i].color.y, ss[i].color.z, 10); 
     printf("C %e %e %e\n",ss[i].color.x, ss[i].color.y, ss[i].color.z); 
     printf("c3 %e %e %e %e\n",ss[i].r.x,ss[i].r.y, ss[i].r.z,ss[i].size);
//      if (i>0) lin(ss[1].r,ss[i].r - (ss[1].r-ss[i].r)/norm(ss[1].r-ss[i].r)*5);
    // do thing with ring buffer


     // first connect the dots
     for (int k=rbl-1+ringbuf_size;k>rbl;k--)
     {
//       printf("!Drawing things for ringbuffer location %d for planet %d. x-coord: %e\n",k%ringbuf_size,i,ringbuf[i][k%ringbuf_size].x);
       if (ringbuf[i][k%ringbuf_size].x==-137 || ringbuf[i][(k+1)%ringbuf_size].x==-137) break;
//       printf("!ringbuffer: %d of %d\n",k,rbl+ringbuf_size);
       lin(ringbuf[i][k%ringbuf_size],ringbuf[i][(k+1)%ringbuf_size]);
       if (connect[i][k%ringbuf_size]) {
         printf("C %e %e %e\n",0.5+0.5*sin(connect[i][k%ringbuf_size]),0.5+0.5*sin(connect[i][k%ringbuf_size]+1),0.5+0.5*sin(connect[i+2][k%ringbuf_size])); 
         //lin(ringbuf[i][k%ringbuf_size],ss[0].r); 
//         printf("C %e %e %e\n",ss[i].color.x, ss[i].color.y, ss[i].color.z);
         if (k>rbl+1) printf("tr %e %e %e %e %e %e %e %e %e\n",ringbuf[i][k%ringbuf_size].x,ringbuf[i][k%ringbuf_size].y,ringbuf[i][k%ringbuf_size].z,
                                                             ss[0].r.x,ss[0].r.y,ss[0].r.z,
                                                           ringbuf[i][(k-1)%ringbuf_size].x,ringbuf[i][(k-1)%ringbuf_size].y,ringbuf[i][(k-1)%ringbuf_size].z);
        }
     }
    }
    
    printf("F\n");
    tup += tskip;
//    printf("!Radius of planet 3: %e\n",norm(ss[3].r));
  }
  }

   
 
  
}

