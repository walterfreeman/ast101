/**********************************************
anim.c, simple animation routine using OpenGL/GLUT
Written by Walter Freeman

Compile (on Linux) with
g++ blackbody.C -lGL -lGLU -lglut -lm

Compile (on Mac) with
g++ blackbody.C -framework GLUT -framework OpenGL -framework Cocoa
**********************************************/

#include <GL/glut.h>      // for Linux
#include <GL/glext.h>      // for Linux
//#include <GLUT/glut.h>       // for Macs 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define timing_hack 1
#define ANIM_FONT GLUT_BITMAP_HELVETICA_18
int window_size=800,window_size_x=800,window_size_y=800;
int autoscale=1;

double emin=1;
double emax=10;
double t=4000;
double maxamp=-1;
double dmaxamp=1;
double lmin=200;
double lmax=800;
double h=0;
double flag;
double ampl(double l, double t);
void setcolor(double wavelength, double intensity) // ganked from an online source
{
    double factor;
    double Red,Green,Blue;

    if((wavelength >= 380) && (wavelength<440)){
        Red = -(wavelength - 440) / (440 - 380);
        Green = 0.0;
        Blue = 1.0;
    }else if((wavelength >= 440) && (wavelength<490)){
        Red = 0.0;
        Green = (wavelength - 440) / (490 - 440);
        Blue = 1.0;
    }else if((wavelength >= 490) && (wavelength<510)){
        Red = 0.0;
        Green = 1.0;
        Blue = -(wavelength - 510) / (510 - 490);
    }else if((wavelength >= 510) && (wavelength<580)){
        Red = (wavelength - 510) / (580 - 510);
        Green = 1.0;
        Blue = 0.0;
    }else if((wavelength >= 580) && (wavelength<645)){
        Red = 1.0;
        Green = -(wavelength - 645) / (645 - 580);
        Blue = 0.0;
    }else if((wavelength >= 645) && (wavelength<781)){
        Red = 1.0;
        Green = 0.0;
        Blue = 0.0;
    }else{
        Red = 0.0;
        Green = 0.0;
        Blue = 0.0;
    };

    // Let the intensity fall off near the vision limits

    if((wavelength >= 380) && (wavelength<420)){
        factor = 0.3 + 0.7*(wavelength - 380) / (420 - 380);
    }else if((wavelength >= 420) && (wavelength<701)){
        factor = 1.0;
    }else if((wavelength >= 701) && (wavelength<781)){
        factor = 0.3 + 0.7*(780 - wavelength) / (780 - 700);
    }else{
        factor = 0.0;
    };
    factor *= factor;
  if (h)
  {
    for (int i=3;i<10;i++)
    {
      double e=13.6/(2*2)-13.6/(i*i);
      double ll=1240/e;
      double f=1-exp(-(wavelength-ll)*(wavelength-ll)/(1));
      factor*=f;
    }
  }
  factor *= intensity;
    glColor4f(Red*factor,Green*factor,Blue*factor,1);
}


