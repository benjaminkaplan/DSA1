#ifndef _BOARD_H
#define	_BOARD_H
#include <vector>
#include <string>
#include <iostream>

using namespace std;
class Board;
class Piece;
class Move;

class Piece{
public:
	vector<Move> getMoves(Piece p);
	Piece(int x, int y, char color, string name): x(x), y(y), color(color), name(name){};
	int x;
	int y;
	char color;
	bool alive = true;
	string name;
};

class Board{

public:
	Piece 	p1 = Piece(0,0,'r',"p1"), 
		p2 = Piece(0,2,'r',"p2"), 
		p3 = Piece(0,4,'r',"p3"), 
		p4 = Piece(0,6,'r',"p4"), 
		p5 = Piece(1,1,'r',"p5"), 
		p6 = Piece(1,3,'r',"p6"), 
		p7 = Piece(1,5,'r',"p7"), 
		p8 = Piece(1,7,'r',"p8"), 
		p9 = Piece(2,0,'r',"p9"), 
		p10 = Piece(2,2,'r',"p10"), 
		p11 = Piece(2,4,'r',"p11"), 
		p12 = Piece(2,6,'r',"p12"), 
		p13 = Piece(7,1,'w',"p13"), 
		p14 = Piece(7,3,'w',"p14"), 
		p15 = Piece(7,5,'w',"p15"), 
		p16 = Piece(7,7,'w',"p16"), 
		p17 = Piece(6,0,'w',"p17"), 
		p18 = Piece(6,2,'w',"p18"), 
		p19 = Piece(6,4,'w',"p19"), 
		p20 = Piece(6,6,'w',"p20"), 
		p21 = Piece(5,1,'w',"p21"), 
		p22 = Piece(5,3,'w',"p22"), 
		p23 = Piece(5,5,'w',"p23"), 
		p24 = Piece(5,7,'w',"p24");


	
	//Piece p1, p2, p3, p4, p5, p6 ,p7, p8, p9, p10, p11, p12, p13, p14,p15, p16;
	/*Board(): 	p1(0, 0, 'w', "p1"), 
			p2(0, 0, 'w', "p1"), 
			p3(0, 0, 'w', "p1"), 
			p4(0, 0, 'w', "p1"), 
			p5(0, 0, 'w', "p1"), 
			p6(0, 0, 'w', "p1"), 
			p7(0, 0, 'w', "p1"), 
			p8(0, 0, 'w', "p1"), 
			p9(0, 0, 'w', "p1"), 
			p10(0, 0, 'w', "p1"), 
			p11(0, 0, 'w', "p1"), 
			p12(0, 0, 'w', "p1"), 
			p13(0, 0, 'w', "p1"), 
			p14(0, 0, 'w', "p1"), 
			p15(0, 0, 'w', "p1"), 
			p16(0, 0, 'w', "p1"){};
	*/

	Board(){
		//cout<<"assigning addresses"<<endl;
		pieces.resize(8);
		for(int i = 0; i<8; i++)
			pieces[i].resize(8);
		//cout<<"address of p1 = "<<&p1<<endl;
		pieces[0][0] = &p1;
		pieces[0][2] = &p2;
		pieces[0][4] = &p3;
		pieces[0][6] = &p4;
		pieces[1][1] = &p5;
		pieces[1][3] = &p6;
		pieces[1][5] = &p7;
		pieces[1][7] = &p8;
		pieces[2][0] = &p9;
		pieces[2][2] = &p10;
		pieces[2][4] = &p11;
		pieces[2][6] = &p12;
		pieces[7][1] = &p13;
		pieces[7][3] = &p14;
		pieces[7][5] = &p15;
		pieces[7][7] = &p16;
		pieces[6][0] = &p17;
		pieces[6][2] = &p18;
		pieces[6][4] = &p19;
		pieces[6][6] = &p20;
		pieces[5][1] = &p21;
		pieces[5][3] = &p22;
		pieces[5][5] = &p23;
		pieces[5][7] = &p24;
		cout<<"done with addresses"<<endl;
		


	};
	void showBoard();
	vector< vector<Piece*> > pieces;
private:

};


class Move{
public:
	int xOld;
	int yOld;
	int xNew;
	int yNew;
};

#endif
