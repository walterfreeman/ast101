$ths=0.1;
for ($theta = 0; $theta < 2*3.14159; $theta += $ths)
{

    printf "line %e %e %e %e\n",8*sin($theta), 1.2*cos($theta), 8*sin($theta+$ths), 1.2*cos($theta+$ths);
    printf "line %e %e %e %e\n",8*cos($theta), 8*sin($theta), 8*cos($theta+$ths/2), 8*sin($theta+$ths/2) if $theta < 3.14159;
}

print "#cm 2\n";
for ($theta = -.3; $theta < 3.14159*.6; $theta += $ths*2)
{
    printf "line %e %e %e %e\n",8*sin($theta), 1.2*cos($theta), 8*sin(3.14159*1.5-$theta), 1.2*cos(3.14159*1.5-$theta);
}
for ($theta = 1.3; $theta < 3.8; $theta += $ths*2)
{
    printf "line %e %e %e %e\n",8*sin($theta), 1.2*cos($theta), 8*sin(3.14159*2.5-$theta), 1.2*cos(3.14159*2.5-$theta);
}

print "#cm 0\n";

print "#cs 1\n";
print <<END;
-.5 1.7 "East"
#cs 1.8
0 1.2 "\\cr"
0 1.2 "\\pl"
END

