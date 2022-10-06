struct vector
{
  double x;
  double y;
  double z;
  vector(double x, double y, double z) : x(x), y(y), z(z) {}
  vector() {}
};

typedef struct
{
  int x;
  int y;
  int z;
} ivec;



  vector operator+(const vector& a, const vector& b)
  {
    return vector(a.x+b.x, a.y+b.y, a.z+b.z);;
  }

  double operator*(const vector& a, const vector& b)
  {
    return a.x*b.x + a.y*b.y + a.z*b.z;
  }

  vector operator^(const vector& a, const vector& b)
  {
     vector c;
    c.x=a.y*b.z - a.z*b.y;
    c.y=a.z*b.x - a.x*b.z;
    c.z=a.x*b.y - a.y*b.x;
    return c;
  }

  vector operator*(const double& a, const vector& b)
  {
    return vector(a*b.x, a*b.y, a*b.z);
  }

  vector operator*(const vector& a, const double& b)
  {
    return vector(a.x*b, a.y*b, a.z*b);
  }

  vector operator-(const vector& a, const vector& b)
  {
    return vector(a.x-b.x, a.y-b.y, a.z-b.z);
  }

  vector operator/(const vector& a, const double& b)
  {
    return vector(a.x/b, a.y/b, a.z/b);
  }

  void operator+=(vector& a, const vector b)
    {
    a=a+b;
    }

  void operator-=(vector& a, const vector b)
    {
    a=a-b;
    }

  double radius( vector BD1, vector BD2 ){
    return sqrt( (BD1 - BD2) * (BD1 - BD2) );//FIXME Does this file need to include math.h to get sqrt()?
  }

  double mag (vector v)
  {
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
  } 
  double norm (vector v)
  {
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
  }
