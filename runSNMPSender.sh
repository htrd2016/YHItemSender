pkill htrdSNMPSender
nohup ./htrdSNMPSender yhqh 101.195.96.254 192.18.103.112 10051 "cisco router" ./router_oid_item_config.ini 500 ./router_temp > /dev/null 2>log &
nohup ./htrdSNMPSender yhqh 192.18.103.230 192.18.103.112 10051 "cisco switch WS-C3750X-48" switch_oid_item_config.ini 500 ./switch_temp> /dev/null 2>log &
