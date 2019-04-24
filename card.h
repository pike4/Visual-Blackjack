/*
 * cards.h
 *
 *  Created on: Mar 27, 2019
 *      Author: root
 */

#ifndef CARD_H_
#define CARD_H_

#define CLUBS		0
#define HEARTS		1
#define SPADES		2
#define DIAMONDS	3
#define NUM_SUITS	4

#define CARD_ACE	1
#define CARD_2		2
#define CARD_3		3
#define CARD_4		4
#define CARD_5		5
#define CARD_6		6
#define CARD_7		7
#define CARD_8		8
#define CARD_9		9
#define CARD_10		10
#define CARD_JACK	11
#define CARD_QUEEN	12
#define CARD_KING	13
#define NUM_CARDS	14

#define FACE_CARD_VAL	10

typedef struct _card
{
	int suit;
	int rank;

	int flipped;
} card;


// Return the score value of the given card
int cardValue(card* c);

// Return a card of a random suit and rank
card* randCard();

// Return a card of a given suit and rank
card* getCard(int s, int v);



#endif /* CARD_H_ */
