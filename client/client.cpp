#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
                                                                                       
#define DEST_PORT 61111                                                                 
#define DEST_IP_ADDRESS "192.168.4.124"                                                  
      
using namespace std; 
string cmd_system(const char* vCmd)
{
   string tRet = "";
   FILE *fpRead;
   fpRead = popen(vCmd, "r");
   char str[1024] = {0};
   while (fgets(str, 1024 - 1, fpRead) != NULL)
   {
      tRet += str;
      memset(str, 0, sizeof(str));
   }
   if(fpRead != NULL)
    fclose(fpRead);
   return tRet;
}                                                                                
//client process                                                                   
void process_info(int s)                                                               
{                                                                                      
        int send_num;                                                                  
        int recv_num;     
        string strResult,strComd;                                                            
        char send_buf[1024];                                                   
        char recv_buf[1024];   
        char str[1024];
                                                     
        while(1)
        { 
           cout<<"begin send" << endl;
           cout<<"input your command:";
           cin.getline(str, 1024-1);
           cout<<str<<endl;   
           send_num = send(s,str,sizeof(send_buf),0);                        
           if (send_num < 0)
           {                                                     
              perror("send");                                              
              exit(1);
           } 
           else 
           {          
           	  cout<<"send sucess:"<<str <<endl;
           }
           cout<<"begin recv" << endl;
           recv_num = recv(s,recv_buf,sizeof(recv_buf),0);                        
           if(recv_num < 0)
           {                                                      
              perror("recv");                                                
              exit(1);                                                       
           } 
           else 
           {                                                               
              recv_buf[recv_num]='\0';
              cout << "recv sucessful: "<< recv_buf<< endl;
           }          
           
           printf("begin send the result\n");
           strResult = cmd_system(str);
           send_num = send(s,strResult.c_str(),sizeof(send_buf),0);
           if (send_num < 0)
           {                                                     
              perror("send");
              exit(1);
           } 
           else 
           {          
           	  cout<<"send sucess:"<<strResult.c_str() <<endl;
           }
           cout << "begin recv:"<<endl;
           recv_num = recv(s,recv_buf,sizeof(recv_buf),0);
           if(recv_num < 0)
           {                                                      
              perror("recv");
              exit(1);
           } 
           else 
           {                                                               
              recv_buf[recv_num]='\0';
              cout << "recv sucessful: "<< recv_buf<< endl;
           }                                                                    
        }                                                                              
}                                                                                      
int main(int argc,char *argv[])                                                        
{                                                                                      
        int sock_fd;
        struct sockaddr_in addr_serv;//·þÎñÆ÷¶ËµØÖ·
                                                                                       
        sock_fd = socket(AF_INET,SOCK_STREAM,0);
        if(sock_fd < 0)
        {                                                               
           perror("sock");
           exit(1);
        } 
        else 
        { 
           cout << "sock sucessful"<<endl;
        }                                                                              
       memset(&addr_serv,0,sizeof(addr_serv));
       addr_serv.sin_family = AF_INET;
       addr_serv.sin_port =  htons(DEST_PORT);
       addr_serv.sin_addr.s_addr = inet_addr(DEST_IP_ADDRESS);
       if( connect(sock_fd,(struct sockaddr *)&addr_serv,sizeof(struct sockaddr)) < 0)
       {
          perror("connect");
          exit(1);
       } 
       else 
       { 
          cout << "connect sucessful"<<endl;
       }                                                                               
       process_info(sock_fd);
       close(sock_fd);
}                                                                                      