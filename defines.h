/*
 * defines.h
 *
 *  Created on: Mar 28, 2019
 *      Author: root
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#include "cardPrinter.h"

// The dimensions of the screen,
// in spaces and newlines, respectively
#define SCREEN_WIDTH	145
#define SCREEN_HEIGHT	48

#define SCREEN_MARGIN	2

// Coordinates of the right-hand display area
#define RIGHT_BOX_Y		2
#define RIGHT_BOX_W		30
#define RIGHT_BOX_H 	(SCREEN_HEIGHT - RIGHT_BOX_Y - SCREEN_MARGIN + 1)
#define RIGHT_BOX_X		(SCREEN_WIDTH - RIGHT_BOX_W - 1)

// The coordinates of the player's hand area
#define HAND_BOX_X	(SCREEN_MARGIN )
#define HAND_BOX_Y	(SCREEN_HEIGHT - SCREEN_MARGIN - CARD_H - 5)
#define HAND_BOX_W	(SCREEN_WIDTH - RIGHT_BOX_W - SCREEN_MARGIN - 2)
#define HAND_BOX_H	(CARD_H + 6)

#define CONTROLS_BOX_X	RIGHT_BOX_X
#define CONTROLS_BOX_W	RIGHT_BOX_W
#define CONTROLS_BOX_Y	(RIGHT_BOX_Y + 2)
#define CONTROLS_BOX_H	5

#define MESSAGE_BOX_X	(RIGHT_BOX_X + 1)
#define MESSAGE_BOX_Y	(RIGHT_BOX_Y + CONTROLS_BOX_H + 2)
#define MESSAGE_BOX_W	(RIGHT_BOX_W - 2)
#define MESSAGE_BOX_H	(RIGHT_BOX_H - CONTROLS_BOX_H - 3)

#define MAX_MESSAGES	(MESSAGE_BOX_H - 2)
#define MESSAGE_LEN		(MESSAGE_BOX_W - 2)

// Area of a box representing a player
#define PLAYER_BOX_W	20
#define PLAYER_BOX_H	12
#define PLAYER_AREA_X	2
#define PLAYER_AREA_Y	(HAND_BOX_Y - PLAYER_BOX_H - 1)

#define BUBBLE_W		(PLAYER_BOX_W - 2)
#define BUBBLE_H		6
#define BUBBLE_OFFSET_X ( ( PLAYER_BOX_W - BUBBLE_W) / 2)
#define BUBBLE_OFFSET_Y	( -BUBBLE_H - 4)

#endif /* DEFINES_H_ */
