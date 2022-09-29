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
  double thstep=M_PI/40.0;
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
  double thstep=M_PI/40.0;
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
  printf("c3 %e %e %e %e\n",cen.x, cen.y, cen.z, norm(pole));
  return;
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

void lit_globe(vector cen, vector pole, vector eq, double r1, double g1, double b1, double axialtilt)
{
  
  printf("C %e %e %e\n",r1,g1,b1);
  printf("c3 %e %e %e %e\n",cen.x,cen.y,cen.z,norm(pole));

  double rad=norm(pole)*1.01;

  double f=0;
//  lit_ring(cen+pole*f, rad*sqrt(1-f*f), pole,cen,0.0, 0.0, 0.3, 0.0, 0.0, 1.0);
  printf("C 0 0.5 1\n");
  ring (cen+pole*f, rad*sqrt(1-f*f), pole);
  f=cos(M_PI*(90-axialtilt)/180);
  printf("C 0 1 0\n");
  ring (cen-pole*f, rad*sqrt(1-f*f), pole);
  ring (cen+pole*f, rad*sqrt(1-f*f), pole);
  f=cos(M_PI*(axialtilt)/180);
  printf("C 0.5 0.5 1\n");
  ring (cen-pole*f, rad*sqrt(1-f*f), pole);
  ring (cen+pole*f, rad*sqrt(1-f*f), pole);


 // double latlines=n;// draw five latitude lines on each side


  //for (double f=-1; f<=1;f+=2.0/latlines)
 // {
 //   lit_ring(cen+pole*f, rad*sqrt(1-f*f), pole,cen,r1,g1,b1,r2,g2,b2);
    //ring(cen+pole*f, rad*sqrt(1-f*f), pole);
    // need to actually pull the code from ring to shade each line
 // }

 // eq=eq/norm(eq)*rad;

 // vector perp;
 // perp=cross(pole,eq);
 // perp=perp/norm(perp)*rad;
//
//  for (double th=0; th<2*M_PI; th+=M_PI/latlines)
//  {
//    lit_ring(cen, rad, eq*cos(th) + perp*sin(th),cen,r1,g1,b1,r2,g2,b2);
//  }
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
  vtemp.z = v.z;
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
  double sec_per_month;
  double sec_per_day=1;
  double sec_per_year=10;
  int axis=1;
  if (argc <= 1)
  {
    fprintf(stderr, "Usage: <this> <sec per day> <sec per month> <sec per year> <axial tilt> <phase angle (0=Yule 180=Lithe)> <observer latitude> <precession time>\n[sun radius] [earth radius] [moon radius] [moon orbit radius] [earth orbit radius]\n"); 
    exit(0);
  }
  
  sec_per_day=atof(argv[1]);
  sec_per_month=atof(argv[2]);
  sec_per_year=atof(argv[3]);
  axialtilt=atof(argv[4]);
  double phase=atof(argv[5]);
  double latitude=atof(argv[6]) / 180 * M_PI;
  double sec_per_26k=atof(argv[7]);

  printf("!%.3f seconds per day\n",sec_per_day);
  printf("!%.3f seconds per year\n",sec_per_year);
  printf("!%.3f seconds per prec\n",sec_per_26k); 
  printf("!%.3f degrees axial tilt\n",axialtilt);
   

  vector phantom_init_earth;
  vector phantom_init_earth_or;
  vector phantom_earth;
  vector phantom_earth_or;
  int phantom=0;
  double ang=0,ang2=0;
  double Rconst=3;
  double earth_orbit_radius = 1.0;
  double earth_radius = 0.05;
  double moon_radius = 0.02;
  double sun_radius = 0.07;
  double moon_orbit_radius = 0.2;
  double factor=1;
  if (argc > 8) sun_radius = atof(argv[8]);
  if (argc > 9) earth_radius = atof(argv[9]);
  if (argc > 10) moon_radius = atof(argv[10]);
  if (argc > 11) moon_orbit_radius = atof(argv[11]);
  if (argc > 12) earth_orbit_radius = atof(argv[12]);

  printf("!Radii: \n");
  printf("!   Sun           %e AU\n",sun_radius);
  printf("!   Earth         %e AU\n",earth_radius);
  printf("!   Moon          %e AU\n",moon_radius);
  printf("!   Lunar orbit   %e AU\n",moon_orbit_radius);

  vector zhat=zv; zhat.z=1;
  vector xhat=zv; xhat.x=1;
  vector yhat=zv; yhat.y=1;
  vector earth_or;
  vector earth_to_moon;
  earth_or.x=-cos(axialtilt/180.*M_PI)*earth_orbit_radius;
  earth_or.y=0;
  earth_or.z=sin(axialtilt/180.*M_PI)*earth_orbit_radius;
  earth_to_moon.x=-cos(axialtilt/180.*M_PI)*moon_orbit_radius;
  earth_to_moon.y=0;
  earth_to_moon.z=sin(axialtilt/180.*M_PI)*moon_orbit_radius;
   
  earth_or = earth_or / norm(earth_or);

  vector rotax;
  rotax.x=sin(axialtilt/180.*M_PI);
  rotax.z=cos(axialtilt/180.*M_PI);
  rotax.y=0;

  vector obs;

  vector earth;

  earth.x=earth_orbit_radius;
  earth.y=0;
  earth.z=0; 
  rotate_z(earth,phase*M_PI/180.);
  double rarrow=1, barrow=1, garrow=1;
  double rearth=0.5,gearth=0.3,bearth=0.2;
  double rmoon=1,gmoon=1,bmoon=1;
  double precess_phase = 0;
  while (1)
  {
    printf("F\n");
//    globe(zv, zhat*0.1, xhat,1,1,0,6);
    printf("C 1 1 0\n");
// draw Sun
    printf("ulc3 %e %e %e %e\n",-earth.x,-earth.y,-earth.z,sun_radius);
    printf("C 1 0 0\n");
    // draw earth orbit
    ring(zv-earth,earth_orbit_radius,zhat);
    printf("C 0 1 1\n");
    // draw moon orbit
//    ring(zv,moon_orbit_radius,zhat);
    
// precess earth
//    rotate_arb(rotax, yhat, 1.0/sec_per_26k*2*M_PI/60);
    rotate_z(rotax, 1.0/sec_per_26k*2*M_PI/60);
    precess_phase += 1.0/sec_per_26k*2*M_PI/60;
    // rotate earth orientation vector
    earth_or=rotate_arb(earth_or, rotax, 1.0/sec_per_day*2*M_PI/60);

    //renormalize to stop weirdness
    earth=earth/norm(earth) * earth_orbit_radius;
     
//    rotate_z(earth, 1.0/sec_per_year*2*M_PI/60);
//    rotate_z(earth_to_moon, 1.0/sec_per_month*2*M_PI/60);

    vector earth0=earth;
    rotate_z(earth, precess_phase*factor);
    for (int i=0; i<12; i++)
    {
      rotate_z(earth, M_PI/6);
      if (i==11) lin((earth - earth0),(earth*-10 - earth0));
      // draw Earth
      lit_globe(earth - earth0, rotax*earth_radius, earth_or, rearth,gearth,bearth, axialtilt);
      obs=sin(latitude)*rotax + cos(latitude)*earth_or;

      int tod;
      if (obs*earth < 0) tod=1; else tod=0;
      if (axis) arrow(earth+rotax*earth_radius - earth0,rotax*4*earth_radius,0,1,0);

    }
    rotate_z(earth, -precess_phase*factor);

    // project rotation axis onto xy plane
    vector winter = (rotax*xhat)*xhat + (rotax*yhat)*yhat;
    winter = winter / norm(winter) * 1.65;

    printf("t3 %e %e %e\nWinter\n",winter.x-earth.x-0.05,winter.y-earth.y,winter.z-earth.z);
    rotate_z(winter,M_PI/2);
    printf("t3 %e %e %e\nSpring\n",winter.x-earth.x-0.05,winter.y-earth.y,winter.z-earth.z);
    rotate_z(winter,M_PI/2);
    printf("t3 %e %e %e\nSummer\n",winter.x-earth.x-0.05,winter.y-earth.y,winter.z-earth.z);
    rotate_z(winter,M_PI/2);
    printf("t3 %e %e %e\nAutumn\n",winter.x-earth.x-0.05,winter.y-earth.y,winter.z-earth.z);

/*    for (int i=0; i<12; i++)
    {
      rotate_z(earth, M_PI/6);
      // draw Earth
      lit_globe(earth - earth0, rotax*earth_radius, earth_or, rearth,gearth,bearth, axialtilt);
      obs=sin(latitude)*rotax + cos(latitude)*earth_or;

      int tod;
      if (obs*earth < 0) tod=1; else tod=0;

    }
*/

    // draw observer
    //    if (tod==1) 
//      printf("C 1 0.5 0\n");
//    else 
//      printf("C 0.4 0.2 0\n");
//   printf("!earth_radius = %e; magnitude of rotax = %e; magnitude of earth_or = %e\n",earth_radius, norm(rotax), norm(earth_or));
//   printf("c3 %e %e %e %e\n",earth.x+obs.x*earth_radius*1.1 - earth.x, earth.y+obs.y*earth_radius*1.1 - earth.y, earth.z+obs.z*earth_radius*1.1 - earth.z, earth_radius * 0.1);
// draw arrow in direction of observer
//    if (tod==1) 
//      arrow(earth+obs*earth_radius*1.1 - earth,obs*3*earth_radius,rarrow,garrow,barrow);
//    else
//      arrow(earth+obs*earth_radius*1.1 - earth,obs*3*earth_radius,rarrow*0.8,garrow*0.5,barrow*0.2);
    
// draw rotation axis

// draw moon
//    lit_globe(earth_to_moon, rotax*moon_radius, earth_or, rmoon,gmoon,bmoon, axialtilt);
//    printf("C %e %e %e\n",rmoon, gmoon, bmoon);
//    printf("c3 %e %e %e %e\n",earth_to_moon.x,earth_to_moon.y,earth_to_moon.z,moon_radius);


// write constellation names at r=Rconst 
   

  if (1)
   {
   vector Vc=zv;
   Vc.x=0.1; 
   
//   ring(zv-earth,6,zhat); 

   Vc=zv; Vc.x=Rconst;
   rotate_z(Vc,-0.45);

     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nTau.\n",Vc.x - earth.x,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nGem.\n",Vc.x - earth.x,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nCan.\n",Vc.x - earth.x,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nLeo\n",Vc.x - earth.x,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nVir.\n",Vc.x - earth.x,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nLib.\n",Vc.x - earth.x,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nScor.\n",Vc.x - earth.x,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nSag.\n",Vc.x - earth.x,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nCap.\n",Vc.x - earth.x,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nAqu.\n",Vc.x - earth.x,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nPis.\n",Vc.x - earth.x,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nAri.\n",Vc.x - earth.x,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);

   Vc = Vc * 1.1;

   for (int i=0; i<12; i++)
   {
     arrow (Vc-earth, Vc*0.2,1,1,1); rotate_z(Vc,M_PI/6.);
   }

    
   Vc=zv; Vc.x=0.8;
   rotate_z(Vc,-0.35+precess_phase*factor);
   
   double offset = 0.01;
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nDec\n",Vc.x - earth.x - offset,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nJan\n",Vc.x - earth.x - offset,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nFeb\n",Vc.x - earth.x - offset,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nMar\n",Vc.x - earth.x - offset,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nApr\n",Vc.x - earth.x - offset,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nMay\n",Vc.x - earth.x - offset,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nJune\n",Vc.x - earth.x - offset,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nJuly\n",Vc.x - earth.x - offset,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nAug\n",Vc.x - earth.x - offset,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nSept\n",Vc.x - earth.x - offset,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nOct\n",Vc.x - earth.x - offset,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);
     if (earth * Vc > 0) printf("C 1 1 1\n"); else printf("C 0.7 0.5 0.5\n");
   printf("t3 %e %e %e\nNov\n",Vc.x - earth.x - offset,Vc.y - earth.y,Vc.z - earth.z); rotate_z(Vc,M_PI/6.);


//    rotate_z(earth, precess_phase);
//     printf("C 0.5 0.5 1\n");
//     lin((earth - earth),(earth*10 - earth));

//     printf("C 0.6 0.6 0\n");
//     lin((earth - earth),(earth*-10) - earth);
//    rotate_z(earth, -precess_phase);

     printf("lightfrom %e %e %e\n",-earth.x,-earth.y,-earth.z);
     printf("font large\n");
     double year = 2020 - precess_phase * 26000 / (2*M_PI);
     printf("T -0.9 -0.9\n");
     printf("Earth orbit in year %d\n",(int)year);
     printf("font medium\n");
}
  }
}

