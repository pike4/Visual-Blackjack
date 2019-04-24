/*
 * Blackjack.h
 *
 *  Created on: Mar 26, 2019
 *      Author: root
 */

#ifndef BLACKJACK_H_
#define BLACKJACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "output.h"
#include "input.h"
#include "card.h"
#include "player.h"

extern char username[52];
extern int acesHigh;

extern player* winners[5];
extern int numWinners;

void updateCPUs();
int checkWin();
void dealerTurn();
void finalTally();

void init();
void quit();

#endif /* BLACKJACK_H_ */
