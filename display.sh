#!/bin/bash
if ! [ -e words.txt ]; then
 echo Can not find ./words >&2
 exit 1
fi
if [ $# -eq 0 ]; then
 exit 0
fi

for i in 0 1 2 3; do
    for line in $@; do
        curline=$(($line+$i))
        sed "$curline!d" words.txt | tr -d "\n"
    done
    echo 
done
