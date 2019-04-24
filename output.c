/*
 * output.c
 *
 *  Created on: Mar 27, 2019
 *      Author: root
 */

#include "Blackjack.h"
#include "cardPrinter.h"

#include "card.h"
#include "player.h"

#include "defines.h"

#include <string.h>

const char* CLUB = "\xe2\x99\xa3";
const char* SPADE = "\xe2\x99\xa0";
const char* HEART = "\xe2\x99\xa5";
const char* DIAMOND = "\xe2\x99\xa6";

const char* BG_RESET	= "\e[49m";
const char* BG_RED		= "\e[41m";
const char* BG_BLUE		= "\e[44m";
const char* BG_BLACK	= "\e[40m";
const char* BG_WHITE	= "\e[107m";
const char* BG_GREY		= "\e[37m";
const char* BG_GREEN	= "\e[32m";

const char* FG_RESET	= "\e[39m";
const char* FG_RED		= "\e[31m";
const char* FG_BLUE		= "\e[34m";
const char* FG_BLACK	= "\e[30m";
const char* FG_WHITE	= "\e[97m";
const char* FG_GREY		= "\e[47m";
const char* FG_GREEN	= "\e[42m";

const char* CLEAR_SCREEN = "\e[2J";

char playerHandBoxStr[50];
char playerHandValStr[25];

void cursorExit()
{
	disableRawMode();
	setColors(RESET, RESET);
	setCursor(0, SCREEN_HEIGHT);
	printf("\n");
}

void clearLine()
{
	setColors(RESET, RESET);
	moveCursor(-SCREEN_WIDTH, 0);

	for(int i = 0; i < SCREEN_WIDTH; i++)
	{
		printf(" ");
	}

	moveCursor(-SCREEN_WIDTH, 0);
}

void say(char* msg)
{
	strncpy( &messages[msgAddIndex][0], msg, MESSAGE_LEN);
	if(numMessages == MAX_MESSAGES) {
		msgStartIndex = (msgStartIndex + 1) % MAX_MESSAGES;
	}

	else {
		numMessages++;
	}

	msgAddIndex = (msgAddIndex + 1) % MAX_MESSAGES;

	if(strlen(msg) > MESSAGE_LEN) {
		say(msg + MESSAGE_LEN);
	}
}

void refresh()
{
	setCursor(0, 0);

	setColors(BLUE, BLUE);

	for(int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for(int x = 0; x < SCREEN_WIDTH; x++)
		{
			printf(" ");
		}

		printf("\n");
	}

	moveCursor(-SCREEN_WIDTH, -SCREEN_HEIGHT);
}

void clearScreen()
{
	printf("%s", CLEAR_SCREEN);
	/*setColors(RESET, RESET);
	setCursor(0, SCREEN_HEIGHT);

	for(int i = 0; i < SCREEN_HEIGHT; i++)
	{
		clearLine();
		moveCursor(0, -1);
	}*/
}

void printHandTotal(player* p)
{
	int val = getHandTotal(p);

	printf("Total: ");

	if(val > 21) {
		setColors(NOCHANGE, RED);
		printf("BUST!");
	}

	else if(p->nat) {
		setColors(NOCHANGE, BLUE);
		printf("Natural!");
	}

	else {
		setColors(NOCHANGE, BLACK);
		printf("%d", val);
	}
}

void printLog()
{
	fillArea(MESSAGE_BOX_X, MESSAGE_BOX_Y, MESSAGE_BOX_W, MESSAGE_BOX_H, BLACK);

	setColors(BLACK, WHITE);

	for(int i = 0; i < numMessages; i++)
	{
		setCursor(MESSAGE_BOX_X + 1, MESSAGE_BOX_Y + i + 1);
		printf("%.*s", MESSAGE_LEN, messages[(i + msgStartIndex) % MAX_MESSAGES]);
	}
}

