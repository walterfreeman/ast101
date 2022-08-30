open Sched,"schedule2022.tsv";

<Sched>;

$line=0;
$day=1;
while (<Sched>)
{
  s/\r//g;
  chomp;
  @w=split /\t/;
  $date[$line]=$w[0];
  $topic[$line]=$w[1];
  $hw[$line]=$w[2];
  $tut[$line]=$w[3];
  $read[$line]=$w[4];
  $labtopic[$line]=$w[5];
  $quiz[$line]=$w[6];
  $tutname[$line]=$w[7];

  unless ($topic[$line] =~ /EXAM/)
  {
      if (-e "slides/lecture$day/lecture$day-2022.pdf")
      {
	  print STDERR "FOUND SLIDES $day\n";
      	  $topic[$line]="<a href=\"slides/lecture$day/lecture$day.pdf\">$topic[$line]</a>";
      }
      if (-e "tutorials/$tutname[$line]/$tutname[$line].pdf")
      {
	  $tut[$line]="<a href=\"tutorials/$tutname[$line]/$tutname[$line].pdf\">$tut[$line]</a>";
      }
      
    $day++;
  }
  print STDERR "Read a line: date $date[$line], topiclink $topic[$line], hw $hw[$line], tutorial $tut[$line], reading $read[$line]\n";
  $line++;
}


print <<END;
---
layout: page
title: Calendar
permalink: calendar.html
category: top 
use_math: true
---

    
This calendar is tentative and might change based on your input. 

Exam dates may change during the first week of class, but will not change after that. Topics might be adjusted if the calendar changes.

You should read the pages listed in the textbook **before** class. The pages in the tutorial will be covered in that day's class.


END


print "| Date          | Topics                                                  | Assignments | Tutorials             |  Readings     |\n";
print "|:-------------:|:-------------------------------------------------------:|:-----------:|:---------------------:|-:------------:|\n";

for ($line=0; $line<@date; $line++)
{
  if ($topic[$line] =~ /FINAL/)
  {
print "|===============+=========================================================+=============+=======================+=======================================+\n";
  }
  print "| $date[$line] | $topic[$line] | $hw[$line] | $tut[$line] | $read[$line] |\n";
}
print "|---------------+---------------------------------------------------------+-------------+-----------------------+---------------------------------------+\n\n\n\n";

