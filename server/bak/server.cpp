#include "server.h"

using namespace std;
ServerApp::ServerApp()
	{
		
	}
ServerApp::~ServerApp()
	{
		
	}
void ServerApp::process_info(int iConnFd)
{
	      int i(1);
        int recv_num;
        int send_num;
        char recv_buf[100];
        char send_buf[100];
        ofstream ofile_log;
        ofile_log.open("log.txt");
        while(1)
        {
             printf("begin recv:\n");
             cout << begin recv: << endl;
             recv_num = recv(iConnFd,recv_buf,40,0);
             if(recv_num <0)
             {
                 perror("recv");
                 exit(1);
             } 
             else 
             {
                 recv_buf[recv_num] = '\0';
                 printf("recv sucessful:%s\n",recv_buf);
                 ofile1 << i << "\t" << recv_buf << endl;
                 i++;
             }
             sprintf(send_buf,"recv %d numbers bytes\n",recv_num);
             printf("begin send\n");
             send_num = send(iConnFd,send_buf,sizeof(send_buf),0);
             if (send_num < 0)
             {
                 perror("sned");
                 exit(1);
             } 
             else 
             {
                 printf("send sucess\n");
             }
             
             printf("begin recv:\n");
             recv_num = recv(iConnFd,recv_buf,40,0);
             if(recv_num <0)
             {
                 perror("recv");
                 exit(1);
             } 
             else 
             {
                 recv_buf[recv_num] = '\0';
                 printf("recv sucessful:%s\n",recv_buf);
                 ofile1 << recv_buf << endl;
                 //i++;
             }
             sprintf(send_buf,"recv %d numbers bytes\n",recv_num);
             printf("begin send\n");
             send_num = send(iConnFd,send_buf,sizeof(send_buf),0);
             if (send_num < 0)
             {
                 perror("sned");
                 exit(1);
             } 
             else 
             {
                 printf("send sucess\n");
             }
        }
}
int main()
{
        int sock_fd,conn_fd;
        unsigned long client_len;
        pid_t pid;
        struct sockaddr_in addr_serv,addr_client;
        sock_fd = socket(AF_INET,SOCK_STREAM,0);
        if(sock_fd < 0)
        {
            perror("socket");
            exit(1);
        } 
        else 
        {
            printf("sock sucessful\n");
        }
        //初始化服务器端地址
        memset(&addr_serv,0,sizeof(addr_serv));
        addr_serv.sin_family = AF_INET;
        addr_serv.sin_port = htons(SOURCE_PORT);
        addr_serv.sin_addr.s_addr =inet_addr(SOURCE_IP_ADDRESS);
        client_len = sizeof(struct sockaddr_in);
        if(bind(sock_fd,(struct sockaddr *)&addr_serv,sizeof(struct sockaddr_in))<0)
        {
            perror("bind");
            exit(1);
        } 
        else 
        {
            printf("bind sucess\n");
        }
        if (listen(sock_fd,QUEUE_LINE) < 0)
        {
            perror("listen");
            exit(1);
        } 
        else 
        {
            printf("listen sucessful\n");
        }
        while(1)
        {
            printf("begin accept:\n");
            conn_fd = accept(sock_fd,(struct sockaddr *)&addr_client,&client_len);
            if(conn_fd < 0)
            {
               perror("accept");
               exit(1);
            }
            printf("accept a new client,ip:%s\n",inet_ntoa(addr_client.sin_addr));
            pid = fork();
            if(0 == pid)
            {  //子进程
               close(sock_fd);//在子进程中关闭服务器的侦听
               process_info(conn_fd);//处理信息
            } 
            else 
            {
               close(conn_fd);//在父进程中关闭客户端的连接
            }
        }
}

