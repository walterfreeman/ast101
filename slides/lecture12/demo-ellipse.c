#include <stdio.h>
#include <math.h>
#include "vector.h"

int main(void)
{
  vector position; position.x=1; position.y=0; position.z=0; 
  vector velocity; velocity.x=0; velocity.y=2; velocity.z=0; 
  
  double time, timestep = 0.001;
  vector acceleration;
  double GM = 4*M_PI*M_PI;

  while (true)
  {
    time = time + timestep;
    position = position + velocity * timestep;
  //  printf("%e %e %e position\n",position.x,position.y,position.z);
    acceleration = GM/(position*position) * inward(position);
   // printf("%e %e %e acceleration\n",acceleration.x,acceleration.y,acceleration.z);
    velocity = velocity + acceleration * timestep;
   
    draw_sun();
    draw_earth(position);
    animate();
  }
}
    
