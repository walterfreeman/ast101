$c1=shift;
$w1=shift;
$a1=shift;
$c2=shift;
$w2=shift;
$a2=shift;

for ($x=0; $x<7; $x+=0.01)
{
  $y=$a1*exp(-($x-$c1)**2/($w1**2));
  $y+=$a2*exp(-($x-$c2)**2/($w2**2)) if $a2>0;
  print "$x $y\n";
}
