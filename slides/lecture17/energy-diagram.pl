$offset=2;

for ($i=1; $i<5; $i++)
{
  $en[$i]=13.6-13.6/($i*$i);
}

@en=(0,0,4,7,9,10);

$n=5;
$emax=$en[$n] + $offset;

$emax2=$emax*1.05;
print "#x -$emax2 $emax2 y -$emax2 $emax2\n"; 

print "#g 0 cs 0.5\n";

for ($i=1; $i<=$n; $i++)
{
  for ($th=0; $th<3.14159265*2; $th=$th+0.0314159265)
  {
    if (abs(sin($th)*($en[$i]+$offset)) > $emax * 0.11 || cos($th)<0 || $i==1)
    {
    printf "%e %e\n",sin($th)*($en[$i]+$offset),cos($th)*($en[$i]+$offset);
    }
    else {printf("#\n");}
  }
  $yo=0;
  $yo=$emax*0.05 if $i==1;
  printf "#\n%e %e \"n=$i E=%.1f\"\n",-$emax*0.08,$en[$i]+$yo+$offset,$en[$i];
}
