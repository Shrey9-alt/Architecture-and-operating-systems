#!/bin/csh
echo "Written by Shreyansh Patel"

# Check if the correct number of arguments is provided
if ($#argv != 2) then
    echo "Usage: findtext.s <string> <filename>"
    exit 1
endif

set keyword = $argv[1]
set filename = $argv[2]

# Check if the file exists
if (! -e $filename) then
    echo "File not found: $filename"
    exit 1
endif

# Print the filename
echo $filename

# Use grep with -F to treat the keyword as a fixed string
grep -nF "$keyword" $filename
