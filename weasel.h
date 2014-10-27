/**
 * weasel.h - Dawkin's Weasel Algorithm
 * 
 * Florian Dejonckheere <florian@floriandejonckheere.be>
 * 
 * */

#ifndef WEASEL_H
#define WEASEL_H

#define	PROBABILITY	0.05
#define	OFFSPRING	100

char* weasel(char *target, char *start);
int score(char *target, char *mutant);
char randomChar();

#endif
