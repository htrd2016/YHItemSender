#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

char* run_cmd(const char *cmd, int cmd_length, char** out_str, int out_str_size)
{
    FILE *fp = 0;
    int index = 0;
    char *out = (char*)(*out_str);
    
    memset(out, 0, out_str_size);
    
    if ((fp = popen(cmd, "r")) == NULL) 
    {
        strcpy(out, "error:popen failed");
        perror("popen failed");
        return out;
    }
    
    while (fgets(out+index, out_str_size-index-1, fp) != NULL) 
    {
        index = strlen(out);
    }
    
    if (pclose(fp) == -1) 
    {
        strcpy(out, "error:pclose failed");
        perror("pclose failed");
        return out;
    }
    return out;
}

int main(int argc, char **argv)
{
  char agent_ip[30] = {0};
  int agent_port = -1;
  char key_to_get[512] = {0};
  char agent_host_name[512] = {0};
  char server_ip[30] = {0};
  int server_port = -1;
  char key_to_send[512] = {0};
  int time_interval = 1000;

  char geter_ret[1024] = {0};
  char geter_cmd[1024] = {0};
  char sender_cmd[1024] = {0};
  char *geter_ret_point = geter_ret;

  //test time
  struct timeval tvafter,tvpre;
  struct timezone tz;
   
  if(argc<9)
  {
     printf("params<agent ip to get item> <agent port> <item key to get> <agent host name> <server ip to send> <server port> <item key configed in server><send data time interval(ms)>");
     return -1;
  }

  strcpy(agent_ip, argv[1]);
  agent_port = atoi(argv[2]);
  strcpy(key_to_get, argv[3]);
  strcpy(agent_host_name, argv[4]);
  strcpy(server_ip, argv[5]);
  server_port = atoi(argv[6]);
  strcpy(key_to_send, argv[7]); 
  time_interval = atoi(argv[8]);

  printf("agent ip:%s,agent port:%d,key to get:%s,agent host name:%s,server ip:%s,server port:%d,key to send:%s, time interval:%d\n",
         agent_ip,agent_port,key_to_get,agent_host_name,server_ip,server_port,key_to_send, time_interval);

  sprintf(geter_cmd, "zabbix_get -s %s -p %d  -k \"%s\"", agent_ip, agent_port, key_to_get);
  printf(geter_cmd);
  while(1)
  {
    gettimeofday (&tvpre , &tz);
    run_cmd(geter_cmd, sizeof(geter_cmd), (char**)(&geter_ret_point), sizeof(geter_ret));
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

    usleep(time_interval*1000);
  }
   
  return 0;
}
