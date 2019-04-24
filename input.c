/*
 * input.c
 *
 *  Created on: Mar 26, 2019
 *      Author: root
 */


#include "Blackjack.h"
#include "input.h"
#include "player.h"
#include <string.h>
#include <fcntl.h>
#include <errno.h>
char username[52];
char numBuf[50];

#define IS_NUM(X) ((X) >= '0' && (X) <= '9')

void flushStdIn()
{
	int flags = fcntl(0, F_GETFL);
	fcntl(0, F_SETFL, O_NONBLOCK);

	while(getchar() != EOF) {}

	fcntl(0, F_SETFL, flags);
}


void getName()
{
	printf("Your name, please: ");

	if(fgets(username, 52, stdin) == 0) {
		printf("Could not get username\n");
	}

	else if(username[strlen(username) - 1] == '\n')
	{
		username[strlen(username) - 1] = 0;
	}

	user->name = strndup(username, 50);

	if(strnlen(username, 52) > 50) {
		printf("That's a pretty long name. Is it foreign or something? I'll call you %s for short\n", user->name);
	}

	flushStdIn();
}

void getNumCPUs()
{
	printf("Welcome to the tables, %s. ", username);

	long int nP = 0;

	while(1)
	{
		printf("How many other players will you be with this evening? ");
		if(fgets(numBuf, 50, stdin) == 0) {
			printf("I'm sorry, I can't quite understand you\n");
		}

		int notNum = 0;

		for(int i = 0; i < strlen(numBuf); i++) {
			if( !IS_NUM(numBuf[i]) && numBuf[i] != '\n' && numBuf[i] != '-') {
				notNum = 1;
			}
		}

		nP = strtol(numBuf, 0, 10);

		flushStdIn();

		if(notNum) {
			printf("That's not a number\n");
		}

		else if(errno == ERANGE)
		{
			printf("That's way too many\n");
			flushStdIn();
		}

		else if(nP < 0)
		{
			printf("You want a negative number of players?\n");
		}

		else if(nP > 4)
		{
			printf("I'm sorry, but the table only seats 4 other players\n");
		}

		else
		{
			break;
		}
	}

	numCPUs = nP;
}

void getInput()
{
	flushStdIn();

	say(" ");
	say("\e[32mYour turn\e[37m");
	say(" ");
	printLog();

	char c = 0;

	while(1)
	{
		c = getchar();

		if(c == 'h') {
			hit(user);
			break;
		}

		else if(c == 's') {
			stand(user);
			break;
		}

		else if(c == 27) {
			quit();
		}
	}
}
