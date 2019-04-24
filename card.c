/*
 * card.c
 *
 *  Created on: Mar 27, 2019
 *      Author: root
 */

#include "card.h"
#include "Blackjack.h"
#include <stdlib.h>

int cardValue(card* c)
{
	if(c->rank >= CARD_2 && c->rank <= CARD_10) {
		return c->rank;
	}

	else if(c->rank >= CARD_JACK || acesHigh ) {
		return FACE_CARD_VAL;
	}

	else return 1;
}

card* getCard(int s, int v)
{
	card* ret = malloc(sizeof(card));

	ret->rank = v;
	ret->suit  = s;
	ret->flipped = 0;

	return ret;
}

card* randCard()
{
	int suit = rand() % NUM_SUITS;
	int rank = 1 + (rand() % (NUM_CARDS - 1));

	return(getCard(suit, rank));
}
