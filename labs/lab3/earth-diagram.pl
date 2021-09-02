$r = 8;

$pi=3.14159;
$th = 22.3 * $pi / 180;

print "circ 0 0 $r\n";

print "#cm 1\n";

print "line 0 8 0 -8\n";

print "#cm 2 m 2\n";
printf "line %e %e %e %e\n",$r * cos(0 ), $r * sin(0 ), $r * cos($pi-2*$th ), $r * sin ($pi-2*$th ); # capricorn
printf "line %e %e %e %e\n",$r * cos($pi ), $r * sin($pi ), $r * cos(-2*$th ), $r * sin (-2*$th ); #cancer
print "#cm 3 m 1\n";
printf "line %e %e %e %e\n",$r * cos(-$th ), $r * sin(-$th ), $r * cos($pi-$th ), $r * sin ($pi-$th ); #equator
print "#cm 4 m 2\n";
printf "line %e %e %e %e\n",$r * cos($pi/2 ), $r * sin($pi/2 ), $r * cos($pi/2-2*$th ), $r * sin ($pi/2-2*$th ); #arc
printf "line %e %e %e %e\n",$r * cos(3*$pi/2 ), $r * sin(3*$pi/2 ), $r * cos(3*$pi/2-2*$th ), $r * sin (3*$pi/2-2*$th );#antarc
print "#cm 2 m 3\n";
printf "line %e %e %e %e\n",$r * cos($pi/2-$th ), $r * sin($pi/2-$th ), $r * cos(3*$pi/2-$th ), $r * sin (3*$pi/2-$th );#axis

