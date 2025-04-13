#!/bin/csh
echo "Written by Shreyansh Patel"

if ($#argv != 3) then
    echo "Usage: right.s <side1> <side2> <side3>"
    exit 1
endif
@ a = $argv[1]
@ b = $argv[2]
@ c = $argv[3]
@ a2 = $a * $a
@ b2 = $b * $b
@ c2 = $c * $c
if (($a2 + $b2 == $c2) || ($a2 + $c2 == $b2) || ($b2 + $c2 == $a2)) then
    echo "$a $b $c is a right triangle"
else
    echo "$a $b $c is not a right triangle"
endif

#STAND_ALONE
