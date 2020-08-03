#!/bin/bash

pre_pid=`cat ./master_wpz.pid`
if test -n $pre_pid ;then
    ps -ef | grep -w ${pre_pid} | grep ./master > /dev/null 
    if [[ $? == 0 ]]; then
        echo "Pihealthd is stoping."
        kill -9 ${pre_pid}
        echo "Pihealthd stoped."
    else
        echo "Pihealthd has alreadly stoped."
    fi
fi
