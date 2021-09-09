print <<EOF;
nsegs 200
dcirc 0 0 1.5
#cm 3
circ 0 1.5 0.4
arc 0 1.5 0.8 -30 90
arrowhead 1.5 2.3 0 2.3
#cs 0.8
-1.7 2.4 "1 day"
#cm 1
arc 0 0 2 180 270
arrowhead -3 -2 0 -2 
circ 0 0 0.2
0.5 -2 "1 year"
#cm 4
stickfig 0 1.9 0 2.2
EOF

$pi=3.14159265;
$r1=8.5;
$r2=9.5;
$r3=0.2;
$r4=0.4;
$r5=8;
@const=("Aries", "Taurus", "Gemini", "Cancer", "Leo", "Virgo", "Libra", "Scorpio", "Sagittarius", "Capricornus", "Aquarius", "Pisces",);
@xoff=(-1,-1,0,-1.5,0,-0.5,-1,-2.5,-3,-1.5,-1,-1);
@yoff=(0,0,0,0,0,0,0,0,0,0,0,0);

if (0)
{
print <<EOF;
#cm 0
2.2 1.5 "Winter"
-4.2 -1.5 "Summer"
-2 4 "Spring"
2 -4 "Fall"
EOF
}

$i=11;
for ($th=0; $th<$pi*2; $th+=$pi/6)
{
	print "#cm 1\n";
	printf "line %e %e %e %e\n",$r3*sin($th), $r3*cos($th), $r4*sin($th), $r4*cos($th);
	print "#cm 2\n";
	printf "arrow %e %e %e %e\n",$r1*sin($th), $r1*cos($th), $r2*sin($th), $r2*cos($th);
	printf "%e %e \"to $const[$i]\"\n",$r5*sin($th)+$xoff[$i], $r5*cos($th)+$yoff[$i];
	$i--;
}

