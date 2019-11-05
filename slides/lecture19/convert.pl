$c=3e8;
while (<STDIN>)
{
	chomp;
	($el, $z, $be)=split;
	print "$el:\n";
	$jkg = (8.79 - $be) / 941 * $c**2;
	$mjkg = $jkg/1e6;
	$gjtonprev = $gjton;
        $gjton = $jkg / 1e6;

	printf "$el: %e seconds, %e hours, %e days, %e years\n",$gjton,$gjton/3600,$gjton/3600/24,$gjton/3600/24/365;
}
printf "Coal \t\t %e seconds per ton\n",24/277778 * 3600;
printf "Gas \t\t %e seconds per ton\n",54/277778* 3600;
