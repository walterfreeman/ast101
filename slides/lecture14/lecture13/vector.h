
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

double operator*(vector b, vector a)
{
  return a.x*b.x + a.y*b.y + a.z*b.z;
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

vector inward(vector a)
{
  return a * (-1.0/sqrt(a.x*a.x + a.y*a.y + a.z*a.z));
}


void draw_sun(void)
{
  printf("C 1 1 0\nc3 0 0 0 0.1\n");
}

void animate(void)
{
  printf("F\n");
}

void draw_earth(vector r)
{
  printf("C 0.5 0.5 1\nc3 %e %e %e 0.05\n",r.x,r.y,r.z);
}

