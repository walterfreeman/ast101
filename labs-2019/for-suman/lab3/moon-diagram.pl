$moonrad=8;
$moonlabel = $moonrad + 1.5;
print <<"EOT";
#w 1.2 x -10 14 y -10 10
arrow -9 -8 -6 -8
arrow -9 -4 -6 -4
arrow -9 -0 -6  0
arrow -9  4 -6  4
arrow -9  8 -6  8
-9 1 "Sunlight"
#m 2
circ 5 0 $moonrad
#m 1 cs 0.8 
4 $moonlabel "Moon's orbit"
4.45 0 "Earth"
circ 5 0 1
circ 5 0 1.02
circ 5 0 0.98
EOT

while (@ARGV)
{
  $a = shift;
  if ($a eq "moon")
  {
    $moonloc = shift;
    print stderr "Moon at $moonloc\n";
    $moonloc /= 180/3.14159;
    $moonx=$moonrad*cos($moonloc)+5;
    $moony=$moonrad*sin($moonloc);
    print "circ $moonx $moony 0.8\n";
    print "circ $moonx $moony 0.78\n";
    print "circ $moonx $moony 0.82\n";
  }
  if ($a eq "bisect")
  {
    $bisect=1;
  }
  if ($a eq "shade")
  {
    $moonshade=1;
  }
  if ($a eq "time")
  {
    $tod = shift;
    $obsang = $tod/24 * 2 * 3.14159;
    printf "stickfig %e %e %e %e\n",5+1*cos($obsang),1*sin($obsang),5+1.5*cos($obsang),1.5*sin($obsang);
  }
  if ($a eq "timeall")
  {
    for ($tod=0; $tod<24; $tod+=3) 
    {
      $obsang = $tod/24 * 2 * 3.14159;
      printf "stickfig %e %e %e %e\n",5+1*cos($obsang),1*sin($obsang),5+1.5*cos($obsang),1.5*sin($obsang);
    }
  }
}

if ($moonshade)
{
  printf("#cm 3\n");
  for ($x = 0; $x < 0.8; $x += 0.1)
  {
    $y = sqrt(0.8*0.8 - $x*$x);
    printf ("line %e %e %e %e\n",$moonx+$x,$moony+$y,$moonx+$x,$moony-$y);
  }
}

if ($bisect)
{
  printf("#cm 1\n");
  printf("line 5 0 $moonx $moony\n");
  for ($s = 0; $s > -0.8; $s -= 0.1)
  {
    $r = sqrt(0.8*0.8 - $s*$s);
    $r *= 3 if $s == 0;
    $x1 = -$s*cos($moonloc) - $r*sin($moonloc);
    $y1 = -$s*sin($moonloc) + $r*cos($moonloc);
    $x2 = -$s*cos($moonloc) + $r*sin($moonloc);
    $y2 = -$s*sin($moonloc) - $r*cos($moonloc);
    printf ("line %e %e %e %e\n",$moonx+$x1,$moony+$y1,$moonx+$x2,$moony+$y2);
  }
}
