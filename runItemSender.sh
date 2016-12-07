#!/bin/sh
#params<agent ip to get item> <agent port> <agent host name> <server ip to send> <server port> <time interval to send(ms)> <item keys config file>
pkill htrdItemSender
#rm -f *.log

nohup ./htrdItemSender 192.168.103.51 10050 Linux_redhat5.8_51 192.168.103.112 10051 500 ./item_sender_conf_linux > /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.11 10050 Linux_redhat5.8_11 192.168.103.112 10051 500 ./item_sender_conf_linux > /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.56 10050 Linux_redhat5.8_56 192.168.103.112 10051 500 ./item_sender_conf_linux > /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.91 10050 Linux_redhat5.8_91 192.168.103.112 10051 500 ./item_sender_conf_linux > /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.92 10050 Linux_redhat5.8_92 192.168.103.112 10051 500 ./item_sender_conf_linux > /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.93 10050 Linux_redhat5.8_93 192.168.103.112 10051 500 ./item_sender_conf_linux > /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.22 10050 Windows_hp-59a5ba74e891 192.168.103.112 10051 500 ./item_sender_conf_windows > /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.95 10050 Windows_baopandalian 192.168.103.112 10051 500 ./item_sender_conf_windows > /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.94 10050 Windows_ctp-czj 192.168.103.112 10051 500 ./item_sender_conf_windows > /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.109 10050 Windows_hp-6083705d9827 192.168.103.112 10051 500 ./item_sender_conf_windows > /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.57 10050 Windows_hp-c49257ecfee7 192.168.103.112 10051 500 ./item_sender_conf_windows > /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.52 10050 Windows_hp-d299df272a36 192.168.103.112 10051 500 ./item_sender_conf_windows > /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.3 10050 Windows_win_config 192.168.103.112 10051 500 ./item_sender_conf_windows > /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.12 10050 Windows_yhqh-1 192.168.103.112 10051 500 ./item_sender_conf_windows > /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.54 10050 Windows_yhqh-9e75dad78e 192.168.103.112 10051 500 ./item_sender_conf_windows > /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.53 10050 Windows_yhqh-9e75dad78e 192.168.103.53 10051 500 ./item_sender_conf_windows > /dev/null 2>log &
