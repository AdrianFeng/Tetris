#ifndef TANK_INCLUDED
#define TANK_INCLUDED
#include <vector>
using namespace std;
class Screen;

class Tank
{
  public:
	Tank(const int w,const int h); // specific function defination in its cpp file;
	~Tank(){};
	void cleartank();
    void display(Screen& screen, int x, int y) const;
	void setcoord(int x, int y, char symbol);
	bool checkonerow(int row) const;
	void shiftabovedown(int row);
	int checkallrow();
	int getw() const{ return twidth; }
	int geth() const { return theight; }
	char gettankchar(int r, int c) const{ return tank[r][c]; };
private:
	int twidth; // tank's inside width
	int theight; // tank's inside depth
	vector<vector<char>> tank;// using vector to create a 2-D tank
};

#endif // TANK_INCLUDED