void setcolor(double wavelength) // ganked from an online source
{
    double factor;
    double Red,Green,Blue;

    if((wavelength >= 380) && (wavelength<440)){
        Red = -(wavelength - 440) / (440 - 380);
        Green = 0.0;
        Blue = 1.0;
    }else if((wavelength >= 440) && (wavelength<490)){
        Red = 0.0;
        Green = (wavelength - 440) / (490 - 440);
        Blue = 1.0;
    }else if((wavelength >= 490) && (wavelength<510)){
        Red = 0.0;
        Green = 1.0;
        Blue = -(wavelength - 510) / (510 - 490);
    }else if((wavelength >= 510) && (wavelength<580)){
        Red = (wavelength - 510) / (580 - 510);
        Green = 1.0;
        Blue = 0.0;
    }else if((wavelength >= 580) && (wavelength<645)){
        Red = 1.0;
        Green = -(wavelength - 645) / (645 - 580);
        Blue = 0.0;
    }else if((wavelength >= 645) && (wavelength<781)){
        Red = 1.0;
        Green = 0.0;
        Blue = 0.0;
    }else{
        Red = 0.0;
        Green = 0.0;
        Blue = 0.0;
    };

    // Let the intensity fall off near the vision limits

    if((wavelength >= 380) && (wavelength<420)){
        factor = 0.3 + 0.7*(wavelength - 380) / (420 - 380);
    }else if((wavelength >= 420) && (wavelength<701)){
        factor = 1.0;
    }else if((wavelength >= 701) && (wavelength<781)){
        factor = 0.3 + 0.7*(780 - wavelength) / (780 - 700);
    }else{
        factor = 0.0;
    };
    factor *= factor;
  if (h)
  {
    for (int i=3;i<10;i++)
    {
      double e=13.6/(2*2)-13.6/(i*i);
      double ll=1240/e;
      double f=1-exp(-(wavelength-ll)*(wavelength-ll)/(1));
      factor*=f;
    }
  }

    glColor4f(Red*factor,Green*factor,Blue*factor,1);
}

void setcolorinv(double Wavelength)
{
    double factor;
    double Red,Green,Blue;

    if((Wavelength >= 380) && (Wavelength<440)){
        Red = -(Wavelength - 440) / (440 - 380);
        Green = 0.0;
        Blue = 1.0;
    }else if((Wavelength >= 440) && (Wavelength<490)){
        Red = 0.0;
        Green = (Wavelength - 440) / (490 - 440);
        Blue = 1.0;
    }else if((Wavelength >= 490) && (Wavelength<510)){
        Red = 0.0;
        Green = 1.0;
        Blue = -(Wavelength - 510) / (510 - 490);
    }else if((Wavelength >= 510) && (Wavelength<580)){
        Red = (Wavelength - 510) / (580 - 510);
        Green = 1.0;
        Blue = 0.0;
    }else if((Wavelength >= 580) && (Wavelength<645)){
        Red = 1.0;
        Green = -(Wavelength - 645) / (645 - 580);
        Blue = 0.0;
    }else if((Wavelength >= 645) && (Wavelength<781)){
        Red = 1.0;
        Green = 0.0;
        Blue = 0.0;
    }else{
        Red = 0.0;
        Green = 0.0;
        Blue = 0.0;
    };

    // Let the intensity fall off near the vision limits

    if((Wavelength >= 380) && (Wavelength<420)){
        factor = 0.3 + 0.7*(Wavelength - 380) / (420 - 380);
    }else if((Wavelength >= 420) && (Wavelength<701)){
        factor = 1.0;
    }else if((Wavelength >= 701) && (Wavelength<781)){
        factor = 0.3 + 0.7*(780 - Wavelength) / (780 - 700);
    }else{
        factor = 0.0;
    };
    factor *= factor;

    glColor4f(1-Red*factor,1-Green*factor,1-Blue*factor,1);
}


