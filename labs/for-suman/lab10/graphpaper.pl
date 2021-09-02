print "#h 0.9 w 1.2 lx \"Rolls (1 small box = 1/2 roll)\" ly \"Dice remaining\"\n";
print "#x 0 20\n";
print "#y 0 120\n";

for ($x = 0; $x < 20; $x++)
{
  if ($x%5==0) {print "#m 1\n";} else {print "#m 2\n";}
  print "#cm 0\n$x 0\n$x 120\n";
  print "#m 4 cm 1\n";
  printf "%e 0\n%e 120\n",$x+0.5,$x+0.5;
}

print "#cm 0\n";

for ($x = 0; $x < 120; $x+=5)
{
  if ($x%20==0) {print "#m 1\n";} else {print "#m 2\n";}
  print "0 $x\n20 $x\n";
}
