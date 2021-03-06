#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEST_PORT 8000
#define DEST_IP_ADDR "192.168.177.128"

void process_info(int fd)
{
	int send_num;
	char send_buf [] = "helloworld";
	char recv_buf [20];
	while (1)
	{
		printf("begin send\n");
		send_num = send(fd, send_buf, sizeof(send_buf),0);
		if (send_num < 0)
		{
			perror("send error");
			exit(1);
		}
		else
		{
		printf("send successful\n");
		printf("begin recv:\n");
		int recv_num = recv(fd,recv_buf,sizeof(recv_buf),0);
		 if(recv_num < 0){
			perror("recv");
			exit(1);
		} else {
		        recv_buf[recv_num]='\0';
		    	printf("recv sucess:%s\n",recv_buf);
				}
		 }		
		sleep(5);
	}
}


int main()
{
	int sock_fd;
	struct sockaddr_in addr_serv;
	sock_fd=socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0)
	{
		perror("sock error");
		exit(1);
	}
	else
	{
		printf("sock successful");		
	}
	memset(&addr_serv, 0, sizeof(addr_serv));
	addr_serv.sin_family = AF_INET;
	addr_serv.sin_port = htons(DEST_PORT);
	addr_serv.sin_addr.s_addr = inet_addr(DEST_IP_ADDR);
	if (connect(sock_fd, (struct sockaddr*)(&addr_serv), sizeof(addr_serv)) < 0)
	{
		perror("connect error\n");
		exit(1);
	}
	else
	{
		printf("connect successful\n");
	}
	process_info(sock_fd);
}
