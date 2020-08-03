#!/bin/bash
pre_pid=`cat /home/wpz/master/master_wpz.pid 2> /dev/null`

if [[ "${pre_pid}x" != "x" ]]; then
    ps -ef | grep -w ${pre_pid} | grep master > /dev/null
    if [[ $? == 0 ]];then
        echo "Pihealthd has already started."
        exit 0
    else
        echo "Piheadlthd is starting."
        /home/wpz/master/master
        echo "Pihealthd starting."
    fi
else
    echo "Pihealthd is starting."
    /home/wpz/master/master
    echo "Piheadlthd started."
fi
