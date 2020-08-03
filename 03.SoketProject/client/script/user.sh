#!/bin/bash
time=`date +"%T-%m-%d__%H:%M:%S"`
root=`cat /etc/group | grep 'sudo' | cut -d ':' -f 4`
active=`last | head -n -2 | sort | cut -d ' ' -f 1 | uniq -c | sort -k 1 -n -r | head -n 3 | awk '{printf("%s,", $2)}' | sed 's/.$//'`
users_number=`cat /etc/passwd | grep /home/ | wc -l`
now_users=`w -h | awk '{printf("%s_%s_%s,", $1, $3, $2)}' | sed 's/.$//'`

echo "$time [$users_number] [$active] [$root] [$now_users]"

