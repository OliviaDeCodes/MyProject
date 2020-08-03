#!/bin/bash

time=`date +"%Y-%m-%d__%H:%M:%S"`
disk=(`df -m | grep "^/dev/" | awk '{print 1" "$6" "$2" "$4" "$5} {total+=$2;used+=$3;free+=$4} {printf "%d ",total;printf "%d ",free;printf "%d\n",used*100/total}' | tr ' ' ';' | tr '\n' ' '`)
echo "$time 0 disk ${disk[3]}%" | tr ';' ' ' 
echo $time ${disk[0]} | tr ';' ' '
echo $time ${disk[2]} | tr ';' ' '
