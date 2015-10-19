#include "Game.h"
#include <cmath>
#include "Tank.h"
#include <string>
#include <iostream>
#include <algorithm> 
const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int TANK_X = 0;
const int TANK_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

Game::Game(int width, int height)
 : m_screen(SCREEN_WIDTH, SCREEN_HEIGHT),m_tank(width,height),stuff(nullptr), m_level(1)
{
	playerscore = 0;
	rowsleft = 5 * m_level;
	nextshape = randPieceType();
	currshape = nextshape;
}

void Game::play()
{
    m_tank.display(m_screen, TANK_X, TANK_Y);
    displayStatus(); //  score, rows left, level
	displayPrompt("Press the Enter key to begin playing Imitris!");
    waitForEnter();  // [in UserInterface.h]

    for(;;)
    {
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_level++;
		// clear the tank and create a new random piece and display the new status
		nextshape = randPieceType();
		currshape = nextshape;
		rowsleft = 5 * m_level;
		m_tank.cleartank();
		displayStatus();
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

///////////////////////////////////////////////////////////
// function that shows the current information about game status
///////////////////////////////////////////////////////////
void Game::displayStatus() 
{
	m_screen.gotoXY(SCORE_X, SCORE_Y);
	m_screen.printString("Score:               ");
	int digit1 = 7-getdigits(playerscore);
	m_screen.gotoXY(SCORE_X+11+digit1, SCORE_Y);
	m_screen.printString(to_string(playerscore));
	m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
	m_screen.printString("Rows left:           ");
	int digit2 = 7 - getdigits(rowsleft);
	m_screen.gotoXY(ROWS_LEFT_X+11+digit2, ROWS_LEFT_Y);
	m_screen.printString(to_string(rowsleft));
	m_screen.gotoXY(LEVEL_X, LEVEL_Y);
	m_screen.printString("Level:               ");
	int digit3 = 7 - getdigits(m_level);
	m_screen.gotoXY(LEVEL_X+11+digit3, LEVEL_Y);
	m_screen.printString(to_string(m_level));
}

///////////////////////////////////////////////////////////
// function that makes piece move 
///////////////////////////////////////////////////////////
void Game::moveanddisplay(piece* & stuf, Tank& mtank, Screen & mscreen, char command)
{
	stuf->unexcute(mtank);// clear the piece copyed in the tank
	// piece moves or rotates as the command says
	if (command == 'd')
	{
		stuf->down();
	}
	else if (command == 'u')
	{
		stuf->roration();
	}
	else if (command == 'l')
	{
		stuf->left();
	}
	else if (command == 'r')
	{
		stuf->right();
	}
	else{}
	stuf->excute(mtank);// copy the piece into the tank again
	mtank.display(mscreen, TANK_X, TANK_Y); // show the tank with new copyed piece that have moved a step or rotated.
}

///////////////////////////////////////////////////////////
// main function of playing a turn
///////////////////////////////////////////////////////////
bool Game::playOneLevel() 
{
	for (;;)
	{
		setshape(); // set stuff to be the current piece type object
		nextshape = randPieceType(); // randomly create a new piece type.
		displaynextpiece(nextshape);
		if (!checkoverlap())// check to see whether the tank is full or not 
		{
			stuff->excute(m_tank);
			m_tank.display(m_screen, TANK_X, TANK_Y);
			return false;
			break;
		}
		moveanddisplay(stuff, m_tank, m_screen, 's');
		for (;;)
		{
			int interval = max(1000 - (100 * (m_level - 1)), 100);// 
			int endTime = getMsecSinceStart() + interval;
			while (getMsecSinceStart() < endTime)// give player some specific time to make a change to the current piece
			{
				char ch;
				if (getCharIfAny(ch))
				{
					if (ch == ARROW_DOWN)
					{
						if (checkboundary('d'))
						{
							moveanddisplay(stuff, m_tank, m_screen, 'd');
							endTime = getMsecSinceStart() + interval;
						}
						else
						{
							break;
						}
					}
					else if (ch == ARROW_UP)
					{
						if (checkrorate())
						{
							moveanddisplay(stuff, m_tank, m_screen, 'u');
						}
					}
					else if (ch == ARROW_LEFT)
					{
						if (stuff->gettype() == 'C')
						{
							if (checkboundary('r'))
							{
								moveanddisplay(stuff, m_tank, m_screen, 'l');
							}
						}
						else
						{
							if (checkboundary('l'))
							{
								moveanddisplay(stuff, m_tank, m_screen, 'l');
							}
						}
					}
					else if (ch == ARROW_RIGHT)
					{
						if (stuff->gettype() == 'C')
						{
							if (checkboundary('l'))
							{
								moveanddisplay(stuff, m_tank, m_screen, 'r');
							}
						}
						else
						{
							if (checkboundary('r'))
							{
								moveanddisplay(stuff, m_tank, m_screen, 'r');
							}
						}
					}
					else if (ch == 'q'||ch=='Q')
					{
						return false;
					}
					else if (ch == ' ')
					{
						for (;;)
						{
							if (!checkboundary('d'))
							{
								break;
							}
							stuff->unexcute(m_tank);
							stuff->down(); stuff->excute(m_tank);
						}
						break;
					}
				}
			};
			if (checkboundary('d'))
			{
				moveanddisplay(stuff, m_tank, m_screen, 'd');
			}
			else // piece rests and rows shift and score changes
			{
				stuff->stay(m_tank);
				if (stuff->gettype() == 'V' || stuff->gettype() == 'F')
				{
					specialexcute();
				}
				scorechange();
				m_tank.display(m_screen, TANK_X, TANK_Y);
				if (rowsleft == 0)
				{
					delete stuff;// free the memory
					stuff = nullptr;
					return true;
					break;
				}
				break;
			}

		}
		currshape = nextshape;
		delete stuff;// free the memory 
		stuff = nullptr;
	}
}

///////////////////////////////////////////////////////////
// function to show the next piece on the screen
///////////////////////////////////////////////////////////
void Game::displaynextpiece(PieceType shape) 
{
	m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
	m_screen.printString("Next piece:");
	for (int a = 0; a < 4; a++)
	{
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y+a);
		m_screen.printString("     ");
	}
	
	switch (shape)
	{
	case PIECE_I:
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y+1);
		m_screen.printString("####");
		break;
	case PIECE_T:
		m_screen.gotoXY(NEXT_PIECE_X+1, NEXT_PIECE_Y);
		m_screen.printChar('#');
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
		m_screen.printString("###");
		break;
	case PIECE_L:
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
		m_screen.printString("###");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 2);
		m_screen.printString("#");
		break;
	case PIECE_J:
		m_screen.gotoXY(NEXT_PIECE_X+1, NEXT_PIECE_Y + 1);
		m_screen.printString("###");
		m_screen.gotoXY(NEXT_PIECE_X + 3, NEXT_PIECE_Y + 2);
		m_screen.printChar('#');
		break;
	case PIECE_O:
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y );
		m_screen.printString("##");
		m_screen.gotoXY(NEXT_PIECE_X , NEXT_PIECE_Y +1);
		m_screen.printString("##");
		break;
	case PIECE_S:
		m_screen.gotoXY(NEXT_PIECE_X+1, NEXT_PIECE_Y+1);
		m_screen.printString("##");
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 2);
		m_screen.printString("##");
		break;
	case PIECE_Z:
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
		m_screen.printString("##");
		m_screen.gotoXY(NEXT_PIECE_X+1, NEXT_PIECE_Y + 2);
		m_screen.printString("##");
		break;
	case  PIECE_VAPOR:
		m_screen.gotoXY(NEXT_PIECE_X+1, NEXT_PIECE_Y );
		m_screen.printString("##");
		break;
	case PIECE_FOAM:
		m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 1);
		m_screen.printChar('#');
		break;
	case PIECE_CRAZY:
		m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y);
		m_screen.printString("#  #");
		m_screen.gotoXY(NEXT_PIECE_X+1, NEXT_PIECE_Y+1);
		m_screen.printString("##");
		break;
	}


}

