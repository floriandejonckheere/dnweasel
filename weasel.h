/**
 * weasel.h - Dawkin's Weasel Algorithm
 * 
 * Florian Dejonckheere <florian@floriandejonckheere.be>
 * 
 * */

#ifndef WEASEL_H
#define WEASEL_H

#define	PROBABILITY	0.01
#define	OFFSPRING	100

/*
 * Uncomment the following line if you want to enable character locking
 * This ensures a much faster convergence to the target string
 * 
 * */
//#define	LOCKING

char* weasel(char *target, char *start);
int score(char *target, char *mutant);
char randomChar();

#endif
