#include "Tank.h"
#include "UserInterface.h"


////////////////////////////////////////////////////////////////////
// function that display the tank on the screen
//////////////////////////////////////////////////
void Tank::display(Screen& screen, int x, int y) const
{
	//screen.gotoXY(x, y);
	int X = x;
	int Y = y;
	for (int a = 0; a <= theight; a++)
	{
		screen.gotoXY(X, Y);
		for (int b = 0; b <= twidth + 1; b++)
		{
			screen.printChar(tank[a][b]);
		}
		Y++;
	}
}

////////////////////////////////////////////////////////////////////
// tank constructor
//////////////////////////////////////////////////

Tank::Tank(const int w,const int h):twidth(w),theight(h)
{
	tank.resize(h+1); // initiallize the tank
	for (int a = 0; a < (h + 1); a++)
	{
		tank[a].resize(w + 2);
		tank[a][0] = '@';
		for (int c = 1; c <= w; c++)
		{
			tank[a][c] = ' ';
		}
		tank[a][w + 1] = '@';
		if (a == h)
		{
			int count = 1;
			while (count < (w + 1))
			{
				tank[a][count] = '@';
				count++;
			}
		}
	}
}


////////////////////////////////////////////////////////////////////
// function that sets a specific coordinates in the tank to a symbol
//////////////////////////////////////////////////
void Tank::setcoord(int x, int y, char symbol) 
{
	tank[y][x] = symbol;
}

////////////////////////////////////////////////////////////////////
// function that checks whether one row is full or not 
//////////////////////////////////////////////////
bool Tank::checkonerow(int  row) const 
{
	for (int p = 1; p <= twidth; p++)
	{
		if (tank[row][p] != '$'&&tank[row][p] != '*')
		{
			return false;
		}
	}
	return true;
}

////////////////////////////////////////////////////////////////////
// function that shifts all rows above down once
//////////////////////////////////////////////////

void Tank::shiftabovedown(int row) 
{
	if (row!=0)
	{
		for (int i = row; i >= 1; i--)
		{
			for (int q = 1; q <= twidth; q++)
			{
				tank[i][q] = tank[i - 1][q];
			}
		}

	}
	for (int q = 1; q <= twidth; q++)
	{
		 tank[0][q]=' ';
	}
}
////////////////////////////////////////////////////////////////////
// check all rows in tank and clear the rows that is full and return the nnumber of rows that are cleared
//////////////////////////////////////////////////
int Tank::checkallrow() 
{
	int numofrows = 0;
	for (int a = 0; a < theight; a++)
	{
		if (checkonerow(a))
		{
			shiftabovedown(a);
			numofrows++;
		}
	}
	return numofrows;
}

////////////////////////////////////////////////////////////////////
// make the tank empty
//////////////////////////////////////////////////
void Tank::cleartank() 
{
	for (int p = 0; p < theight; p++)
	{
		for (int q = 1; q <= 10; q++)
		{
			tank[p][q] = ' ';
		}
	}
}