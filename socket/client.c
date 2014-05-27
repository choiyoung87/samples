#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MAX_MSG_LEN		4096

int main(int argc, char** argv)
{
	struct sockaddr_in    serv_addr;
	int sockfd;
	int err;
	char recvline[MAX_MSG_LEN], sendline[MAX_MSG_LEN];

	if(argc != 2){
		printf("usage: ./client <ipaddress>\n");
		return -1;
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd  < 0) {
		printf("create socket error\n");
		return -1;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(6666);

	err = inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);
	if (err <= 0) {
		printf("inet_pton error for %s\n",argv[1]);
		return -1;
	}

	err = connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if (err < 0) {
		printf("connect error\n");
		return -1;
	}

	printf("send msg to server:\n");

	memset(sendline, 0, MAX_MSG_LEN);
	fgets(sendline, MAX_MSG_LEN, stdin);

	err = send(sockfd, sendline, strlen(sendline), 0);
	if (err < 0) {
		printf("send msg error\n");
		return -1;
	}

	close(sockfd);
	return 0;
}
