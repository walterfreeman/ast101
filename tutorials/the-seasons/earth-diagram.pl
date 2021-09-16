$th=23 * 3.14159/180;
$ph=3.14159/2-$th;
$sy=3.14159/4;

print <<END;
circ 0 0 9
circ 0 0 8.98
circ 0 0 8.96
END

printf "#cm 3 m 2\nline %e %e %e %e\n",9*sin($th),9*cos($th),-9*sin($th),9*cos($th);
printf "#cm 3 m 2\nline %e %e %e %e\n",9*sin($th),-9*cos($th),-9*sin($th),-9*cos($th);
printf "#cm 3 m 1\nstickfig %e %e %e %e\n",-9*sin($th),9*cos($th),-9.8*sin($th),9.8*cos($th);
printf "#cm 1 m 2\nline %e %e %e %e\n",9*sin($ph),9*cos($ph),-9*sin($ph),9*cos($ph);
printf "#cm 1 m 2\nline %e %e %e %e\n",9*sin($ph),-9*cos($ph),-9*sin($ph),-9*cos($ph);
printf "#cm 1 m 1\nstickfig %e %e %e %e\n",-9*sin($ph),9*cos($ph),-9.8*sin($ph),9.8*cos($ph);
printf "#cm 0 m 1\nstickfig %e %e %e %e\n",-9*sin($sy),9*cos($sy),-10.8*sin($sy),10.8*cos($sy);
printf "#cm 0 m 1\nline -9 0 9 0\n";
printf "#cm 2 m 2\nline 0 9 0 -9\n";

printf "#cm 2 m 2\nline %e %e %e %e\n",-9*sin($th),9*cos($th),9*sin($th),-9*cos($th);

print <<END;
#cm 0 m 1 cs 0.8
-1.4 9.4 "North Pole"
-1.4 -9.4 "South Pole"
-1.6 8 "Arctic Circle"
-2 -8 "Antarctic Circle"
-0.9 0.4 "Equator"
-1.9 3 "Tropic of Cancer"
-2 -3 "Tropic of Capricorn"
END