void printScreen()
{
	refresh();

	// Print the dealer's hand box
	fillArea(HAND_BOX_X, 6, HAND_BOX_W, HAND_BOX_H - 3, GREEN);
	printBox(HAND_BOX_X, 3, HAND_BOX_W, HAND_BOX_H, BLUE);
	printTextBox(HAND_BOX_X, 3, "Dealer's hand", WHITE, BLACK);

	// Print dealer hand value label
	int dealerLabelX =  HAND_BOX_W - HAND_BOX_X - 16;
	printBox(dealerLabelX, 3, 20, 3, BLUE);
	setCursor(dealerLabelX + 2, 4);
	setColors(WHITE, BLACK);
	printHandTotal(dealer);

	// Print the user's hand box
	fillArea(HAND_BOX_X, HAND_BOX_Y + 3, HAND_BOX_W, HAND_BOX_H - 3, GREEN);
	printBox(HAND_BOX_X, HAND_BOX_Y, HAND_BOX_W, HAND_BOX_H, BLUE);

	// Print hand box label
	sprintf(playerHandBoxStr, "%s's hand", user->name);
	printTextBox(HAND_BOX_X, HAND_BOX_Y, playerHandBoxStr, WHITE, BLACK);

	// Print hand value label
	int handBoxX =  HAND_BOX_W - HAND_BOX_X - 16;
	printBox(handBoxX, HAND_BOX_Y, 20, 3, BLUE);
	setCursor(handBoxX + 2, HAND_BOX_Y + 1);
	setColors(WHITE, BLACK);
	printHandTotal(user);


	// Print Right-hand box
	printBox(RIGHT_BOX_X, SCREEN_MARGIN, RIGHT_BOX_W, RIGHT_BOX_H, BLUE);

	// Display the log
	printLog();

	// Print Controls label
	printBox(RIGHT_BOX_X, RIGHT_BOX_Y, RIGHT_BOX_W, 3, BLUE);
	setCursor(RIGHT_BOX_X + (RIGHT_BOX_W / 2) - 4, RIGHT_BOX_Y + 1);
	setColors(RED, WHITE);
	printf("Controls");

	// Print controls
	printBox(CONTROLS_BOX_X, CONTROLS_BOX_Y, CONTROLS_BOX_W, CONTROLS_BOX_H, BLUE);
	setColors(RED, WHITE);
	setCursor(CONTROLS_BOX_X + 2, CONTROLS_BOX_Y + 1);
	printf("h - hit");
	setCursor(CONTROLS_BOX_X + 2, CONTROLS_BOX_Y + 2);
	printf("s - stand");
	setCursor(CONTROLS_BOX_X + 2, CONTROLS_BOX_Y + 3);
	printf("esc - exit");



	// Print the CPU players
	for(int i = 0; i < numCPUs; i++)
	{
		printPlayerBox(cpuPlayers[i], i);
	}

	printHand(HAND_BOX_X + 2, HAND_BOX_Y + 4, user);

	printHand(HAND_BOX_X + 2, 7, dealer);

	fflush(stdout);
}

void printHand(int x, int y, player* p)
{
	int seperation = CARD_W + 2;

	if(p->handSize > 8) {
		seperation = 3;
	}

	setCursor(x, y);

	for(int i = 0; i < p->handSize; i++)
	{
		if(p->hand[i]->flipped) {
			printFlippedCard(x, y);
		}

		else {
			printCard(p->hand[i]->suit, p->hand[i]->rank);
		}

		moveCursor(seperation, 0);
		x += seperation;
	}
}

void fillArea(int x, int y, int w, int h, int color)
{
	setCursor(x, y);
	setColors(color, color);
	for(int i = 0; i < h; i++)
	{
		for(int j = 0; j < w; j++)
		{
			printf(" ");
		}
		moveCursor(-w, 1);
	}

	setCursor(x, y);
}

void speakOneAtATime(int x, int y, char* speech)
{
	int len = strlen(speech);

	for(int i = 1; i <= len; i++)
	{
		printSpeechBubble(x, y, speech, i);
		fflush(stdout);
		usleep(200000);
	}
}

void printSpeechBubble(int bubbleX, int bubbleY, char* speech, int lim)
{
	// Clear a previously printed speech bubble if null
	if(!speech)
	{
		//fillArea(bubbleX, bubbleY, BUBBLE_W, BUBBLE_H + 3, GREEN);
		return;
	}

	// Print the main area
	fillArea(bubbleX, bubbleY, BUBBLE_W, BUBBLE_H, WHITE);

	// Erase the corners
	fillArea(bubbleX, bubbleY, 1, 1, GREEN);
	fillArea(bubbleX + BUBBLE_W - 1, bubbleY, 1, 1, GREEN);
	fillArea(bubbleX, bubbleY + BUBBLE_H - 1, 1, 1, GREEN);
	fillArea(bubbleX + BUBBLE_W - 1, bubbleY + BUBBLE_H - 1, 1, 1, GREEN);

	// Print the tail
	fillArea(bubbleX + BUBBLE_W - 7, bubbleY + BUBBLE_H, 3, 1, WHITE);
	fillArea(bubbleX + BUBBLE_W - 7, bubbleY + BUBBLE_H + 1, 2, 1, WHITE);
	fillArea(bubbleX + BUBBLE_W - 7, bubbleY + BUBBLE_H + 2, 1, 1, WHITE);

	setCursor(bubbleX + 6, bubbleY + 3);
	setColors(WHITE, BLUE);
	printf("%.*s", lim, speech);
	fflush(stdout);
}

