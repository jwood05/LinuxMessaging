#!/bin/bash
# listen on port 9001 (OVER NINE THOUSAND!!!!)
NEWIP=$(socat -u TCP-LISTEN:9001 -)
echo "pong" | socat TCP:$NEWIP:9001 -
