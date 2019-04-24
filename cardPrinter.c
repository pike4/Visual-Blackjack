#include "output.h"
#include "cardPrinter.h"

int checkPattern(int rank, int x, int y)
{
	if(rank > 10 || rank < 2) {
		return 0;
	}

	for(int i = 0; i < rank; i++)
	{
		if(x == COORDS[rank-2][i][0] && y == COORDS[rank-2][i][1]) {
			return 1;
		}
	}

	return 0;
}

void printFlippedCard(int x, int y)
{
	fillArea(x, y, CARD_W, CARD_H, WHITE);
	fillArea(x + 1, y + 1, CARD_W - 2, CARD_H - 2, RED);
	fillArea(x + CARD_W / 2 - 1, y + 2, 2, 2, WHITE);
	fillArea(x + CARD_W / 2 - 1, y + CARD_H - 4, 2, 2, WHITE);

	setCursor(x, y);
}

void printCard(int suit, int rank)
{
	int textColor = 0;
	const char* suitStr = 0;

	switch(suit)
	{
	case SPADES:
		textColor = BLACK;
		suitStr	= SPADE;
		break;
	case CLUBS:
		textColor = BLACK;
		suitStr = CLUB;
		break;
	case HEARTS:
		textColor = RED;
		suitStr = HEART;
		break;
	case DIAMONDS:
		textColor = RED;
		suitStr = DIAMOND;
		break;
	}

	setColors(WHITE, textColor);
	for(int y = 0; y < CARD_H; y++)
	{
		for(int x = 0; x < CARD_W; x++)
		{
			// Print the card's rank in the 2 corners
			if( (x == L_MARGIN && y == T_MARGIN) || (x == R_MARGIN && y == B_MARGIN))
			{
				printRank(rank);
			}

			else if( rank == 10 && ((x == L_MARGIN+1 && y == T_MARGIN) || (x == R_MARGIN+1 && y == B_MARGIN) ))
			{}

			// Print the suit above or below the rank
			else if( (x == L_MARGIN && y == (T_MARGIN + 1)) || (x == R_MARGIN && y == (B_MARGIN - 1)))
			{
				printf("%s", suitStr);
			}

			// Print the pattern in the middle
			else if(checkPattern(rank, x, y)) {
				printf("%s", suitStr);
			}

			// Print a grey border around the card
			else if( x == 0 || x == CARD_W-1 || y == 0 || y == CARD_H - 1 ) {
				setColors(GREY, GREY);
				printf(" ");
				setColors(WHITE, textColor);
			}

			// Print a white card interior
			else {
				printf(" ");
			}
		}

		moveCursor(- (CARD_W), 1);
	}

	// Reset cursor to original status
	moveCursor(0, -CARD_H);
}

void printSuit(int suit)
{
	int tmp = curFG;

	switch(suit)
	{
	case CLUBS:
		setColors(NOCHANGE, BLACK);
		printf(CLUB);
		break;
	case DIAMONDS:
		setColors(NOCHANGE, RED);
		printf(DIAMOND);
		break;
	case SPADES:
		setColors(NOCHANGE, BLACK);
		printf(SPADE);
		break;
	default:
		setColors(NOCHANGE, RED);
		printf(HEART);
		break;
	}
	setColors(NOCHANGE, tmp);
}

// Print the properly formatted card rank
void printRank(int rank)
{
	if(rank >= CARD_2 && rank <= CARD_10)
	{
		printf("%d", rank);
	}

	else
	{
		switch(rank)
		{
		case CARD_ACE:
			printf("A");
			break;
		case CARD_KING:
			printf("K");
			break;
		case CARD_QUEEN:
			printf("Q");
			break;
		case CARD_JACK:
			printf("J");
			break;
		default:
			printf("?");
			break;
		}
	}
}