void printPlayerBox(player* p, int index)
{
	int boxX = PLAYER_AREA_X + (index * (2 + PLAYER_BOX_W));
	int boxY = PLAYER_AREA_Y;
	fillArea(boxX, boxY, PLAYER_BOX_W, PLAYER_BOX_H, WHITE);
	printBox( boxX, boxY, PLAYER_BOX_W, PLAYER_BOX_H, WHITE);
	printBox( boxX, boxY, PLAYER_BOX_W, 3, WHITE);
	setCursor(boxX + 2, boxY + 1);
	setColors(WHITE, BLACK);
	printf(p->name);


	setCursor( boxX + 2, boxY + 4);
	printf("Hand:");
	fflush(stdout);
	setCursor( boxX + 2, boxY + 5);
	for(int i = 0; i < p->handSize; i++)
	{
		printRank(p->hand[i]->rank);
		printSuit(p->hand[i]->suit);

		if( i < p->handSize - 1) {
			printf("-");
		}
	}

	setCursor( boxX + 2, boxY + 7 );

	printHandTotal(p);
}

void printTextBox(int x, int y, char* str, int bg, int fg)
{
	int w = strlen(str) + 4;
	printBox(x, y, w, 3, BLUE);
	setCursor(x + 2, y + 1);
	setColors(bg, fg);
	printf("%s", str);
	setCursor(x, y);
}

void printBox(int x, int y, int w, int h, int color)
{
	setCursor(x, y);
	setColors(color, RED);

	for(int mY = y; mY < (y+h); mY++)
	{
		for(int mX = x; mX < (x+w);  mX++)
		{
			if(mY == y || mY == (y + h - 1))
			{
				printf("-");
			}

			else if(mX == x || mX == (x + w - 1))
			{
				printf("|");
			}

			else
			{
				moveCursor(1, 0);
			}
		}
		moveCursor(-w, 1);
	}
}

void moveCursor(int x, int y)
{
	while(y > 0) {
		printf("\e[1B");
		y--;
	}

	while(y < 0) {
		printf("\e[1A");
		y++;
	}

	while(x > 0) {
		printf("\e[1C");
		x--;
	}

	while(x < 0) {
		printf("\e[1D");
		x++;
	}
}

void setCursor(int x, int y)
{
	int tmpFG = curFG, tmpBG = curBG;
	printf("\e[u");
	moveCursor(x, y);

	setColors(tmpBG, tmpFG);
}

// Clear out a space on the screen for drawing
void reserveSpace()
{
	moveCursor(-SCREEN_WIDTH, -SCREEN_HEIGHT);
	printf("\e[s");
	setColors(BLUE, BLUE);

	for(int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for(int x = 0; x < SCREEN_WIDTH; x++)
		{
			printf(" ");
		}

		printf("\n");
	}

	moveCursor(-SCREEN_WIDTH, -SCREEN_HEIGHT);
}

void setColors(int bg, int fg)
{
	setColor(BG, bg);
	setColor(FG, fg);
}

void setColor(int bg, int color)
{
	const char* outStr = 0;

	if(color == NOCHANGE) {
		return;
	}

	if(bg == BG) {
		curBG = color;
	} else {
		curFG = color;
	}

	switch(color)
	{
	case RED:
		if(bg == BG) {
			outStr = BG_RED;
		} else {
			outStr = FG_RED;
		}
		break;
	case BLUE:
		if(bg == BG) {
			outStr = BG_BLUE;
		} else {
			outStr = FG_BLUE;
		}
		break;
	case WHITE:
		if(bg == BG) {
			outStr = BG_WHITE;
		} else {
			outStr = FG_WHITE;
		}
		break;
	case BLACK:
		if(bg == BG) {
			outStr = BG_BLACK;
		} else {
			outStr = FG_BLACK;
		}
		break;
	case GREY:
		if(bg == BG) {
			outStr = BG_GREY;
		} else {
			outStr = FG_GREY;
		}
		break;
	case GREEN:
		if(bg == BG) {
			outStr = BG_GREEN;
		} else {
			outStr = FG_GREEN;
		}
		break;
	default:
		if(bg == BG) {
			outStr = BG_RESET;
		} else {
			outStr = FG_RESET;
		}
		break;
	}
	printf("%s", outStr);
}

int curFG = RESET;
int curBG = RESET;

char messages[MAX_MESSAGES][MESSAGE_LEN];
int msgStartIndex = 0;
int msgAddIndex = 0;
int numMessages = 0;
