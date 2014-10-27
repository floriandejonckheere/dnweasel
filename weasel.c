/**
 * weasel.c - Dawkin's Weasel Algorithm
 * 
 * Florian Dejonckheere <florian@floriandejonckheere.be>
 * 
 * */

#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "weasel.h"

static char *alphabet = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char randomChar(){
	return alphabet[(random() & 0x0ffff) * strlen(alphabet) / 0x0ffff];
}

int score(char *target, char *mutant){
	int i, score = 0;
	for(i = 0; i < strlen(target); i++){
		if(mutant[i] == target[i]) score++;
	}
	return score;
}

char* weasel(char *target, char *start){
	srand48(time(NULL));
	char parent[strlen(target)], mutant[strlen(target)];
	char *winner = malloc(strlen(target) * sizeof(char));

	int i, j;
	if(start == NULL){
		for(i = 0; i < strlen(target); i++){
			parent[i] = randomChar();
		}
	} else strncpy(parent, start, strlen(target));

	int cur_score, max_score = 0;
	for(i = 0; i < OFFSPRING; i++){
		for(j = 0; j < strlen(target); j++){
			if(drand48() < PROBABILITY) 
				mutant[j] = randomChar();
			else
				mutant[j] = parent[j];
		}
		mutant[strlen(target)] = '\0';

		cur_score = score(target, mutant);
		if(cur_score > max_score){
			strncpy(winner, mutant, strlen(target));
			max_score = cur_score;
		}
		if(cur_score == strlen(target)){
			strncpy(winner, mutant, strlen(target));
			max_score = cur_score;
			break;
		}
	}
	return winner;
}
