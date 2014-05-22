#include <iostream>
#include "server.h"

int main()
{
	      ServerApp  serverApp;
	      int iRet;
        pid_t pid;        
        fd_set fdsr;
        int maxsock;        
        int iOptval = 1;
        int conn_amount = 0;
        int sock_fd,conn_fd;
        int fd_Col[MAXCLENT];
        unsigned long client_len;
        struct timeval tv;
        struct sockaddr_in addr_serv,addr_client;
        
        
        sock_fd = socket(AF_INET,SOCK_STREAM,0);
        if(sock_fd < 0)
        {
            perror("socket");
            exit(1);
        } 
        else 
        {
            cout << "sock sucessful" << endl;
        }
        if(-1 == setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR,&iOptval, sizeof(int)))
        {
        	  perror("setsockopt");
            exit(1); 
        }
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
            cout << "bind sucess" << endl;
        }
        if (listen(sock_fd,QUEUE_LINE) < 0)
        {
            perror("listen");
            exit(1);
        } 
        else 
        {
            cout << "listen sucessful" << endl;
        }
        maxsock = sock_fd;
        while (1) 
        {
        	  FD_ZERO(&fdsr);
            FD_SET(sock_fd, &fdsr);

            tv.tv_sec = 30;
            tv.tv_usec = 0;
           
            for (int i = 0; i < MAXCLENT; i++) 
            {
                if (fd_Col[i] != 0) 
                {
                    FD_SET(fd_Col[i], &fdsr);
                }
            }

            iRet = select(maxsock + 1, &fdsr, NULL, NULL, &tv);
            if (iRet < 0) 
            {
                perror("select");
                break;
            } 
            else if (iRet == 0) 
            {
                cout << "timeout" << endl;
                continue;
            }
            
            if (FD_ISSET(sock_fd, &fdsr))
            {
                conn_fd = accept(sock_fd,(struct sockaddr *)&addr_client,&client_len);
                if (conn_fd <= 0)
                {
                    perror("accept");
                    continue;
                }
                if (conn_amount < MAXCLENT) 
                {
                    fd_Col[conn_amount++] = conn_fd;
                    cout << "accept a new client,ip:" << inet_ntoa(addr_client.sin_addr)<< endl;
                    if (conn_fd > maxsock)
                      maxsock = conn_fd;
                }
                else
                {
                    cout << "this is the max client" << endl;
                    send(conn_fd, "bye", 4, 0);
                    close(conn_fd);
                    break;
                }
            }
            for (int i = 0; i < conn_amount; i++)
            {
                if (FD_ISSET(fd_Col[i], &fdsr))
                {
                   serverApp.process_info(fd_Col[i]);//处理信息                   
                }
            }
        }
        for (int i = 0; i < MAXCLENT; i++)
        {
            if (fd_Col[i] != 0)
            {
                 close(fd_Col[i]);
            }
        }
}