int COORDS[10][10][2] =
{
	// 2
	{
		{ CARD_MID_X, CARD_MID_Y - 2},
		{ CARD_MID_X, CARD_MID_Y + 2}
	},

	// 3
	{
		{CARD_MID_X, CARD_MID_Y - 2},
		{CARD_MID_X, CARD_MID_Y},
		{CARD_MID_X, CARD_MID_Y + 2}
	},

	// 4
	{
		{CARD_MID_X - 2, CARD_MID_Y - 2},
		{CARD_MID_X - 2, CARD_MID_Y + 2},
		{CARD_MID_X + 2, CARD_MID_Y - 2},
		{CARD_MID_X + 2, CARD_MID_Y + 2}
	},

	// 5
	{
		{CARD_MID_X - 2, CARD_MID_Y - 2},
		{CARD_MID_X - 2, CARD_MID_Y + 2},
		{CARD_MID_X + 2, CARD_MID_Y - 2},
		{CARD_MID_X + 2, CARD_MID_Y + 2},
		{CARD_MID_X, CARD_MID_Y}
	},

	// 6
	{
		{CARD_MID_X - 2, CARD_MID_Y - 2},
		{CARD_MID_X - 2, CARD_MID_Y + 2},
		{CARD_MID_X + 2, CARD_MID_Y - 2},
		{CARD_MID_X + 2, CARD_MID_Y + 2},
		{CARD_MID_X + 2, CARD_MID_Y },
		{CARD_MID_X - 2, CARD_MID_Y }
	},

	// 7
	{
		{CARD_MID_X - 2, CARD_MID_Y - 2},
		{CARD_MID_X - 2, CARD_MID_Y + 2},
		{CARD_MID_X + 2, CARD_MID_Y - 2},
		{CARD_MID_X + 2, CARD_MID_Y + 2},
		{CARD_MID_X + 2, CARD_MID_Y },
		{CARD_MID_X - 2, CARD_MID_Y },
		{CARD_MID_X, CARD_MID_Y -1 }
	},

	// 8
	{
		{CARD_MID_X - 2, CARD_MID_Y - 2},
		{CARD_MID_X + 2, CARD_MID_Y - 2},
		{CARD_MID_X - 2, CARD_MID_Y - 1},
		{CARD_MID_X + 2, CARD_MID_Y - 1},
		{CARD_MID_X - 2, CARD_MID_Y + 2},
		{CARD_MID_X + 2, CARD_MID_Y + 1},
		{CARD_MID_X - 2, CARD_MID_Y + 1},
		{CARD_MID_X + 2, CARD_MID_Y + 2}
	},

	// 9
	{
		{CARD_MID_X - 2, CARD_MID_Y - 2},
		{CARD_MID_X + 2, CARD_MID_Y - 2},
		{CARD_MID_X - 2, CARD_MID_Y },
		{CARD_MID_X + 2, CARD_MID_Y },
		{CARD_MID_X, CARD_MID_Y - 1},
		{CARD_MID_X - 2, CARD_MID_Y + 2},
		{CARD_MID_X + 2, CARD_MID_Y + 1},
		{CARD_MID_X - 2, CARD_MID_Y + 1},
		{CARD_MID_X + 2, CARD_MID_Y + 2}
	},

	// 10
	{
			{CARD_MID_X - 2, CARD_MID_Y - 3},
			{CARD_MID_X + 2, CARD_MID_Y - 3},
			{CARD_MID_X - 2, CARD_MID_Y - 1},
			{CARD_MID_X + 2, CARD_MID_Y - 1},
			{CARD_MID_X, CARD_MID_Y - 2},
			{CARD_MID_X - 2, CARD_MID_Y + 2},
			{CARD_MID_X + 2, CARD_MID_Y },
			{CARD_MID_X - 2, CARD_MID_Y },
			{CARD_MID_X + 2, CARD_MID_Y + 2},
			{CARD_MID_X, CARD_MID_Y + 1}
	}
};