///////////////////////////////////////////////////////////
// get number's digits
///////////////////////////////////////////////////////////
int Game::getdigits(int num)const 
{
	int numofdig = 1;
	while (num /= 10)
	{
		numofdig++;
	}
	return numofdig;
}
///////////////////////////////////////////////////////////
//function set stuff to point to a new piece type object
///////////////////////////////////////////////////////////
void Game::setshape()
{
	switch (currshape)
	{
	case PIECE_I:
		stuff = new I_piece();
		break;
	case PIECE_L:
		stuff = new L_piece();
		break;
	case PIECE_J:
		stuff = new J_piece();
		break;
	case PIECE_T:
		stuff = new T_piece();
		break;
	case PIECE_O:
		stuff = new O_piece();
		break;
	case PIECE_S:
		stuff = new S_piece();
		break;
	case  PIECE_Z:
		stuff = new Z_piece();
		break;
	case PIECE_VAPOR:
		stuff = new Vaporpiece();
		break;
	case PIECE_FOAM:
		stuff = new FBpiece();
		break;
	case PIECE_CRAZY:
		stuff = new Crazy();
		break;
	}
}


///////////////////////////////////////////////////////////
// check whether piece is out of boundary
///////////////////////////////////////////////////////////
bool Game::checkboundary(char direction)
{
	for (int a = 0; a < 4; a++)
	{
		int row = stuff->getcoords(a).Y;
		int col = stuff->getcoords(a).X;
		char left = m_tank.gettankchar(row, col - 1);
		char right = m_tank.gettankchar(row, col + 1);
		char down = m_tank.gettankchar(row + 1, col);
		switch (direction)
		{
		case 'l':
			if (left != ' '&&left != '#')
				return false;
			break;
		case 'r':
			if (right != ' '&&right != '#')
				return false;
			break;
		case 'd':
			if (down != ' '&& down != '#')
				return false;
			break;
		case 'u':
			if ((row - 1) < 0)
				return false;
			else
			{
				char top = m_tank.gettankchar(row - 1, col);
				if (top != ' '&&top != '#')
					return false;
			}
			break;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////
// check to see if the piece can rotate or not. true for being able to rotate
///////////////////////////////////////////////////////////
bool Game::checkrorate() 
{
	stuff->copy();
	stuff->roration();
	for (int a = 0; a < 4; a++)
	{
		int row = stuff->getcoords(a).Y;
		int col = stuff->getcoords(a).X;
		char curr = m_tank.gettankchar(row, col );
		if (curr != ' '&&curr != '#')
		{
			stuff->back();
			return false;
			break;
		}
	}
	stuff->back();
	return true;
}

///////////////////////////////////////////////////////////
// function that clear full row and change the status of the game
///////////////////////////////////////////////////////////
void Game::scorechange()
{
	int num = m_tank.checkallrow();
	rowsleft = rowsleft - num;
	if (rowsleft < 0)
	{
		rowsleft = 0;
	}
	int intger = num / 5;
	int mod = (num % 5)-1;
	if (mod < 0)
	{
		playerscore = playerscore + 1600 * intger;
	}
	else
	{
		playerscore = playerscore + 1600 * intger + 100 * pow(2, mod);
	}
	displayStatus();
}


////////////////////////////////////////////////////////////////////
// function that will do VaporBomb and FoamBomb's special actions
//////////////////////////////////////////////////
void Game::specialexcute()
{
	if (stuff->gettype() == 'V')
	{
		int curry = stuff->getcoords(0).Y;
		int currx = stuff->getcoords(0).X;
		int upl = stuff->getcoords(0).Y;
		int dowl = m_tank.geth() - stuff->getcoords(0).Y - 1;
		if (upl >2)
		{
			upl = 2;
		}
		if (dowl > 2)
		{
			dowl = 2;
		}
		for (int a = curry - upl; a <= (curry + dowl); a++)
		{
			for (int b = currx; b < (currx + 2); b++)
			{
				m_tank.setcoord(b, a, ' ');
			}
		}
	}
	else if (stuff->gettype() == 'F')
	{
		int r = stuff->getcoords(0).Y;
		int c = stuff->getcoords(0).X;
		bool boolen = fillblank(r,c,r,c);
	}
}

////////////////////////////////////////////////////////////////////
// function that fills the blanks near the FoamBomb with "*" recursively
//////////////////////////////////////////////////
bool Game::fillblank(int cr, int cc,int sr,int sc) 
{
	char symbol = m_tank.gettankchar(cr, cc);
	if (cr == sr + 3 || cr == sr - 3 || cc == sc + 3 || cc == sc -3||symbol!=' ')
	{
		return true;
	}
	else
	{
		m_tank.setcoord(cc, cr, '*');
		if (fillblank(cr - 1, cc, sr, sc) && fillblank(cr + 1, cc, sr, sc) && fillblank(cr, cc + 1, sr, sc) && fillblank(cr, cc - 1, sr, sc))
		{
			return true;
		}
	}
	return false;
	
}


////////////////////////////////////////////////////////////////////
// check to see whether the piece in its current position overlaps with existing pieces or not. true for not overlap 
//////////////////////////////////////////////////
bool Game::checkoverlap() 
{
	for (int a = 0; a < 4; a++)
	{
		int row = stuff->getcoords(a).Y;
		int col = stuff->getcoords(a).X;
		char curr = m_tank.gettankchar(row, col);
		if (curr !=' ')
		{
			return false;
			break;
		}
	}
	return true;
}