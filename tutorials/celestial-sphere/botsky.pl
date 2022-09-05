use Math::Trig;
print "#x -11 11\n";
print "#y -11 11\n";
print "rect -10.5 -10.5 10.5 10.5\n";

print "#cm 1 cs 1\ncirc 0 0 9\ncirc 0 0 8.95\ndotcirc 0 0 6 0.3\ndotcirc 0 0 0.1 0.3\n";
print "#cm 2\n";
$pt=9*cos(pi/4);
print "line 0 -9 0 9\n";
print "line -9 0 9 0\n";
print "line -$pt -$pt $pt $pt\n";
print "line $pt -$pt -$pt $pt\n";

@directions=("N","NW","W","SW","S","SE","E","NE");

$start=0;

$r=9.7;
for ($i=0; $i<8; $i++)
{
    $th=(-$i+$start)*pi/4;
    $x=cos($th)*$r;
    $y=sin($th)*$r;
    print "$x $y \"$directions[$i]\"\n";
}
print "#cm 1\n";
print "-4.8 9.1 \"Horizon\"\n";
print "-4.1 5.4 \"Below the horizon\"\n";
#print "-2.8 2.7 \"High in sky\"\n";
print "fillcirc 0 0 0.2\n";
print "-0.8 -0.5 \"Nadir\"\n";
