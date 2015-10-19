#include "Piece.h"
#include <string>
piece::piece(char ty) :type(ty), orientation(0)
{
	switch (ty) // different piece initiallize differently
	{
	case 'I':
		for (int a = 4; a < 8; a++)
		{
			coords[a - 4].X = a;
			coords[a - 4].Y = 1;
		}
		break;
	case 'T':
		coords[0].X = 5;
		coords[0].Y = 0;
		for (int b = 4; b < 7; b++)
		{
			coords[b - 3].X = b;
			coords[b - 3].Y = 1;
		}
		break;
	case 'L':
		coords[0].X = 4;
		coords[0].Y = 2;
		for (int b = 4; b < 7; b++)
		{
			coords[b - 3].X = b;
			coords[b - 3].Y = 1;
		}
		break;
	case'J':
		coords[0].X = 7;
		coords[0].Y = 2;
		for (int b = 4; b < 7; b++)
		{
			coords[b - 3].X = 11 - b;
			coords[b - 3].Y = 1;
		}
		break;
	case'O':
		coords[0].X = 4; coords[0].Y = 0;
		coords[1].X = 5; coords[1].Y = 0;
		coords[2].X = 4; coords[2].Y = 1;
		coords[3].X = 5; coords[3].Y = 1;
		break;
	case'S':
		coords[0].X = 4; coords[0].Y = 2;
		coords[1].X = 5; coords[1].Y = 2;
		coords[2].X = 5; coords[2].Y = 1;
		coords[3].X = 6; coords[3].Y = 1;
		break;
	case'Z':
		coords[0].X = 4; coords[0].Y = 1;
		coords[1].X = 5; coords[1].Y = 1;
		coords[2].X = 5; coords[2].Y = 2;
		coords[3].X = 6; coords[3].Y = 2;
		break;
	case'C':
		coords[0].X = 4; coords[0].Y = 0;
		coords[1].X = 5; coords[1].Y = 1;
		coords[2].X = 6; coords[2].Y = 1;
		coords[3].X = 7; coords[3].Y = 0;
		break;
	case 'V':
		coords[0].X = 5; coords[0].Y = 0;
		coords[1].X = 6; coords[1].Y = 0;
		coords[2].X = 5; coords[2].Y = 0;
		coords[3].X = 6; coords[3].Y = 0;
		break;
	case'F':
		for (int i = 0; i < 4; i++)
		{
			coords[i].X = 5; coords[i].Y = 1;
		}
		break;
     }
};

////////////////////////////////////////////////////////////////////
// function that increases coordinate with specific value v
//////////////////////////////////////////////////
void piece::icoords(int i, char l, int v) 
{
	switch (l)
	{
	case 'X':
		coords[i].X += v;
		break;
	case 'Y':
		coords[i].Y += v;
		break;
	}
}

////////////////////////////////////////////////////////////////////
// function that decreases coordinate with specific value v
//////////////////////////////////////////////////
void piece::dcoords(int i, char l, int v)
{
	switch (l)
	{
	case 'X':
		coords[i].X -= v;
		break;
	case'Y':
		coords[i].Y -= v;
		break;
	}
}

////////////////////////////////////////////////////////////////////
// make piece move down one step
//////////////////////////////////////////////////
void piece::down()
{
	for (int a = 0; a < 4; a++)
	{
		coords[a].Y++;
	}
}
////////////////////////////////////////////////////////////////////
// make piece move one step to the left
//////////////////////////////////////////////////
void piece::left() 
{
	if (type == 'C')
	{
		for (int a = 0; a < 4; a++)
		{
			coords[a].X++;
		}
	}
	else
	{

		for (int a = 0; a < 4; a++)
		{
			coords[a].X--;
		}
	}
}

////////////////////////////////////////////////////////////////////
// make piece move one step to the right
//////////////////////////////////////////////////
void piece::right()
{
	if (type == 'C')
	{
		for (int a = 0; a < 4; a++)
		{
			coords[a].X--;
		}
	}
	else
	{
		for (int a = 0; a < 4; a++)
		{
			coords[a].X++;
		}
	}
}

////////////////////////////////////////////////////////////////////
// function that copys current piece's corrdinates
//////////////////////////////////////////////////
void piece::copy()
{
	for (int a = 0; a < 4; a++)
	{
		copyc[a].X = coords[a].X;
		copyc[a].Y = coords[a].Y;
	}
}

