nohup ./htrdItemSender 192.168.103.51 10050 Linux_redhat5.8_51 192.168.103.112 10051 500 ./item_sender_conf_51 ./temp_item_51> /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.51 10050 system.cpu.load[percpu,avg1] Linux_redhat5.8_51 192.168.103.112 10051 sender.system.cpu.load.percpu.avg1 500 > /dev/null 2>log &

nohup ./htrdItemSender 192.168.103.22 10050 vm.memory.size[available] Windows_hp-59a5ba74e891 192.168.103.112 10051 sender.vm.memory.size.available 500 > /dev/null 2>log &
nohup ./htrdItemSender 192.168.103.22 10050 system.cpu.load[percpu,avg1] Windows_hp-59a5ba74e891 192.168.103.112 10051 sender.system.cpu.load.percpu.avg1 500 > /dev/null 2>log &

