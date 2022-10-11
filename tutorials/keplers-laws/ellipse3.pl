$x=1;
$y=0;
$vx=3.14159*0.8;
$vy=3.14159*1.4;
$t=0;
$dt=0.0001;
$GM = 3.14159**2*4;
print "#x -1.5 1.5 y -1.5 1.5\n";

@stops  = (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);
@labels = ("A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L");
@labels = ("Jan 1","Feb 1", "Mar 1", "Apr 1", "May 1","Jun 1", "Jul 1", "Aug 1", "Sep 1", "Oct 1", "Nov 1", "Dec 1");

#@stops = (0, 1, 5, 5.33, 5.66, 6, 6.33, 6.66, 7);
#@labels = ("Jan 1", "Feb 1", "A", "B", "C", "D", "E", "F","G");

print "#cs 0.8\n";
$st=0;

print "circ 0 0 0.05\n";
for ($i=0; $i<8; $i++)
{
    $th=3.14159*0.25*$i;
        printf "line %e %e %e %e\n",0.05*sin($th),0.05*cos($th),0.08*sin($th), 0.08*cos($th);
}
$mode=1;

print "-.4 -.2 \"\\cr\"\n";
