#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "utils.h"

char *snmp_get(const char *key, const char *ip, const char* oid, char out[], int out_size)
{
  char cmd[1024] = {0};
  sprintf(cmd, "snmpget -v 2c -c %s %s %s", key, ip, oid);
  printf("%s\n", cmd);
  run_cmd(cmd, out, out_size);
  return out;
}

int get_data_from_cisco(const char *key, const char *ip, const char* oid, char out_data[], int out_size)
{
  char out[1024] = {0};
  char *data_start = 0;
  char *data_end = 0;

  memset(out, 0, out_size);
  snmp_get(key, ip, oid, out, sizeof(out));
  //printf("%s\n", out);
  if(0==(data_start = strchr(out, '(')))
  {
    return -1;
  }

  if(0==(data_end = strchr(out, ')')))
  {
    return -1;
  }

  strncpy(out_data, data_start+1, data_end-data_start-1);
  printf("out data:%s\n", out_data);

  return 0;
}

/*void send_data(const char *server_ip, int server_port, const char *agent_host_name, const char *key_to_send, const char *data)
{
  char sender_cmd[1024] = {0};
  char ret[1024] = {0};
  sprintf(sender_cmd, "zabbix_sender -z %s -p %d -s \"%s\" -k \"%s\" -o %s\n", server_ip, server_port, agent_host_name, key_to_send, data);
  printf("%s", sender_cmd);
  run_cmd(sender_cmd, ret, sizeof(ret));
  //printf("send ret:%s\n", ret);
  if (strstr(ret, "failed: 1") != NULL)
  {
    perror(ret);
    printf("error\n");
    sleep(10);
  }
}*/

int get_datas_from_cisco(const char *snmp_key, const char *snmp_ip, char (*snmp_oids)[512], int item_count, char (*snmp_datas)[64])
{
  int index = 0;
  for(index=0;index<item_count;index++)
  {
    memset(snmp_datas[index], 0, 64);
    if (-1 == get_data_from_cisco(snmp_key, snmp_ip, snmp_oids[index], snmp_datas[index], 64))
    {
      perror("get data from cisco error!!!\n");
      return -1;
    }
  }
  return 0;
}

int main(int argc, char **argv)
{
  char snmp_key[512] = {0};
  char snmp_ip[32] = {0};
  char htrd_server_ip[32] = {0};
  int htrd_server_port=-1;
  char agent_host_name[512] = {0};
  char config_path[1024] = {0};
  int send_interal = 1000;

  char snmp_oid[100][512];
  char item_key[100][512];
  char item_data[100][64];
  int item_count = 0;

  if (argc<8)
  {
    printf("useage<path><snmp key><snmp ip><htrd server ip><htrd server port><agent host name in config><oid and item config file><send data time interval(ms)>\n");
    return -1;
  }

  strcpy(snmp_key, argv[1]);
  strcpy(snmp_ip, argv[2]);
  strcpy(htrd_server_ip, argv[3]);
  htrd_server_port = atoi(argv[4]);
  strcpy(agent_host_name, argv[5]);
  strcpy(config_path, argv[6]);
  send_interal = atoi(argv[7]);

  printf("snmp key:%s,snmp ip:%s,htrd server ip:%s,htrd server port:%d,agent host name:%s,agent host name:%s,time interval:%d\n", 
        snmp_key, snmp_ip, htrd_server_ip, htrd_server_port, agent_host_name, agent_host_name, send_interal);

  if(0>=parse_oids_items_to_array(config_path, snmp_oid, item_key, &item_count))
  {
    printf("parse %s failed\n", config_path);
    return -1;
  }

  while(1)
  {
    if (-1 == get_datas_from_cisco(snmp_key, snmp_ip, snmp_oid, item_count, item_data))
    {
      perror("get data from cisco error!!!\n");
      sleep(30);
      continue;
    }
   send_data(htrd_server_ip, htrd_server_port, agent_host_name, item_key, item_data, item_count);

/*    if(-1 == write_to_send_file(temp_file_name, agent_host_name, item_key, item_data, item_count))
    {
      perror("write file error!!!\n");
      sleep(30);
      continue;
    }
    send_file(htrd_server_ip, htrd_server_port, temp_file_name);  */
    usleep(send_interal*1000);
  }
  
  return 0;
  
  //gettimeofday (&tvpre , &tz);
  //run_cmd(geter_cmd, sizeof(geter_cmd), geter_ret, sizeof(geter_ret));
  //gettimeofday (&tvafter , &tz);
  //printf("\n%s get data cost time:%lds %ldus\n", geter_ret, tvafter.tv_sec-tvpre.tv_sec, tvafter.tv_usec-tvpre.tv_usec);

  return 0;
}