////////////////////////////////////////////////////////////////////
// return the current piece's coordinates
//////////////////////////////////////////////////
void piece::back()
{
	for (int a = 0; a < 4; a++)
	{
		coords[a].X = copyc[a].X;
		coords[a].Y = copyc[a].Y;
	}
	orientation--;
}
////////////////////////////////////////////////////////////////////
// clear the copyed a piece in the tank
//////////////////////////////////////////////////
void piece::unexcute(Tank& tank)
{
	for (int a = 0; a < 4; a++)
	{
		tank.setcoord(coords[a].X, coords[a].Y, ' ');
	}

}
////////////////////////////////////////////////////////////////////
// function that copys the piece into the tank
//////////////////////////////////////////////////
void piece::excute(Tank& tank) 
{
	for (int a = 0; a < 4; a++)
	{
		tank.setcoord(coords[a].X, coords[a].Y, '#');
	}
}

////////////////////////////////////////////////////////////////////
// if piece in tank should stay, this function makes them shown as '$'
//////////////////////////////////////////////////
void piece::stay(Tank& tank)
{
	char sample='$';
	if (type=='F')
	{
		sample = ' ';
	}
	for (int a = 0; a < 4; a++)
	{
		tank.setcoord(coords[a].X, coords[a].Y, sample);
	}
}


I_piece::I_piece() : piece('I'){}

////////////////////////////////////////////////////////////////////
// specific rotation move for I piece
//////////////////////////////////////////////////
void I_piece::roration()
{
	orientp1();
	int realori = getorient() % 4;
	switch (realori)
	{
	case 1:
		icoords(0, 'X', 1); dcoords(0, 'Y', 1);
		dcoords(2, 'X', 1); icoords(2, 'Y', 1);
		dcoords(3, 'X', 2); icoords(3, 'Y', 2);
		break;
	case 2:
		dcoords(0, 'X', 1); icoords(0, 'Y', 1);
		icoords(2, 'X', 1); dcoords(2, 'Y', 1);
		icoords(3, 'X', 2); dcoords(3, 'Y', 2);
		break;
	case 3:
		icoords(0, 'X', 1); dcoords(0, 'Y', 1);
		dcoords(2, 'X', 1); icoords(2, 'Y', 1);
		dcoords(3, 'X', 2); icoords(3, 'Y', 2);
		break;
	case 0:
		dcoords(0, 'X', 1); icoords(0, 'Y', 1);
		icoords(2, 'X', 1); dcoords(2, 'Y', 1);
		icoords(3, 'X', 2); dcoords(3, 'Y', 2);
		break;
	}
}

////////////////////////////////////////////////////////////////////
// specific rotation move for T piece
//////////////////////////////////////////////////
void T_piece::roration()
{
	orientp1();
	int realori = getorient() % 4;
	switch (realori)
	{
	case 1:
		icoords(0, 'X', 1); icoords(0, 'Y', 1);
		icoords(1, 'X', 1); dcoords(1, 'Y', 1);
		dcoords(3, 'X', 1); icoords(3, 'Y', 1);
		break;
	case 2:
		dcoords(0, 'X', 1); icoords(0, 'Y', 1);
		icoords(1, 'X', 1); icoords(1, 'Y', 1);
		dcoords(3, 'X', 1); dcoords(3, 'Y', 1);
		break;
	case 3:
		dcoords(0, 'X', 1); dcoords(0, 'Y', 1);
		dcoords(1, 'X', 1); icoords(1, 'Y', 1);
		icoords(3, 'X', 1); dcoords(3, 'Y', 1);
		break;
	case 0:
		icoords(0, 'X', 1); dcoords(0, 'Y', 1);
		dcoords(1, 'X', 1); dcoords(1, 'Y', 1);
		icoords(3, 'X', 1); icoords(3, 'Y', 1);
		break;
	}
}

////////////////////////////////////////////////////////////////////
// specific rotation move for L piece
//////////////////////////////////////////////////
void L_piece::roration()  
{
	orientp1();
	int realori = getorient() % 4;
	switch (realori)
	{
	case 1:
		icoords(0, 'X', 1); dcoords(0, 'Y', 2);
		icoords(1, 'X', 2); dcoords(1, 'Y', 1);
		icoords(2, 'X', 1);
		icoords(3, 'Y', 1);
		break;
	case 2:
		icoords(0, 'X', 1); icoords(0, 'Y', 1);
		icoords(1, 'Y', 2);
		dcoords(2, 'X', 1); icoords(2, 'Y', 1);
		dcoords(3, 'X', 2); 
		break;
	case 3:
		icoords(0, 'Y', 2);
		dcoords(1, 'X', 1); icoords(1, 'Y', 1);
		icoords(3, 'X', 1); dcoords(3, 'Y', 1);
		break;
	case 0:
		dcoords(0, 'X', 2); dcoords(0, 'Y', 1);
		dcoords(1, 'X', 1); dcoords(1, 'Y', 2);
		dcoords(2, 'Y', 1);
		icoords(3, 'X', 1); 
		break;
	}
}

