$x=1;
$y=0;
$vx=3.14159*0.8;
$vy=3.14159*1.4;
$t=0;
$dt=0.0001;
$GM = 3.14159**2*4;
print "#x -1.5 1.5 y -1.5 1.5\n";

#@stops  = (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);
#@labels = ("A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L");
#@labels = ("Jan 1","Feb 1", "Mar 1", "Apr 1", "May 1","Jun 1", "Jul 1", "Aug 1", "Sep 1", "Oct 1", "Nov 1", "Dec 1");

#@stops = (0, 1, 5, 5.33, 5.66, 6, 6.33, 6.66, 7);
#@labels = ("Jan 1", "Feb 1", "A", "B", "C", "D", "E", "F","G");

print "#cs 0.8\n";
$st=0;

#print "circ 0 0 0.05\n";
for ($i=0; $i<8; $i++)
{
    $th=3.14159*0.25*$i;
    #    printf "line %e %e %e %e\n",0.05*sin($th),0.05*cos($th),0.08*sin($th), 0.08*cos($th);
}
$mode=2;

#if ($mode == 1) {$a=shift @labels; push @labels,$a;}

while (1)
{
    $oldx=$x;
    $oldy=$y;
    $x += $vx * $dt/2;
    $y += $vy * $dt/2;
    $r = sqrt($x**2 + $y**2);
    $vx -= $GM * $x / ($r**3)*$dt;
    $vy -= $GM * $y / ($r**3)*$dt;
    $x += $vx * $dt/2;
    $y += $vy * $dt/2;
    print "line $oldx $oldy $x $y\n";
    $t+=$dt;
    if (($oldy < 0 && $y > 0) && $stage != 2 && $t > 0.1) {$stage = 2; $year=$t;}

    if ($stage == 2)
    {
	if ($st >= @stops) {last;}
	#	printf "year is $year: %e vs. %e\n",(($t - $year) / $year), $stops[$st]/12.0;
	if ((($t - $year) / $year) >= $stops[$st]/12.0 && $mode == 1) {$advance = 1;}

	$ang = atan2($y,$x);
	if ($ang<0) {$ang+=3.14159*2;}
	if ($ang > $st*3.14159/6 && $mode==2) {$advance=1;}



if ($advance)
	{
	    $advance=0;
	    print "fillcirc $x $y 0.05\n";
	    printf "%e %e \"$labels[$st]\"\n",$x+($x/$r)*0.2-0.07,$y+($y/$r)*0.2;
	    $st++;
	}
    }
}

