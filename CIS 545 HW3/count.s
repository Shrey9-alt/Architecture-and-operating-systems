#!/bin/csh
echo "Written by Shreyansh Patel"
if ($#argv < 1) then
    echo "Usage: count.s <filename(s)>"
    exit 1
endif
foreach file ($argv)
    if (! -e $file) then
        echo "$file not found"
    else
        echo $file
        set output = (`wc $file`)
        echo "$output[3] characters"
        echo "$output[2] words"
        echo "$output[1] lines"
    endif
end

