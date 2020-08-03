#!/bin/bash
TIME_NOW=`date +"%Y-%m-%d__%H:%M:%S"` #时间

#AVG_LOAD=`uptime | tr ' ,:' '\n' | grep -v '^$' | tail -n -3 | xargs` #CPU平均负载

#IDLE1=`cat /proc/stat | head -n 1 | awk '{print $5}'` #获取CPU第一次的其他时间
#TOTAL1=$[ 0 `cat /proc/stat | head -n 1 | tr -s -c "0-9\n" "+"`  ] #获取第一次CPU的CPU的总时间

#sleep 0.5 #相隔0.5 

#IDLE2=`cat /proc/stat | head -n 1 | awk '{print $5}'` #获取CPU第二次的其他时间
#TOTAL2=$[ 0 `cat /proc/stat | head -n 1 | tr -s -c "0-9\n" "+"`  ] #获取CPU第二次的CPU总时间

#CPU_USAGE=`echo "scale=2; ($IDLE2 - $IDLE1) * 100 / ($TOTAL2 - $TOTAL1)" | bc` #通过前四个变量获得CPU的占有率

#CPU_INFO=`cat /sys/class/thermal/thermal_zone0/temp` #CPU温度的1000倍

#CPU_TEMPERATURE=`echo "scale=2;$CPU_INFO/1000" | bc` #CPU温度

#ALARM_LEVEL_CPU=`test $CPU_INFO -ge 0 && test $CPU_INFO -le 50000 && echo normal || (test $CPU_INFO -le 70000 && echo note || echo warning)` #CPU报警级别

#echo "$TIME_NOW $AVG_LOAD $CPU_USAGE "$CPU_TEMPERATURE"°C $ALARM_LEVEL_CPU"


#time=`date +"%T_%m_%d__%H:%M:%S"`
#cpu平均负载
IDLE1=`cat /proc/stat | head -n 1 | awk '{print $5}'` 
TOTAL1=$[ 0 `cat /proc/stat | head -n 1 | tr -s -c "0-9\n" "+"`  ]
sleep 0.5
IDLE1=`cat /proc/stat | head -n 1 | awk '{print $5}'`
TOTAL1=$[ 0 `cat /proc/stat | head -n 1 | tr -s -c "0-9\n" "+"`  ]
CPU_USAGE=`echo "scale=2; ($IDLE2 - $IDLE1) * 100 / ($TOTAL2 - $TOTAL1)" | bc`
#cpu温度
message=$[ `cat /sys/class/thermal/thermal_zone0/temp`  ]
cpu_temperature=`echo "scale=2;${message}/1000" | bc`
temp=`echo $cpu_temperature | awk '{if($1<=50){print "normal"}else if($1<=70){print "note"}else{print"warning"}}'`
echo "$TIME_NOW $average ${cpu_temperature}°C  $temp"

