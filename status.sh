#!/bin/sh
# Status bar script.
# You can put this in your .xinitrc or whatever
# Example of how it might look:
# sound 100%    mem 500M    time 13:08:24    date sat 21 may    user jeremy
while xsetroot -name " sound `pamixer --get-volume`%    mem `free -h | sed '1d;3d;s/Ki/K/g;s/Mi/M/g;s/Gi/G/g' | awk '{print $3}'`    time `date +%H:%M:%S`    date `date '+%a %d %b' | tr '[:upper:]' '[:lower:]'`    user $USER   "
do
    sleep 0.5
done &