void getcolorrgb(double Wavelength, double &r, double &g, double &b)
{
    double factor;
    double Red,Green,Blue;

    if((Wavelength >= 380) && (Wavelength<440)){
        Red = -(Wavelength - 440) / (440 - 380);
        Green = 0.0;
        Blue = 1.0;
    }else if((Wavelength >= 440) && (Wavelength<490)){
        Red = 0.0;
        Green = (Wavelength - 440) / (490 - 440);
        Blue = 1.0;
    }else if((Wavelength >= 490) && (Wavelength<510)){
        Red = 0.0;
        Green = 1.0;
        Blue = -(Wavelength - 510) / (510 - 490);
    }else if((Wavelength >= 510) && (Wavelength<580)){
        Red = (Wavelength - 510) / (580 - 510);
        Green = 1.0;
        Blue = 0.0;
    }else if((Wavelength >= 580) && (Wavelength<645)){
        Red = 1.0;
        Green = -(Wavelength - 645) / (645 - 580);
        Blue = 0.0;
    }else if((Wavelength >= 645) && (Wavelength<781)){
        Red = 1.0;
        Green = 0.0;
        Blue = 0.0;
    }else{
        Red = 0.0;
        Green = 0.0;
        Blue = 0.0;
    };

    // Let the intensity fall off near the vision limits

    if((Wavelength >= 380) && (Wavelength<420)){
        factor = 0.3 + 0.7*(Wavelength - 380) / (420 - 380);
    }else if((Wavelength >= 420) && (Wavelength<701)){
        factor = 1.0;
    }else if((Wavelength >= 701) && (Wavelength<781)){
        factor = 0.3 + 0.7*(780 - Wavelength) / (780 - 700);
    }else{
        factor = 0.0;
    };
    factor *= factor*ampl(Wavelength,t)/pow(Wavelength,1.5); // hack to make this match perception
    r+=Red*factor;
    g+=Green*factor;
    b+=Blue*factor;
}



void renderBitmapString(
    float x, 
    float y, 
    float z, 
    void *font, 
    char *string) {  
  char *c;
  glRasterPos3f(x, y,z);
  glColor4f(0,0,0,1);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}

void circle(double x, double y, double r, double n)
{ 
  glBegin(GL_LINE_STRIP);
  for (double th=0;th<2*M_PI;th+=2*M_PI/n)
  {
    glVertex3f(x+r*cos(th),y+r*sin(th),0);
  }
    glVertex3f(x+r,y,0);
  glEnd();
}

double getx(double l)
{
  return -0.9+1.8*(l-lmin)/(lmax-lmin);
}


double amp(double e, double t)
{
  double a=e*e*e * 1.0/(exp(e/(8.617e-5*t)-1));
  return a;
}

double ampl(double l, double t)
{
  double a=1.0/(l*l*l*l*l) * 1.0/(exp(1240/(l*8.617e-5*t))-1);
  return a;
}

