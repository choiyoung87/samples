#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MAX_REQ_NR		32
#define MAX_MSG_LEN		4096

int main(int argc, char** argv)
{
	struct sockaddr_in server_addr;
	int listen_fd, request_fd;
	int err, len;
	char    buff[MAX_MSG_LEN];

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd < 0) {
		printf("create socket error\n");
		return -1;
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(6666);

	err = bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (err < 0) {
		printf("bind socket error\n");
		return -1;
	}

	err = listen(listen_fd, MAX_REQ_NR);
	if (err < 0) {
		printf("listen socket error\n");
		return -1;
	}

	printf("start loop\n");

	while(1) {
		request_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
		if(request_fd < 0) {
			printf("accept socket error\n");
			continue;
		}
		len = recv(request_fd, buff, MAX_MSG_LEN, 0);
		buff[len] = '\0';
		printf("recv msg: %s\n", buff);
		close(request_fd);
	}

	close(listen_fd);
}
