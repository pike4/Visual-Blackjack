/*
 * output.h
 *
 *  Created on: Mar 27, 2019
 *      Author: root
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "player.h"
#include "defines.h"

#include <stdio.h>

extern const char* CLUB;
extern const char* SPADE;
extern const char* HEART;
extern const char* DIAMOND;

extern const char* BG_RESET;
extern const char* BG_RED;
extern const char* BG_BLUE;
extern const char* BG_BLACK;
extern const char* BG_WHITE;
extern const char* BG_GREY;
extern const char* BG_GREEN;

extern const char* FG_RESET;
extern const char* FG_RED;
extern const char* FG_BLUE;
extern const char* FG_BLACK;
extern const char* FG_WHITE;
extern const char* FG_GREY;
extern const char* FG_GREEN;

extern int curFG;
extern int curBG;



#define FG		0
#define BG		1

#define NOCHANGE	-1
#define RESET	0
#define BLUE	1
#define BLACK	2
#define WHITE	3
#define RED		4
#define GREY	5
#define GREEN	6

extern int numMessages;
extern int msgStartIndex;
extern int msgAddIndex;
extern int numMessages;
extern char messages[MAX_MESSAGES][MESSAGE_LEN];

void setColors(int bg, int fg);
void setColor(int bg, int color);
void printCard(int suit, int rank);
void reserveSpace();

void clearScreen();
void refresh();
void cursorExit();

void printLog();
void say(char* str);

void moveCursor(int x, int y);
void setCursor(int x, int y);
void printScreen();
void printHand(int x, int y, player* p);
void printBox(int x, int y, int w, int h, int color);
void printTextBox(int x, int y, char* str, int bg, int fg);
void printPlayerBox(player* p, int index);
void printHandTotal(player* p);

void printFlippedCard(int x, int y);

void fillArea(int x, int y, int w, int h, int color);

void printSpeechBubble(int bubbleX, int bubbleY, char* speech, int lim);
void speakOneAtATime(int x, int y, char* speech);

#endif /* OUTPUT_H_ */
