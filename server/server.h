#ifndef __SERVER__H_20140505_
#define __SERVER__H_20140505_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>//close()
#include<netinet/in.h>//struct sockaddr_in
#include<arpa/inet.h>//inet_ntoa
#include<iostream>
#include<fstream>

#define  QUEUE_LINE  12
#define  MAXCLENT 5 
#define  BUF_LEN 1024 
#define  SOURCE_PORT 61111
#define  SOURCE_IP_ADDRESS "192.168.4.124"

using namespace std;
class ServerApp
{
	public:
		ServerApp();
		virtual ~ServerApp();
	public:
		void process_info(int iConnFd);
	private:
	  int  iConnFd;	  
    ofstream ofile_log;
};
#endif // __SERVER__H_20140505_
