#!/bin/bash
time=`date +"%Y-%m-%d__%H:%M:%S"`
OS=`cat /etc/issue | awk '{printf("%s_%s_%s", $1, $2, $3)}'`
Kernel_version=`cat /proc/version | cut -d ' ' -f 3`
operation_hours=`uptime -p | tr ' ' '_'`
Average_load=`uptime | tr ' ' '\n' | tail -n 3 | xargs | tr -d ','`
#磁盘大小 已用%
disk=(`df -m | tail -n +2 | grep -v tmp |awk '{total+=$2;used+=$3} END{printf "%d ",total;printf "%d",used*100/total}'`)
#内存大小 已用%
mem_size=(`free -m |head -n 2 | tail -n 1 | awk '{print $2" "$3}'`)
mem_per=$[${mem_size[1]}*100/${mem_size[0]}]
#cpu温度
message=$[ `cat /sys/class/thermal/thermal_zone0/temp` ]
cpu=`echo "scale=2;${message}/1000" | bc`
temp1=''
if  [[ ${disk[1]} < 70 ]]; then
	temp1="normal"
elif [[ ${disk[1]} > 70 && ${disk[1]} < 80 ]]; then
	temp1="note"
elif [[ ${disk[1]} > 80 && ${disk[1]} < 100 ]]; then
	temp1="warning"
fi

temp2=`echo $cpu |awk '{if($1 <= 50){print "normal"}else if($1<=70){print "note"}else{print "warning"}}'`
temp3=`echo $mem_per |awk '{if($1<=70){print "normal"}else if($1<=80){print "note"}else{print "warning"}}'`

echo "$time $HOSTNAME $OS $Kernel_version $operation_hours $Average_load ${disk[0]} ${disk[1]}% ${mem_size[0]} ${mem_per}% $cpu $temp1 $temp2 $temp3"


