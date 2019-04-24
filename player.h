/*
 * player.h
 *
 *  Created on: Mar 27, 2019
 *      Author: root
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "card.h"

#define NUM_NAMES 40

typedef struct _player
{
	// The user's display name
	char* name;

	// Number of cards in the player's hand
	int handSize;

	// Max number of cards the player's hand can hold
	int handMax;

	// Array of cards held by the player
	card** hand;

	// 0 if the player is no longer in the game
	int playing;

	// 0 if the player is not currently busted
	int busted;

	// 1 if the player is currently holding a natural
	int nat;

	// 1 if the player is counting aces high
	int acesHigh;
} player;

// Return the combined total value of a player's hand
int getHandTotal(player* p);

// Free a player and all associated data
void freePlayer(player* p);

// Allocate a new player and return
player* getPlayer();

// Add the given card to the given players hand
void addCard(player* p, card* c);

// Generate the given number of players
void genPlayers(int count);

// Make the given player hit, for good or ill
void hit(player* p);

// Make the given player stand
void stand(player* p);

extern int numCPUs;
extern player* cpuPlayers[4];


extern player* user;
extern player* dealer;

extern char* firstNames[NUM_NAMES];

#endif /* PLAYER_H_ */
