print "#g 0 cs 0.85 h 0.8 x -1 2\n";
print "#cs 0.1\n";
print "-0.99 0 \".\"\n";
print "1.99 0 \".\"\n";

printf "#cs 2\n0.5 %e \"\\oc\"\n",-13.6/4;
print "#cs 0.85\n";

for ($n=1;$n<8;$n++)
{
  $e=-13.6/$n/$n;
  printf "0 $e\n1 $e\n#\n";
  printf "1.05 $e \"n=$n: %.1f eV\"\n",$e if $n<4;
#  printf "0.1 1 \"E>0: electron escapes from atom\"\n";
}

for ($e=-13.6/1; $e<-13.6/9; $e+=0.01)
{
  printf "%e %e\n",0.2+sin($e*10)*0.03,$e
}


print "#\n-0.9 -6 \"n=1 to n=3: 12.1 eV (UV)\n";

print "#cm 1\n";
for ($e=-13.6/4; $e<-13.6/9; $e+=0.01)
{
  printf "%e %e\n",0.5+sin($e*10)*0.03,$e
}

print "#\n0.6 -2.4 \"n=3 to n=2: 1.9 eV (red)\n";
exit;
print "#cm 0\n";
for ($e=-13.6/1; $e<-13.6/4; $e+=0.01)
{
  printf "%e %e\n",0.8+sin($e*10)*0.03,$e
}

print "#\n0.9 -6 \"n=2 to n=1: 10.2 eV (UV)\n";



