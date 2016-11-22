#!/bin/bash
# make a call to port 9001 on the target IP address
MYIP=$(/sbin/ifconfig | sed -En 's/127.0.0.1//;s/.*inet (addr:)?(([0-9]*\.){3}[0-9]*).*/\2/p')
echo $MYIP | socat TCP:$1:9001 -
RESP=$(socat -u TCP-LISTEN:9001 -)
