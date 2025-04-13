#!/bin/csh

echo "Written by Shreyansh Patel"

# Check if any arguments are provided
if ($#argv == 0) then
    echo "Usage: mu.s -f <string> <filename> | -r <side1> <side2> <side3> | -c <filename(s)>"
    exit 1
endif

# Start processing arguments
set i = 1
while ($i <= $#argv)
    set flag = "$argv[$i]"

    switch ($flag)

        # -f flag for findtext.s
        case "-f":
            if ($i + 2 <= $#argv) then
                @ i++
                set searchString = "$argv[$i]"
                @ i++
                set fileName = "$argv[$i]"
                echo "Running findtext.s with '$searchString' in '$fileName'"
                if (-e "$fileName") then
                    ./findtext.s "$searchString" "$fileName"
                else
                    echo "Error: File '$fileName' not found"
                endif
            else
                echo "Error: Invalid parameters for -f. Provide a string and a filename."
            endif
            @ i++
            echo "---"
            breaksw

        # -r flag for right.s   
        case "-r":
            if ($i + 3 <= $#argv) then
                @ i++
                set side1 = "$argv[$i]"
                @ i++
                set side2 = "$argv[$i]"   
                @ i++
                set side3 = "$argv[$i]" 
                echo "Running right.s with sides $side1 $side2 $side3"
                ./right.s "$side1" "$side2" "$side3"
            else
                echo "Error: Invalid parameters for -r. Provide three numbers."
            endif
            @ i++
            echo "---"
            breaksw

        # -c flag for count.s
        case "-c":
            @ i++
            while ($i <= $#argv)
                set fileName = "$argv[$i]"
                echo "Running count.s on '$fileName'"
                if (-e "$fileName") then
                    ./count.s "$fileName"
                else
                    echo "Error: File '$fileName' not found"
                endif
                @ i++
                echo "---"
                if ($i <= $#argv && "$argv[$i]" =~ -*) then
                    break
                endif
            end  
            breaksw

        # Handle invalid flags
        default:
            echo "Error: Invalid argument - '$flag'"
            @ i++
            if ($i <= $#argv) then
                echo "Error: Invalid parameter - '$argv[$i]'"
                @ i++
            endif
            if ($i <= $#argv) then
                echo "Error: Invalid parameter - '$argv[$i]'"
                @ i++
            endif
            echo "---"
    endsw
end
