/*
 * cardPrinter.h
 *
 *  Created on: Mar 27, 2019
 *      Author: root
 */

#ifndef CARDPRINTER_H_
#define CARDPRINTER_H_

#include "card.h"

// The width, in character widths and heights,
// respectively, of a printed playing card
#define	CARD_W	12
#define CARD_H	9
#define CARD_MID_X	(CARD_W / 2)
#define CARD_MID_Y	(CARD_H / 2)

// The margins of the card.
// Values are relative to the top left of the card
#define L_MARGIN	1
#define	R_MARGIN	(CARD_W - 2)
#define T_MARGIN	1
#define B_MARGIN	(CARD_H - 2)

extern int COORDS[10][10][2];

int checkPattern(int rank, int x, int y);
void printCard(int suit, int rank);

void printSuit(int suit);
void printRank(int rank);

#endif /* CARDPRINTER_H_ */