////////////////////////////////////////////////////////////////////
// specific rotation move for J piece
//////////////////////////////////////////////////
void J_piece::roration()  
{
	orientp1();
	int realori = getorient() % 4;
	switch (realori)
	{
	case 1:
		dcoords(0, 'X', 2); icoords(0, 'Y', 1);
		dcoords(1, 'X', 1); icoords(1, 'Y', 2);
		icoords(2, 'Y', 1);
		icoords(3, 'X', 1);
		break;
	case 2:
		dcoords(0, 'Y', 2);
		dcoords(1, 'X', 1); dcoords(1, 'Y', 1);
		icoords(3, 'X', 1); icoords(3, 'Y', 1);
		break;
	case 3:
		icoords(0, 'X', 1); dcoords(0, 'Y', 1);
		dcoords(1, 'Y', 2);
		dcoords(2, 'X', 1); dcoords(2,'Y', 1);
		dcoords(3, 'X', 2);
		break;
	case 0:
		icoords(0, 'X', 1); icoords(0, 'Y', 2);
		icoords(1, 'X', 2); icoords(1, 'Y', 1);
		icoords(2, 'X', 1);
		dcoords(3, 'Y', 1);
		break;
	}

}
////////////////////////////////////////////////////////////////////
// specific rotation move for S piece
//////////////////////////////////////////////////
void S_piece::roration()  
{
	orientp1();
	int realori = getorient() % 4;
	switch (realori)
	{
	case 1:
		icoords(0, 'X', 1); dcoords(0, 'Y', 2);
		dcoords(1, 'Y', 1);
		icoords(2, 'X', 1);
		icoords(3, 'Y', 1);
		break;
	case 2:
		icoords(0,'X',1); icoords(0, 'Y', 1);
		dcoords(2, 'X', 1); icoords(2, 'Y', 1);
		dcoords(3, 'X', 2);
		break;
	case 3:
		icoords(0, 'Y', 1);
		icoords(1, 'X', 1);
		dcoords(2, 'Y', 1);
		icoords(3, 'X', 1); dcoords(3, 'Y', 2);
		break;
	case 0:
		dcoords(0, 'X', 2); 
		dcoords(1, 'X', 1); icoords(1, 'Y', 1);
		icoords(3, 'X', 1); icoords(3, 'Y', 1);
		break;
	}

}

////////////////////////////////////////////////////////////////////
// specific rotation move for Z piece
//////////////////////////////////////////////////
void Z_piece::roration()  
{
	orientp1();
	int realori = getorient() % 4;
	switch (realori)
	{
	case 1:
		icoords(0, 'X', 2); dcoords(0, 'Y', 1);
		icoords(1, 'X', 1);
		dcoords(2, 'Y', 1);
		dcoords(3, 'X', 1);
		break;
	case 2:
		dcoords(0, 'X', 2); icoords(0, 'Y', 1);
		dcoords(1, 'X', 1);
		icoords(2, 'Y', 1);
		icoords(3, 'X', 1);
		break;
	case 3:
		icoords(0, 'X', 2); dcoords(0, 'Y', 1);
		icoords(1, 'X', 1);
		dcoords(2, 'Y', 1);
		dcoords(3, 'X', 1);
		break;
	case 0:
		dcoords(0, 'X', 2); icoords(0, 'Y', 1);
		dcoords(1, 'X', 1);
		icoords(2, 'Y', 1);
		icoords(3, 'X', 1);
		break;
	}

}

////////////////////////////////////////////////////////////////////
// specific rotation move for Crazy piece
//////////////////////////////////////////////////
void Crazy::roration() 
{
	orientp1();
	int realori = getorient() % 4;
	switch (realori)
	{
	case 1:
		icoords(0, 'X', 3);
		icoords(1, 'X', 1);
		icoords(2, 'Y', 1);
		icoords(3, 'Y', 3);
		break;
	case 2:
		icoords(0, 'Y', 3);
		icoords(1, 'Y', 1);
		dcoords(2, 'X', 1);
		dcoords(3, 'X', 3);
		break;
	case 3:
		dcoords(0, 'X', 3);
		dcoords(1, 'X', 1); 
		dcoords(2, 'Y', 1);
		dcoords(3, 'Y', 3);
		break;
	case 0:
		dcoords(0, 'Y', 3);
		dcoords(1, 'Y', 1);
		icoords(2, 'X', 1);
		icoords(3, 'X', 3);
		break;
	}
}