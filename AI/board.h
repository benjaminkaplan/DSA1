#ifndef _BOARD_H
#define	_BOARD_H
#include <vector>
#include <string>
#include <iostream>

using namespace std;
class Board;
class Piece;
class Move;
class Player;

class Piece{
public:
	vector<Move> getMoves(Piece p);
	Piece(int x, int y, char color, string name): x(x), y(y), color(color), name(name){};
	int x;
	int y;
	char color;
	bool alive = true;
	bool isKing = false;
	string name;
};

class Player{
public:
	char color;
	vector<Piece*> pieces;
	vector<Move> getMoves();
	Player(Piece* p1, Piece* p2,Piece* p3,Piece* p4,Piece* p5,Piece* p6,
		Piece* p7,Piece* p8,Piece* p9,Piece* p10,Piece* p11,Piece* p12,char color): color(color){
		this->pieces.resize(12);
		this->pieces[0] = p1;
		this->pieces[1] = p2;
		this->pieces[2] = p3;
		this->pieces[3] = p4;
		this->pieces[4] = p5;
		this->pieces[5] = p6;
		this->pieces[6] = p7;
		this->pieces[7] = p8;
		this->pieces[8] = p9;
		this->pieces[9] = p10;
		this->pieces[10] = p11;
		this->pieces[11] = p12;
		

	}
};

class Board{

public:
	
	Piece	p1 = Piece(0,0,'r',"p1"),  // X is row, Y is col
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
	vector<Move> getMoves(char player);
	Player* player2;
	Player* player1;
	Player* myTurn;
	Player* opponent;
	Board(){
		pieces.resize(8);
		for(int i = 0; i<8; i++)
			pieces[i].resize(8);
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
		player1 = new Player(&p1,&p2,&p3,&p4,&p5,&p6,
					&p7,&p8,&p9,&p10,&p11,&p12, 'r');
		player2 = new Player(&p13, &p14, &p15, &p16, &p17, &p18, 
					&p19, &p20, &p21, &p22, &p23, &p24,'w');
		myTurn = player1;
		opponent = player2;	
		cout<<"done with addresses"<<endl;
		cout<<"myturn: "<<myTurn<<", player1: "<<player1<<endl;
	};
	void showBoard();
	void loadBoard();
	void playGame();
	void executeMove(Move move);
	vector< vector<Piece*> > pieces;

private:

}; // End of Board class


class Move{
public:
	int xOld;
	int yOld;
	int xNew;
	int yNew;
	int xCap = 0;
	int yCap = 0;
	bool capMove = false;
	Move(int x1, int y1, int x2, int y2): xOld(x1), yOld(y1), xNew(x2), yNew(y2){this->capMove = false;}
	Move(int x1, int y1, int x2, int y2, int x3, int y3): xOld(x1), yOld(y1), xNew(x2), yNew(y2), xCap(x3), yCap(y3){this->capMove = true;}
};



#endif
