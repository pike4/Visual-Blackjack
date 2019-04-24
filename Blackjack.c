/*
 * Blackjack.c
 *
 *  Created on: Mar 26, 2019
 *      Author: root
 */


#include "Blackjack.h"

#include "player.h"
#include "card.h"

#include "defines.h"

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#include <time.h>

struct termios orig_termios;

int acesHigh = 0;

int topScore = 0;

player* winners[5];
int numWinners = 0;

void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);
  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void init()
{
	srand(time(0));
	clearScreen();

	numWinners = 0;
	memset(winners, 0, 5);

	user = getPlayer();
	dealer = getPlayer();

	dealer->name = strdup("Dealer");
	dealer->hand[0]->flipped = 1;

	getName();
	getNumCPUs();

	genPlayers(numCPUs);

	enableRawMode();
}

// Free memory and clean up the terminal before quitting
void quit()
{

	cleanUp();
	setColors(RESET, RESET);
	cursorExit();

	exit(0);
}

// Free all players and cards and reset variables for next iteration
void cleanUp()
{
	freePlayer(user);
	user = 0;
	freePlayer(dealer);
	dealer = 0;

	for(int i = 0; i < numCPUs; i++)
	{
		freePlayer(cpuPlayers[i]);
		cpuPlayers[i] = 0;
	}

	// Clean up variables
	msgStartIndex = 0;
	msgAddIndex = 0;
	numMessages = 0;

	numCPUs = 0;
}

void finalTally()
{
	int dealerScore = getHandTotal(dealer);

	int numFinalWinners = 0;

	// Determine the number of winners
	for(int i = 0; i < numWinners; i++)
	{
		if(getHandTotal(winners[i]) > dealerScore) {
			numFinalWinners++;
		}
	}

	char sayBuf[200];

	say("Final Tally:");
	say(" ");

	winners[0] = user;
	for(int i = 0; i < numCPUs; i++) {
		winners[i + 1] = cpuPlayers[i];
	}


	// Determine win conditions for each player
	for(int i = 0; i < numCPUs + 1; i++)
	{
		if( (getHandTotal( winners[i] ) < dealerScore && dealer->busted == 0) || winners[i]->busted == 1) {
			sprintf(sayBuf, "%s: lose", winners[i]->name);
		}

		else if(getHandTotal(winners[i]) > dealerScore || dealer->busted == 1) {
			sprintf(sayBuf, "%s: win", winners[i]->name);
		}

		else {
			sprintf(sayBuf, "%s: pull", winners[i]->name);
		}

		say(sayBuf);
	}

	printScreen();
}

void dealerTurn()
{
	dealer->hand[0]->flipped = 0;

	say(" ");
	say("Dealer's turn");
	say(" ");
	printScreen();

	// Determine the dealer's goal score. Goal min is 17
	int goal = 17;

	// Goal is the min of 17 and the highest surviving player score
	if(getHandTotal(user) > goal && !user->busted) {
		goal = getHandTotal(user);
	}

	for(int i = 0; i < numCPUs; i++) {
		if(getHandTotal(cpuPlayers[i]) > goal && !cpuPlayers[i]->busted) {
			goal = getHandTotal(cpuPlayers[i]);
		}
	}


	// The dealer hits until he exceeds the goal
	while(getHandTotal(dealer) < goal) {
		usleep(1000000);
		hit(dealer);
		printScreen();
	}

	say(" ");
}

int checkWin()
{
	// check if any CPUs are in the game
	for(int i = 0; i < numCPUs; i++)
	{
		if(cpuPlayers[i] -> playing) {
			return 0;
		}
	}

	// check if the player is still in the game
	if(user->playing) {
		return 0;
	}

	if(user->busted == 0) {
		winners[0] = user;
		numWinners++;
	}

	for(int i = 0; i < numCPUs; i++) {

		if(cpuPlayers[i]->busted) {
			continue;
		}
		else  {
			winners[numWinners++] = cpuPlayers[i];
		}
	}

	return 1;
}

void updateCPUs()
{
	for(int i = 0; i < numCPUs; i++)
	{
		if(!cpuPlayers[i]->playing) {
			continue;
		}

		int x = PLAYER_AREA_X + (i * (2 + PLAYER_BOX_W)) + BUBBLE_OFFSET_X;
		int y = PLAYER_AREA_Y + BUBBLE_OFFSET_Y;

		speakOneAtATime(x, y, "...");

		// Decide to fold or stand
		int val = getHandTotal(cpuPlayers[i]);

		int threshold = 21 - val - 1 + 10;

		int choice = rand() % 21;

		if(choice < threshold || val < 11)
		{
			printSpeechBubble(x, y, "Hit!", 4);
			hit(cpuPlayers[i]);
		}

		else {
			printSpeechBubble(x, y, "Stand...", 8);
			stand(cpuPlayers[i]);
		}

		usleep(400000);
		printScreen();
		printSpeechBubble(x, y, 0, 0);
	}
}
