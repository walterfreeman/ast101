$hl=shift;
$el=shift;
$skip=shift;
$lg=shift;
$max=shift;
$unit=shift;

print "#y l r 0.05\n" if $lg;

print "#h 0.5 lx \"Time ($unit of years)\" ly \"Percentage of original $el\"\n";
printf "#x 0 %e\n",$hl*$max;
$dt=$hl/80;
if ($skip==1)
{
for ($t=0;$t<$hl*($max+1);$t+=$dt)
{
  print "#cm 1\n";
  $pct=100*2**(-$t/$hl);
  for ($y=0;$y<$pct;$y+=0.2)
  {
    printf "$t $y\n%e $y\n#\n",$t+$dt;
  }
  print "#cm 2\n";
  for ($y=$pct;$y<100;$y+=0.2)
  {
    printf "$t $y\n%e $y\n#\n",$t+$dt;
  }
}
}
else
{
for ($t=0;$t<$hl*$max;$t+=$dt)
  {
    $pct=100*2**(-$t/$hl);
    print "$t $pct\n";
  }
print "#cm 1\n";

$min=0;
$min=100*2**-$max if $lg;

for ($l=1;$l<=$max;$l+=1)
{
  printf "%e %e\n%e %e\n%e %e\n#\n",$min,100*2**-$l,$l*$hl,100*2**-$l,$l*$hl,$min;
}

if ($skip<1)
{
    printf "%e %e\n%e %e\n%e %e\n#\n",100,100*2**-$l,$l*$hl,100*2**-$l,$l*$hl,100;
}
}

