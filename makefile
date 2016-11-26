CC=gcc
CFLAGS=-g -Wall -O2
LDFLAGS=-L/usr/lib/
#LIBS=-L/usr/lib/ -lmysqlclient #-lpthread
#INCLUDES= -I./mysql-connector-c-6.0.2-linux-rhel5
TARGET_ITEM_SENDER = htrdItemSender
TARGET_SNMP_SENDER = htrdSNMPSender
all:$(TARGET_ITEM_SENDER) $(TARGET_SNMP_SENDER)

utils.o: utils.c
	$(CC) $(CFLAGS) $(INCLUDES) -c utils.c

$(TARGET_ITEM_SENDER): utils.o
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) utils.o htrd_item_main.c $(LIBS)

$(TARGET_SNMP_SENDER): utils.o
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) utils.o htrd_snmp_main.c $(LIBS)

clean:
	rm  -f *.o $(TARGET_ITEM_SENDER) $(TARGET_SNMP_SENDER)
