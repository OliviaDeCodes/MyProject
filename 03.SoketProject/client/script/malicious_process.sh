#!/bin/bash
nowtime=`date +"%Y-%m-%d__%H:%M:%S"`
PID=(`ps -aux | awk '{if($3>50||$4>50)print $2}'`)
if [[ $PID ]];then
	sleep 5
ps -aux | awk -v time=$nowtime '{if($3>50||$4>50) printf "%s %s %d %s %.2f%% %.2f%%\n", time,$11,$2,$1,$3,$4}'
fi

