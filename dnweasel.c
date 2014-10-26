/**
 * 
 * dnweasel.c - Dawkins' Network Weasel
 * 
 * Florian Dejonckheer <florian@floriandejonckheere.be>
 * 
 * */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define	PORT		8376
#define	MAX_LEN		4096
#define	BACKLOG		5

static struct option long_options[] = {
	{"listen",	no_argument,		NULL, 'l'},
	{"port",	required_argument,	NULL, 'p'},
	{"hostname",	required_argument,	NULL, 'h'},
	{"message",	required_argument,	NULL, 'm'},
	{0}
};

void die(char* msg){
	fprintf(stderr, "E: %s\n", msg);
	exit(EXIT_FAILURE);
}

void print_usage(char* progname){
	fprintf(stderr, "Usage:\tListen for inbound:\t%s -l [-p port]\n", progname);
	fprintf(stderr, "\tConnect to somewhere:\t%s -h hostname -m message [-p port]\n", progname);
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv){
	int port = PORT;
	char *host = NULL;
	char *msg = NULL;
	bool server = false;

	int c;
	while(1){
		int option_index = 0;
 
		c = getopt_long(argc, argv, "lp:h:m:",
						long_options, &option_index);

		if(c == -1) break;

		switch(c){
			case 0:	break;
			case 'l':
				server = true;
				break;
			case 'p':
				port = atoi(optarg);
				break;
			case 'h':
				host = strndup(optarg, INET_ADDRSTRLEN);
				break;
			case 'm':
				msg = strdup(optarg);
				break;
			default:
				fprintf(stderr, "Unknown option: %s\n", long_options[option_index].name);
				print_usage(argv[0]);
		}
	}


	if(server){
		/** Server **/
		if(host != NULL && msg != NULL)
			print_usage(argv[0]);

		printf("Listening on port %i\n", port);

		char buffer[MAX_LEN];
		int sock_srv, sock_cli;
		struct sockaddr_in addr_srv, addr_cli;
		socklen_t sin_size = sizeof(struct sockaddr_in);

		sock_srv = socket(AF_INET, SOCK_STREAM, 0);
		if(sock_srv < 0){
			perror("socket");
			exit(EXIT_FAILURE);
		}

		int optval = 1;
		if(setsockopt(sock_srv, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval) < 0){
			perror("setsockopt");
			exit(EXIT_FAILURE);
		}

		bzero((char *) &addr_srv, sizeof(addr_srv));
		addr_srv.sin_family = AF_INET;
		addr_srv.sin_addr.s_addr = INADDR_ANY;
		addr_srv.sin_port = htons(PORT);

		if(bind(sock_srv, (struct sockaddr *) &addr_srv, sizeof(addr_srv)) < 0){
			perror("bind");
			close(sock_srv);
			exit(EXIT_FAILURE);
		}
		if(listen(sock_srv, BACKLOG) < 0){
			perror("listen");
			close(sock_srv);
			exit(EXIT_FAILURE);
		};

		sin_size = sizeof(addr_cli);
		sock_cli = accept(sock_srv, (struct sockaddr *) &addr_cli, &sin_size);
		if(sock_cli < 0){
			perror("accept");
			exit(EXIT_FAILURE);
		}

		while(1){
			bzero(buffer, MAX_LEN);

			int bytes;
			if((bytes = recv(sock_cli, buffer, MAX_LEN, 0)) == -1){
				perror("recv");
				close(sock_cli);
				continue;
			}
			buffer[bytes] = '\0';

			// Stop on client close()
			if(!bytes) break;

			char ip4[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &(addr_cli.sin_addr), ip4, INET_ADDRSTRLEN);
			printf("> %s: %s (%i bytes)\n", ip4, buffer, bytes);

			printf("< %s: %s\n", ip4, buffer);
			if(send(sock_cli, buffer, strlen(buffer), 0) < 0){
				perror("send");
				close(sock_cli);
				continue;
			}
		}

		close(sock_cli);
		close(sock_srv);
		return EXIT_SUCCESS;

	} else {
		/** Client **/
		if(host == NULL || msg == NULL)
			print_usage(argv[0]);

		printf("Connecting to %s...\n", host);

		char buffer[MAX_LEN];
		int sock;
		struct sockaddr_in addr_srv;

		sock = socket(AF_INET, SOCK_STREAM, 0);
		if(sock < 0){
			perror("socket");
			exit(EXIT_FAILURE);
		}

		bzero(&addr_srv, sizeof(struct sockaddr));
		addr_srv.sin_family = AF_INET;
		if(inet_pton(AF_INET, host, &(addr_srv.sin_addr)) <= 0){
			perror("inet_pton");
			close(sock);
			exit(EXIT_FAILURE);
		}
		addr_srv.sin_port = htons(port);

		if(connect(sock, (struct sockaddr *) &addr_srv, sizeof(struct sockaddr)) < 0){
			perror("connect");
			close(sock);
			exit(EXIT_FAILURE);
		}

		int i;
		for(i = 0; i < 1024; i++){
			strncpy(buffer, msg, MAX_LEN);

			printf("< %s: %s\n", host, msg);
			if(send(sock, buffer, strlen(buffer), 0) < 0){
				perror("send");
				close(sock);
				continue;
				//~ exit(EXIT_FAILURE);
			}

			bzero(buffer, MAX_LEN);
			int bytes;
			if((bytes = recv(sock, buffer, MAX_LEN, 0)) == -1){
				perror("recv");
				close(sock);
				continue;
				//~ exit(EXIT_FAILURE);
			}
			buffer[bytes] = '\0';
			printf("> %s: %s (%i bytes)\n", host, buffer, bytes);
		}

		close(sock);
		return EXIT_SUCCESS;
	}

	if(host)	free(host);
	if(msg)		free(msg);

	return 0;
}
