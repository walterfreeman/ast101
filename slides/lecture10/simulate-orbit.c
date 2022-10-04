#include <stdio.h>
#include <math.h>
#include "vector.h"

double GM=4*M_PI*M_PI;
double step=0.01;

void draw_planet(vector position)
{
  printf("C 0.5 0.5 1\n");
  printf("ct3 0 %e %e %e %e\n",position.x,position.y,position.z,0.05);
  printf("C 1 0.5 0.5\n");
  printf("c3 0 0 0 0.1\n");
  printf("F\n");
}

int main(void)
{
  // these lines just tell the computer what quantities it will need to keep track of and calculate
  vector earth_position(1,0,0);                             
  vector earth_velocity(0,6.2,0);
  vector gravitational_accel;
  double radius;
  vector direction;
  
  while (1)
  {
    radius = mag(earth_position);                           // calculate the distance from Earth to Sun
    direction = -1 * earth_position/radius;                 // calculate the direction gravity goes (back toward Sun)

    gravitational_accel = GM / (radius*radius) * direction; // Newton's law of gravity
    earth_velocity += gravitational_accel * step;           // acceleration is rate of change of velocity
    earth_position += earth_velocity * step;                // velocity is rate of change of position
    draw_planet(earth_position);                            // draw the Earth and Sun on the screen
  }
}