void idle(void)
{
  maxamp=-10;
  double lastx,x;
  char thestring[60];
  usleep(15);
  glBegin(GL_LINES);
  double r=0, g=0, b=0;
  
   if (autoscale)
  {
    for (double l=lmin; l<lmax; l+=(lmax-lmin)/(window_size) * 0.5)
    {
      double e=1240/l;
      double x=getx(l);
     
      if (ampl(l,t)>maxamp && fabs(x)<0.9) 
      {
        maxamp=ampl(l,t);
      }
   }
   dmaxamp=maxamp;
  }


  for (double l=300; l<800; l++)
  {
    getcolorrgb(l,r,g,b);
  }
  if (r>g && r>b) {g/=r; b/=r; r=1;}
  else if (g>r && g>b) {r/=g; b/=g; g=1;}
  else if (b>g && b>r) {r/=b; g/=b; b/=b;}

  glColor4f(r,g,b,1);
  for (double x=-0.9; x<0.9; x+=1.8/window_size * 0.5)
  {
    glVertex3f(x,.7,0);
    glVertex3f(x,.8,0);
  }

      flag=1;
    for (double l=lmin; l<lmax; l+=(lmax-lmin)/(window_size) * 0.5)
    {
      double e=1240/l;
      double x=getx(l), y=ampl(l,t)/dmaxamp-0.8;
      setcolor(l,ampl(l,t)/maxamp);
      glVertex3f(x,-0.1,0);
      glVertex3f(x,0.1,0);
     
      if (ampl(l,t)>maxamp && fabs(x)<0.9) 
      {
        maxamp=ampl(l,t);
      }
   }
   flag=0;
   glEnd();
   glColor4f(1,1,1,0.6);
 
  glEnd();
  // draw frame

  glBegin(GL_LINE_STRIP);
  glColor4f(0,0,0,1);
  glVertex3f(-0.9,-0.2,0);
  glVertex3f(0.9,-0.2,0);
  glVertex3f(0.9,0.2,0);
  glVertex3f(-0.9,0.2,0);
  glVertex3f(-0.9,-0.2,0);
  glEnd();
    lastx=-10;
  for (double l=100; l<10000; l+=25)
  {
    
    double e=1240/l;
    x=getx(l);
    if (fabs(x)>0.9) continue;
  glBegin(GL_LINES);
    glVertex3f(x,-0.25,0);
    glVertex3f(x,-0.2,0);
  glEnd();
    sprintf(thestring,"%d",(int)l);
    glColor4f(0,0,0,1);
    if (x-lastx > 0.2)
    {
    lastx=x;
    renderBitmapString(x-0.02,-0.30,0,GLUT_BITMAP_HELVETICA_18,thestring);
    }
  } 
  lastx=-10;
  for (double e=100; e>=1; e-=0.2)
  {
    x=getx(1240/e);
    if (fabs(x)>0.9) continue;
  glBegin(GL_LINES);
    glVertex3f(x,0.25,0);
    glVertex3f(x,0.2,0);
  glEnd();
    sprintf(thestring,"%.1f",e);
  glColor4f(0,0,0,1);
    if (x-lastx > 0.2)
    {
    lastx=x;
    renderBitmapString(x-0.006,0.27,0,GLUT_BITMAP_HELVETICA_18,thestring);
    }
  } 
  sprintf(thestring,"Energy per photon (eV)");
  renderBitmapString(-0.2,0.32,0,GLUT_BITMAP_HELVETICA_18,thestring);
  sprintf(thestring,"Wavelength (nanometers)");
  renderBitmapString(-0.2,-0.35,0,GLUT_BITMAP_HELVETICA_18,thestring);
//  sprintf(thestring,"Temp = %d Kelvin (%d Fahrenheit)",(int)t,(int)((t-273)*1.8+32));
//  renderBitmapString(-0.5,0.5,0,GLUT_BITMAP_HELVETICA_18,thestring);
   glutSwapBuffers();
  glClear(GL_COLOR_BUFFER_BIT);
}

void disp(void)
{
}


void resize(int w, int h)
{
  window_size_x=w;
  window_size_y=h;
  if (h>w) window_size=h; else window_size=w;
   glViewport(0,0,w,h);
  printf("%f pixels per nm (Z6 at 70mm: %f)\n",window_size_x/(lmax-lmin),12438/2000.0);
}

void keyb(unsigned char key, int x, int y)
{
  if (key == 'Q') {exit(0);}
  if (key == 'q') {lmin*=1.01;}
  if (key == 'w') {lmin/=1.01;}
  if (key == 'a') {lmax*=1.01;}
  if (key == 's') {lmax/=1.01;}
  if (key == '=') {t+=100;}
  if (key == '-') {t-=100;}
  if (key == 'h') {h=1-h;}  
  if (key == ' ') {dmaxamp=maxamp;}
  if (key == 'S') {autoscale = 1-autoscale;}
  printf("%f pixels per nm (Z6 at 70mm: %f)\n",window_size_x/(lmax-lmin),12438/2000.0);
}


int main(int argc, char **argv)
{
  if (argc == 2)
  {
    sscanf(argv[1],"%d",&window_size);
  }
  //INITIALIZATION
  glutInit(&argc, argv);

  //set rgba and double buffering  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE |  GLUT_MULTISAMPLE);

  //set window size and position and title
  glutInitWindowSize(window_size,window_size);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Thermal Radiation Demo");

  //SET CALLBACKS
  glutDisplayFunc(disp);
  glutKeyboardFunc(keyb);
  glutIdleFunc(idle);
  glutReshapeFunc(resize);
  //DO OPENGL INIT
  glEnable(GL_BLEND);
  glEnable(GL_MULTISAMPLE);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(1.0, 1.0, 1.0, 1.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
    
  glutMainLoop();
}
