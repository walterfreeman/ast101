#include <stdio.h>
#include <math.h>
#include "vector.h"

int main(void)
{
  vector position; position.x=1; position.y=0; position.z=0; 
  vector velocity; velocity.x=0; velocity.y=4; velocity.z=0; 
  vector oldvel=velocity;
  double time, timestep = 0.0005;
  vector acceleration;
  vector lastpos; lastpos=position*0;
  double GM = 4*M_PI*M_PI;
  int signchange=0,step=0;
  char symbol[4]=" PA";
  printf("#g 0 x -1.2 1.2 y -1.2 1.2\n");
  for (double th=0; th<7; th+=0.2)
  {
    printf("%e %e\n",sin(th)*0.06,cos(th)*0.06);
  }
  printf("#\n");
  while (signchange < 2)
  {
    oldvel=velocity;
    time = time + timestep;
    position = position + velocity * timestep/2;
    acceleration = GM/(position*position) * inward(position);
    velocity = velocity + acceleration * timestep;
    position = position + velocity * timestep/2;
     if (oldvel.x * velocity.x < 0)
    {
      fprintf(stderr,"sign change\n");
      signchange++;
      printf("%e %e \"\\cr\"\n",position.x,position.y);
      printf("%e %e \"%c\"\n",position.x*1.15-0.04,position.y,symbol[signchange]);
    }
   if ((position - lastpos)*(position-lastpos) > pow(0.03,2))
   {
     step++;
     printf("#\n");
     lastpos=position;
   }
    if (step % 2 == 0) 
    printf("%e %e\n",position.x,position.y);
  }
}
    
