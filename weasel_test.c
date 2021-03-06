/**
 * weasel-test.c - Test program for the algoritm
 * 
 * Florian Dejonckheere <florian@floriandejonckheere.be>
 * 
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <math.h>

#include "weasel.h"

/*
 * Uncomment the following lines if you
 * want to omit printing repeated strings
 * */
//#define OMIT_REPEATED

static struct option long_options[] = {
	{"message",	required_argument,	NULL, 'm'},
	{0}
};

void print_usage(char* progname){
	fprintf(stderr, "Usage: %s [OPTIONS]\n", progname);
	fprintf(stderr, "\t-m, --message\tTarget string (METHINKS IT IS LIKE A WEASEL)\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv){
	char *msg = "METHINKS IT IS LIKE A WEASEL";

	int c;
	while(1){
		int option_index = 0;
 
		c = getopt_long(argc, argv, "m:",
						long_options, &option_index);

		if(c == -1) break;

		switch(c){
			case 0:	break;
			case 'm':
				msg = strdup(optarg);
				break;
			default:
				fprintf(stderr, "Unknown option: %s\n", long_options[option_index].name);
				print_usage(argv[0]);
		}
	}

	char mutant[strlen(msg)];
	strncpy(mutant, msg, strlen(msg));
	char *offspring;
	int i, max_score;
	i = max_score = 0;
	do {
		offspring = weasel(msg, (i == 0 ? NULL : mutant));
		#ifdef OMIT_REPEATED
		if(strcmp(mutant, offspring) != 0)
		#endif
			printf("%s (score %i)\n", offspring, score(msg, offspring));
		if(score(msg, offspring) > max_score){
			max_score = score(msg, offspring);
			strncpy(mutant, offspring, strlen(msg));
		}
		free(offspring);
		i++;
	} while(max_score < strlen(msg));
	printf("Winner: %s (score %i) in %i iterations\n", mutant, score(msg, mutant), i);

	exit(EXIT_SUCCESS);
}
