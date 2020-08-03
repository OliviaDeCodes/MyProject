#!/bin/bash
temp=$1
time=`date -u +"%Y-%m-%d__%H:%M:%S"`
size=( $(free -m | head -n 2 | tail -n 1 | awk '{print $2" "$3" "$2-$3}') )
employ=`echo "scale=1;${size[1]}*100/${size[0]}" | bc`
average=`echo "scale=1;0.3*${temp}+0.7*${employ}" | bc`
echo "$time ${size[0]}M ${size[2]}M ${employ}% ${average}%"


