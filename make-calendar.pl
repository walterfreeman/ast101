open Sched,"schedule5.csv";

<Sched>;

$line=0;
$day=1;
while (<Sched>)
{
  chomp;
  @w=split /,/;
  $date[$line]=$w[0];
  $topic[$line]=$w[1];
  
  unless ($topic[$line] =~ /EXAM/)
  {
    $topic[$line]="<a href=\"slides/lecture$day.pdf\">$topic[$line]</a>";
    $day++;
  }
  $sec6[$line]=$w[2];
  $pages6[$line]=$w[3];
  $sec7[$line]=$w[4];
  $pages7[$line]=$w[5];
  $sec8[$line]=$w[6];
  $pages8[$line]=$w[7];
  $tutorials[$line]=$w[8];
  print STDERR "Read a line: topic $topic[$line], 6th ed $sec6[$line] $pages6[$line], 7th ed $sec7[$line] $pages7[$line], 8th ed $sec8[$line] $pages8[$line]\n";
  $line++;
}

# calendar for 8th edition books

print <<END;
---
layout: page
title: Calendar
permalink: calendar.html
category: top 
use_math: true
---

    
This calendar is tentative and might change based on your input. Exam dates will not change, but topics might be adjusted if the calendar changes.
  
You should read the pages listed in the textbook **before** class. The pages in the tutorial will be covered in that day's class.


END


print "<br><br>\n### Eighth edition page numbers:\n\n";

print "| Class Date    | Topics                                                  | Textbook sections              | Textbook pages          | Tutorials    |\n";
print "|:-------------:|:-------------------------------------------------------:|:------------------------------:|:-----------------------:|:------------:|\n";

for ($line=0; $line<@date; $line++)
{
  if ($topic[$line] =~ /FINAL/)
  {
    print "|===============+=========================================================+================================+=========================+==============+\n";
  }
  print "| $date[$line] | $topic[$line] | $sec8[$line] | $pages8[$line] | $tutorials[$line] |\n";
}
print "|---------------+---------------------------------------------------------+--------------------------------+-------------------------+--------------+\n\n\n\n";


# calendar for 7th edition books

print "<br><br>\n### Seventh edition page numbers:\n\n";

print "| Class Date    | Topics                                                  | Textbook sections              | Textbook pages          | Tutorials    |\n";
print "|:-------------:|:-------------------------------------------------------:|:------------------------------:|:-----------------------:|:------------:|\n";

for ($line=0; $line<@date; $line++)
{
  if ($topic[$line] =~ /FINAL/)
  {
    print "|===============+=========================================================+================================+=========================+==============+\n";
  }
  print "| $date[$line] | $topic[$line] | $sec7[$line] | $pages7[$line] | $tutorials[$line] |\n";
}
print "|---------------+---------------------------------------------------------+--------------------------------+-------------------------+--------------+\n\n\n\n";


# calendar for 6th edition books
print "\n\n\n\n<br><br>\n### Sixth edition page numbers:\n\n";

print "| Class Date    | Topics                                                  | Textbook sections              | Textbook pages          | Tutorials    |\n";
print "|:-------------:|:-------------------------------------------------------:|:------------------------------:|:-----------------------:|:------------:|\n";

for ($line=0; $line<@date; $line++)
{
  if ($topic[$line] =~ /FINAL/)
  {
    print "|===============+=========================================================+================================+=========================+==============+\n";
  }
  print "| $date[$line] | $topic[$line] | $sec6[$line] | $pages6[$line] | $tutorials[$line] |\n";
}
print "|---------------+---------------------------------------------------------+--------------------------------+-------------------------+--------------+\n";


