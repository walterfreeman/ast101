/**********************************************
Blackbody simulator
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
#include <string.h>
#define timing_hack 1
#define ANIM_FONT GLUT_BITMAP_HELVETICA_18

int window_size=800,window_size_x=800,window_size_y=800;

int inverse=1;
int first=1;
int autoscale=0;
double emin=1;
double emax=10;
double t=4000;
double maxamp=-1;
double dmaxamp=1;
double lmin=351;
double lmax=800;
double h=0;
double he=0,hg=0;
double ampl(double l, double t);

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

    // handle spectral lines:
    factor *= inverse;
    double width=0.2;
    if (h)
    {
      for (int i=3;i<7;i++)
      {
        double e=13.6/(2*2)-13.6/(i*i);
        double ll=1240/e;
        double f=exp(-(wavelength-ll)*(wavelength-ll)/(width));
        printf("wavelength is %.2f factor is %e\n",wavelength,f);
        factor-=f*(inverse-0.5)*2;
    }
  }

  if (he)
  {
    double lines[7]={587.5, 667.8, 686.7, 706.5, 781.3, 501.5, 388.8};
      for (int i=0;i<7;i++)
      {
        double ll=lines[i];
        double f=exp(-(wavelength-ll)*(wavelength-ll)/(width));
        printf("wavelength is %.2f factor is %e\n",wavelength,f);
        factor-=f*(inverse-0.5)*2;
      }
   }

  if (hg)
  {
    double lines[4]={435.8, 546.1, 404.7, 578.2};
      for (int i=0;i<4;i++)
      {
        double ll=lines[i];
        double f=exp(-(wavelength-ll)*(wavelength-ll)/(width));
        printf("wavelength is %.2f factor is %e\n",wavelength,f);
        factor-=f*(inverse-0.5)*2;
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

  int l=strlen(string);
  x-=l*5.0*(2.0/window_size); // shift left so center, not left, is at coords

  glRasterPos3f(x, y,z);
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
 usleep(15000);
}

void disp(void)
{
  maxamp=-10;
  double lastx,x;
  char thestring[60];
  glBegin(GL_LINES);
  double r=0, g=0, b=0;
  
  for (double l=300; l<800; l++)
  {
    getcolorrgb(l,r,g,b);
  }
  if (r>g && r>b) {g/=r; b/=r; r=1;}
  else if (g>r && g>b) {r/=g; b/=g; g=1;}
  else if (b>g && b>r) {r/=b; g/=b; b/=b;}

  glColor4f(r,g,b,1);
//  for (double x=-0.9; x<0.9; x+=1.8/window_size)
//  {
//    glVertex3f(x,.7,0);
//   glVertex3f(x,.8,0);
//  }
   
    for (double l=lmin; l<lmax; l+=(lmax-lmin)/(window_size))
    {
      double e=1240/l;
      setcolor(l);
      double x=getx(l), y=1;
      glVertex3f(x,-0.3,0);
      glVertex3f(x,0.3,0);
     
   }
   glEnd();
   glColor4f(0,0,0,0.6);
 
  glEnd();
  // draw frame
  glBegin(GL_LINE_STRIP);
  glColor4f(0,0,0,1);
  glVertex3f(-0.9,-0.4,0);
  glVertex3f(0.9,-0.4,0);
  glVertex3f(0.9,0.4,0);
  glVertex3f(-0.9,0.4,0);
  glVertex3f(-0.9,-0.4,0);
  glEnd();
    lastx=-10;
  double lstep;
  if (lmax-lmin < 10) lstep=1;
  else if (lmax - lmin < 20) lstep=2;
  else if (lmax - lmin < 50) lstep=5;
  else if (lmax - lmin < 100) lstep=10;
  else if (lmax - lmin < 200) lstep=20;
  else if (lmax - lmin < 500) lstep=50;
  else if (lmax - lmin < 1000) lstep=100;
  else if (lmax - lmin < 2000) lstep=200;
  else if (lmax - lmin < 5000) lstep=500;
  else if (lmax - lmin < 10000) lstep=1000;
  else if (lmax - lmin < 20000) lstep=2000;
  else lstep=5000;
 
  double linit=(int)(lmin/lstep)*lstep;

  for (double l=linit; l<lmax; l+=lstep)
  {
    
    double e=1240/l;
    x=getx(l);
    if (fabs(x)>0.9) continue;
  glBegin(GL_LINES);
    glVertex3f(x,-0.48,0);
    glVertex3f(x,-0.4,0);
  glEnd();
    sprintf(thestring,"%d",(int)l);
    glColor4f(0,0,0,1);
    if (x-lastx > 0.2)
    {
    lastx=x;
    renderBitmapString(x,-0.64,0,GLUT_BITMAP_HELVETICA_18,thestring);
    }
  } 
  lastx=-10;
  // figure out energy marks; let's aim for 5-10.
  double erange=1240/lmin - 1240/lmax;
  double emin=1240/lmax, emax=1240/lmin;
  double dec;
  int prec;
  if (erange < 0.1) {dec=0.01; prec=2;}
  else if (erange < 0.2) {dec=0.02; prec=2;}
  else if (erange < 0.5) {dec=0.05; prec=2;}
  else if (erange < 1) {dec=0.1; prec=1;}
  else if (erange < 2) {dec=0.2; prec=1;}
  else if (erange < 5) {dec=0.5; prec=1;}
  else if (erange < 10) {dec=1; prec=0;}
  else if (erange < 20) {dec=2; prec=0;}
  else   {dec=5; prec=0;}
  
  emax = (int)(emax/dec)*dec; //round
  for (double e=emax; e>=emin; e-=dec)
  {
    // dynamically adjust stuff if energy gets too small to account for IR


    x=getx(1240/e);
    if (x < 0.3 && e-emin < dec*2)
    {
      // do some horrid hackish thing to bump decrement down by one click
      int digit=pow(10,log10(dec)-(int)log10(dec)+1);
 
      if (digit == 10) dec/=2; // it's a one
      else if (digit == 2) dec/=2; // it's a two
      else dec *= 0.4; // it's a five
    }

    if (fabs(x)>0.9) continue;
  glBegin(GL_LINES);
    glVertex3f(x,0.48,0);
    glVertex3f(x,0.4,0);
  glEnd();
    prec=-log10(dec)+0.9;
    sprintf(thestring,"%.*f",prec,e);
  glColor4f(0,0,0,1);
    if (x-lastx > 2.0/window_size*(15*(prec+1)))
    {
    lastx=x;
    renderBitmapString(x,0.55,0,GLUT_BITMAP_HELVETICA_18,thestring);
    }
  } 
  sprintf(thestring,"Energy per photon (eV)");
  renderBitmapString(0,0.72,0,GLUT_BITMAP_HELVETICA_18,thestring);
  sprintf(thestring,"Wavelength (nanometers)");
  renderBitmapString(0,-0.85,0,GLUT_BITMAP_HELVETICA_18,thestring);
  
  if (autoscale)
  {
  sprintf(thestring,"Autoscale enabled");
    renderBitmapString(0,0.6,0,GLUT_BITMAP_HELVETICA_18,thestring);
  }
   glutSwapBuffers();
  glClear(GL_COLOR_BUFFER_BIT);
}



void resize(int w, int h)
{
  window_size_x=w;
  window_size_y=h;
  if (h>w) window_size=h; else window_size=w;
   glViewport(0,0,w,h);
}

void keyb(unsigned char key, int x, int y)
{
  if (key == 'Q') {exit(0);}
  if (key == 'q') {lmin*=1.01;}
  if (key == 'w') {lmin/=1.01;}
  if (key == 'a') {lmax*=1.01;}
  if (key == 's') {lmax/=1.01;}
  if (key == 'i') {inverse=1-inverse;}
  if (key == 'h') {h=1-h;}  
  if (key == 'H') {he=1-he;}  
  if (key == 'm') {hg=1-hg;}
  if (key == ' ') {dmaxamp=maxamp;}
  if (key == 'S') {autoscale=1-autoscale;}
  glutPostRedisplay();
}


int main(int argc, char **argv)
{
  printf("Controls: \n");
  printf("\tshift-Q : quit\n");
  printf("\tq/w     : change minimum wavelength\n");
  printf("\ta/s     : change maximum wavelength\n");
  printf("\ti       : toggle inverse (emission/absorption)\n");
  printf("\th       : toggle Balmer series ([h]ydrogen lines)\n");
  printf("\tH       : toggle [H]elium lines\n");
  printf("\tm       : toggle [m]ercury lines\n");
  printf("\t<space> : rescale amplitude\n");
  printf("\tshift-S : toggle automatic amplitude scaling\n");

  if (argc == 2)
  {
    sscanf(argv[1],"%d",&window_size);
  }
  //INITIALIZATION
  glutInit(&argc, argv);

  //set rgba and double buffering  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE |  GLUT_MULTISAMPLE);

  //set window size and position and title
  glutInitWindowSize(1600,350);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Thermal Radiation Demo");

  //SET CALLBACKS
  glutDisplayFunc(disp);
  glutKeyboardFunc(keyb);
//  glutIdleFunc(idle);
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
