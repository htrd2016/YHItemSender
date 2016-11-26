#!/bin/sh
#params<agent ip to get item> <agent port> <agent host name> <server ip to send> <server port> <time interval to send(ms)> <keys file name> <temp file name to sender>
pkill htrdItemSender
#rm -f *.log

nohup ./htrdItemSender 192.18.103.51 10050 Linux_redhat5.8_51 192.18.103.112 1005 500 ./item_sender_conf_51 ./temp_item_51 > /dev/null 2>log &
nohup ./htrdItemSender 192.18.103.22 10050 Windows_hp-59a5ba74e891 192.18.103.112 1005 500 ./item_sender_conf_22 ./temp_item_22> /dev/null 2>log &

