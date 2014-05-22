#include <iostream>
#include "server.h"


ServerApp::ServerApp()
	{
		
	}
ServerApp::~ServerApp()
	{
		
	}
void ServerApp::process_info(int iConnFd)
{
	      int i(1);
        int recv_num, send_num;
        char recv_buf[BUF_LEN];
        char send_buf[BUF_LEN];
        ofile_log.open("log.txt");
        while(1)
        {
             cout << "begin recv: " << endl;
             recv_num = recv(iConnFd,recv_buf,sizeof(recv_buf),0);
             if(recv_num <0)
             {
                 perror("recv");
                 exit(1);
             } 
             else 
             {
                 recv_buf[recv_num] = '\0';
                 cout << "recv sucessful: "<< recv_buf<< endl;
                 ofile_log << i << "\t" << recv_buf << endl;
                 i++;
             }
             sprintf(send_buf,"recv %d numbers bytes\n",recv_num);
             cout << "begin send"<<endl;
             send_num = send(iConnFd,send_buf,sizeof(send_buf),0);
             if (send_num < 0)
             {
                 perror("sned");
                 exit(1);
             } 
             else 
             {
                 cout << "send sucess"<<endl;
             }
             
             cout << "begin recv command result:"<<endl;
             recv_num = recv(iConnFd,recv_buf,sizeof(recv_buf),0);
             if(recv_num <0)
             {
                 perror("recv");
                 exit(1);
             } 
             else 
             {
                 recv_buf[recv_num] = '\0';
                 cout << "recv sucessful:"<<recv_buf<<endl;
                 ofile_log << recv_buf << endl;
             }
             sprintf(send_buf,"recv %d numbers bytes\n",recv_num);
             cout << "begin send"<<endl;
             send_num = send(iConnFd,send_buf,sizeof(send_buf),0);
             if (send_num < 0)
             {
                 perror("sned");
                 exit(1);
             } 
             else 
             {
                 cout << "send sucess"<<endl;
             }
        }
}


