/*
 * main.c
 *
 *  Created on: Mar 26, 2019
 *      Author: root
 */

#include "Blackjack.h"
#include "player.h"
#include "card.h"
#include "input.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{

	// Main loop
	// Each iteration is one full game
	while(1)
	{
		init();

		for(int i = 0; i < 5; i++)
		{
			printf("\a");
			fflush(stdout);
			usleep(1000* 100);
		}

		printf("\n");

		reserveSpace();
		printScreen();

		// Each iteration is one turn
		while(1)
		{
			printScreen();
			if(user->playing) {
				getInput();
			}

			printScreen();
			fflush(stdout);
			updateCPUs();

			if(checkWin()) {
				say("Winner...");
				printScreen();
				fflush(stdout);
				break;
			}

			usleep(100000);
		}

		// If all players busted
		if(numWinners == 0) {
			say("No winners.");
			say("The house wins!");
			printScreen();
		}

		//
		else {

			// Display the current set of players still in the game
			say(" ");
			say("Current leaders:");
			printScreen();
			fflush(stdout);

			for(int i = 0; i < numWinners; i++) {
				say(winners[i]->name);
			}

			// Take the dealer's turn and wrap up the game
			printScreen();
			dealerTurn();
			finalTally();
		}

		say(" ");
		say("Game over. Press any key to play again or escape to quit.");
		flushStdIn();
		printScreen();

		char cc = getchar();

		if(cc == 27) {
			break;
		}

		cleanUp();

		cursorExit();
	}

	quit();
}
