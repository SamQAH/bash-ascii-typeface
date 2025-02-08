#!/bin/bash
if ! [ -x say ]; then
echo Access denied /say >&2
exit 1
fi
if ! [ -x display.sh ]; then
echo Access denied /display.sh >&2
exit 1
fi
TEMPFILE=$(mktemp)
./say $@ > $TEMPFILE
lines=$(wc -l < $TEMPFILE | tr -d ' ')
for curline in $(seq 1 $lines); do
./display.sh $(sed "$curline!d" $TEMPFILE | tr -d "\n")
done
rm $TEMPFILE