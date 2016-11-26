#!/bin/sh
#params<agent ip to get item> <agent port> <item key to get> <agent host name> <server ip to send> <server port> <item key configed in server>
pkill htrdItemSender
#rm -f *.log

nohup ./htrdItemSender 192.168.103.51 10050 vm.memory.size[available] Linux_redhat5.8_51 192.168.103.112 10051 sender.vm.memory.size.available 500 > /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.51 10050 system.cpu.load[percpu,avg1] Linux_redhat5.8_51 192.168.103.112 10051 sender.system.cpu.load.percpu.avg1 500 > /dev/null 2>log &

nohup ./htrdItemSender 192.168.103.22 10050 vm.memory.size[available] Windows_hp-59a5ba74e891 192.168.103.112 10051 sender.vm.memory.size.available 500 > /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.22 10050 system.cpu.load[percpu,avg1] Windows_hp-59a5ba74e891 192.168.103.112 10051 sender.system.cpu.load.percpu.avg1 500 > /dev/null 2>log &
