#ifndef PIECE_H_
#define PIECE_H_
#include "Tank.h"
#include "UserInterface.h"
struct coord
{
	int X;
	int Y;
};
class piece
{
public:
	piece(char ty);// specific function defination in cpp file
	virtual ~piece(){};// define destructor virtual to make sure derived class's destructor gets called
	void down();  
	void left() ;
	void right() ;
	void unexcute(Tank& tank);
	void excute(Tank& tank);
	void stay(Tank& tank);
	virtual void roration()=0; // pure virtual function since every piece rotates, but rotates differently
	void icoords(int i, char l, int v);
	void dcoords(int i, char l, int v);
	void orientp1() { orientation++; };
	int getorient() const { return orientation; };
	coord getcoords(int i) const{ return coords[i]; };
	char gettype() const { return type; };
	void copy();
	void back();
private:
	char type; // current piece type
	coord coords[4];// array copy the current piece's coordinates
	coord copyc[4];// temp copy array
	int orientation;// record the orientation times
};

class I_piece: public piece // derived I piece class
{
public:
	I_piece();
	~I_piece(){};
	void roration();
private:
};

class T_piece : public piece // derived T piece class
{
public:
	T_piece(): piece('T'){};
	~T_piece(){};
	void roration();
private:

};
class L_piece : public piece  // derived L piece class
{
public:
	L_piece() : piece('L'){};
	~L_piece(){};
	void roration();
private:
};
class J_piece :public piece   // derived J piece class
{
public:
	J_piece() : piece('J'){};
	~J_piece(){};
	void roration();
};
class O_piece:public piece // derived O piece class
{
public:
	O_piece() :piece('O'){};
	~O_piece(){};
	void roration(){ orientp1(); };
};
class S_piece :public piece  // derived S piece class
{
public:
	S_piece() :piece('S'){};
	~S_piece(){};
	void roration();
};
class Z_piece :public piece  // derived Z piece class
{
public:
	Z_piece() :piece('Z'){};
	~Z_piece(){};
	void roration();

};
class Crazy :public piece   // derived C piece class
{
public:
	Crazy() :piece('C'){};
	~Crazy(){};
	void roration();
};
class Vaporpiece :public piece   // derived VaporBomb class
{
public:
	Vaporpiece() :piece('V'){};
	~Vaporpiece(){};
	void roration(){};

};
class FBpiece :public piece   // derived FoamBomb class
{
public:
	FBpiece() :piece('F'){};
	~FBpiece(){};
	void roration(){};
};
#endif;  // PIECE_H_