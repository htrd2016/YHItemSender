#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "utils.h"

int get_items_data(const char *agent_ip, int agent_port, char(*search_keys)[512], int count, char(*datas_out)[64])
{
  char *end = NULL;
  int index = 0;
  char geter_cmd[1024];
  char geter_ret[64]  = {0};
  for(index=0; index<count; index++)
  {
    sprintf(geter_cmd, "zabbix_get -s %s -p %d  -k \"%s\"", agent_ip, agent_port, search_keys[index]); 
    run_cmd(geter_cmd, geter_ret, sizeof(geter_ret));

    if (strchr(geter_ret, ':') != NULL)
    {
       return -1;
    }

    printf("%s\n", geter_cmd);
    memset(datas_out[index], 0, 64);
    if(NULL != (end=strchr(geter_ret, '\n')))
    {
      strncpy(datas_out[index], geter_ret, end-geter_ret);
    }
    else
    {
      strcpy(datas_out[index], geter_ret);
    }
  }
  return 0;
}

int main(int argc, char **argv)
{
  char agent_ip[30] = {0};
  int agent_port = -1;
  char agent_host_name[512] = {0};
  char server_ip[30] = {0};
  int server_port = -1;
  int time_interval = 1000;
  char items_file[512] = {0};

  char search_keys[100][512];
  char item_keys[100][512];
  char item_datas[100][64];
  int item_count = 0;
  if(argc<8)
  {
     printf("params<agent ip to get item> <agent port> <agent host name> <server ip to send> <server port> <send data time interval(ms)> <item key config file>\n");
     return -1;
  }

  strcpy(agent_ip, argv[1]);
  agent_port = atoi(argv[2]);
  strcpy(agent_host_name, argv[3]);
  strcpy(server_ip, argv[4]);
  server_port = atoi(argv[5]);
  time_interval = atoi(argv[6]);
  strcpy(items_file, argv[7]);

  printf("agent ip:%s,agent port:%d,agent host name:%s,server ip:%s,server port:%d, time interval:%d,item key config file:%s\n",
         agent_ip,agent_port, agent_host_name,server_ip,server_port, time_interval, items_file);

  if(0>=parse_oids_items_to_array(items_file, search_keys, item_keys, &item_count))
  {
    printf("parse %s failed\n", items_file);
    return -1;
  }

  while(1)
  {
    
    if(-1==get_items_data(agent_ip, agent_port, search_keys, item_count, item_datas))
    {
      printf("error!!\n");
      sleep(30);
      continue;
    }
    
   /*if(-1 == write_to_send_file(temp_file_name, agent_host_name, item_keys, item_datas, item_count))
   {
     perror("write file error!!!\n");
     sleep(30);
     continue;
   }
   send_file(server_ip, server_port, temp_file_name);*/

    send_data(server_ip, server_port, agent_host_name, item_keys, item_datas, item_count);


/*
    gettimeofday (&tvpre , &tz);
    run_cmd(geter_cmd, sizeof(geter_cmd), geter_ret, sizeof(geter_ret));
    gettimeofday (&tvafter , &tz);
    printf("\n%s get data cost time:%lds %ldus\n", geter_ret, tvafter.tv_sec-tvpre.tv_sec, tvafter.tv_usec-tvpre.tv_usec);

    if (strchr(geter_ret, ':') != NULL)
    {
      printf("error");
      sleep(10);
      continue;
    }
    sprintf(sender_cmd, "zabbix_sender -z %s -p %d -s \"%s\" -k \"%s\" -o %s\n", server_ip, server_port, agent_host_name, key_to_send, geter_ret);
    printf("%s", sender_cmd);
    
    gettimeofday (&tvpre , &tz);
    system(sender_cmd);
    gettimeofday (&tvafter , &tz);
    printf("send data cost time:%lds %ldus\n", tvafter.tv_sec-tvpre.tv_sec, tvafter.tv_usec-tvpre.tv_usec);
*/
    usleep(time_interval*1000);
  }
   
  return 0;
}
