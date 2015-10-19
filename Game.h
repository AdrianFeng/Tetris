#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Tank.h"
#include "Piece.h"
#include "UserInterface.h"
#include "randPieceType.h"
#include <string>
// [Add other #include directives as necessary.]

class Game
{
  public:
    Game(int width, int height); // specific function defination in cpp file
	~Game(){ delete stuff; };
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
	Tank getmtank()const { return m_tank; }
	Screen getmscreen()const{ return m_screen; }
	int getdigits(int num)const;
	void moveanddisplay(piece* & stuf, Tank& mtank, Screen & mscreen, char command);
	void displaynextpiece(PieceType shape);
	void setshape();
	bool checkboundary(char direction);
	bool checkrorate();
	void scorechange();
	bool checkoverlap();
	void specialexcute();
	bool fillblank(int cr, int cc,int sr,int sc);

  private:
	piece*  stuff; // its name is stuff, however it points to a piece type object that records the current piece's feature
    Tank    m_tank; // tank 
    Screen  m_screen; // screen
	PieceType currshape;// current piece  type
	PieceType nextshape;// next piece type
    int     m_level;// current game level
	int playerscore;  // current score earned by player
	int rowsleft; // the number of rows left to finish the current level
};

#endif // GAME_INCLUDED
