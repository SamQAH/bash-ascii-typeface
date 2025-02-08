#!/bin/bash
if [ -e words_data.txt ]; then
rm words_data.txt
fi
for line in {1..27}; do
echo $(($(sed "$(($line*4))!d" words.txt | wc -c | tr -d ' ')-1)) >> words_data.txt
done