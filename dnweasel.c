/*
 * dnweasel.c - Dawkins' Network Weasel
 * 
 * */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#define	PORT	1234

static struct option long_options[] =
{
	{"listen",	no_argument,		NULL, 'l'},
	{"port",	required_argument,	NULL, 'p'},
	{"hostname",	required_argument,	NULL, 'h'},
	{"message",	required_argument,	NULL, 'm'},
	{0}
};

void print_usage(char** argv){
	fprintf(stderr, "Usage:\tListen for inbound:\t%s -l [-p port]\n", argv[0]);
	fprintf(stderr, "\tConnect to somewhere:\t%s -h hostname -m message [-p port]\n", argv[0]);
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
	/** options **/
	int port = PORT;
	char *host = NULL;
	char *msg = NULL;
	bool listen = false;

	int c;
	while (1)
	{
		int option_index = 0;
 
		c = getopt_long(argc, argv, "lp:h:m:",
						long_options, &option_index);
 
		if(c == -1) break;

		switch (c)
		{
			case 'l':
				listen = true;
				break;
			case 'p':
				port = atoi(optarg);
				break;
			case 'h':
				host = strndup(optarg, 15);
				break;
			case 'm':
				msg = strdup(optarg);
				break;
			default:
				print_usage(argv);
		}
	}


/*	if(listen == false && optind < argc)
	{
		//const char *get_argv = argv[optind++];
		printf("%i < %i\n", optind, argc);
	}*/

	if(listen == true){
		printf("Listening on port %i\n", port);
	} else {
		if(host == NULL || msg == NULL)
			print_usage(argv);
		printf("Connecting to %s...\n", host);
		printf("Sending %s\n", msg);
	}

	//free(host);
	//free(msg);

	return 0;
}
