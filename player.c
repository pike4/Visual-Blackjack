/*
 * player.c
 *
 *  Created on: Mar 27, 2019
 *      Author: root
 */

#include "player.h"
#include "output.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

player* getPlayer()
{
	player* ret = malloc(sizeof(player));

	ret->handMax = 5;
	ret->handSize = 0;
	ret->hand = malloc(sizeof(card*) * ret->handMax);
	ret->name = 0;
	ret->playing = 1;
	ret->busted = 0;

	addCard(ret, randCard());
	addCard(ret, randCard());

	return ret;
}

int getHandTotal(player* p)
{
	int ret = 0;
	int numAces = 0;

	// Count up hand excluding acesh
	for(int i = 0; i < p->handSize; i++)
	{

		if(p->hand[i]->rank == CARD_ACE) {
			numAces++;
		}

		else {
			ret += cardValue(p->hand[i]);
		}
	}

	// If aces high would put the player over, count them low
	if(ret + (numAces * 11) > 21) {
		ret += numAces;
	}

	// Otherwise count aces high
	else {
		ret += numAces * 11;
	}

	// Check if hand is natural
	if(ret == 21 && numAces == 1 && p->handSize == 2) {
		p->nat = 1;
	}

	// If a player is fucking stupid and hits when he is already holding a natural
	// then this line will become relevant
	else {
		p->nat = 0;
	}

	return ret;
}

void addCard(player* p, card* c)
{
	if(p->handSize == p->handMax)
	{
		p->hand = realloc(p->hand, sizeof(card*) * p->handMax * 2);
	}

	p->hand[p->handSize++] = c;
}

void freePlayer(player* p)
{
	if(!p) {
		return;
	}

	if(p->hand) {
		// Free each card in the player's hand
		for(int i = 0; i < p->handSize; i++) {
			free(p->hand[i]);
		}

		// Free the player's hand buffer
		free(p->hand);
	}

	if(p->name)
	{
		// Free the player's name
		free(p->name);
	}

	// Free the player
	free(p);
}

void genPlayers(int count)
{
	for(int i = 0; i < count; i++)
	{
		player* p = getPlayer();

		p->name = strdup(firstNames[rand() % NUM_NAMES]);

		cpuPlayers[i] = p;
	}
}

void hit(player* p)
{
	card* c = randCard();

	char buf[500];
	snprintf(buf, 500, "%s hits", p->name);
	say(buf);

	addCard(p, c);

	int tot = getHandTotal(p);

	if(tot > 21) {
		p->busted = 1;
		p->playing = 0;

		snprintf(buf, 500, "%s%s busted!%s", FG_RED, p->name, FG_WHITE);
		say(buf);

	} else if(tot == 21) {
		p->playing = 0;
	}
}

// Make the given player stand
void stand(player* p)
{
	p->playing = 0;

	char buf[500];
	snprintf(buf, 500, "%s stands", p->name);
	say(buf);
}

player* user;
player* dealer;

int numCPUs = 4;
player* cpuPlayers[4];

char* firstNames[NUM_NAMES] = {
"Liam", "Emma", "Noah", "Olivia", "William", "Ava",
"James", "Isabella", "Logan", "Sophia", "Benjamin", "Mia", "Mason", "Charlotte",
"Elijah", "Amelia", "Oliver", "Evelyn", "Jacob", "Abigail", "Lucas", "Harper",
"Michael", "Emily", "Alexander","Elizabeth", "Ethan", "Avery", "Daniel",	"Sofia",
"Matthew", "Ella", "Aiden", "Madison", "Henry", "Scarlett", "Joseph", 	"Victoria",
"Jackson", "Jehoram"};
