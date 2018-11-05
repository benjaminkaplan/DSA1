#include "board.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>

using namespace std;

void loadBoard( Board b);
int main(){
	cout<<"Hello wolrd!"<<endl;
	Piece p1 = Piece(0,0,'r', "p1");
	cout<<"piece name:"<<p1.name<<", coords: ("<<p1.x<<p1.y<<"), color: "<<p1.color<<endl; 
	Board b = Board();
	cout<<"created board"<<endl;
	//b.showBoard();
	//auto moves = b.getMoves();
	cout<<"==============================="<<endl;
	char letters[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
	/*for( int i = 0 ; i< moves.size(); i++){
		cout<<i+1<<": "<<moves[i].xOld+1<<", "<<letters[moves[i].yOld]<<" -> ";
		cout<<moves[i].xNew+1<<", "<<letters[moves[i].yNew]<<endl;

	}*/

//========================================================
	cout<<"Welcome to checkers!"<<endl;
	cout<<"Options: "<<endl;
	cout<<"1: Start a new game against the AI"<<endl;
	cout<<"2: Have the AI play itself in a new game"<<endl;
	cout<<"3: Load a board to play against the AI"<<endl;
	cout<<"4: Load a board and have AI play itself"<<endl; 
	int option;
	string entered;

	do{
		cout<<"Choose an option: ";
		cin>> entered;
	} while(!std::isdigit(entered[0]));
	option = stoi(entered);
	cout<<"entered digit: "<<option<<endl;
	do{
		cout<<"Enter time limit in seconds: ";
		cin>>entered;
	} while(!std:: isdigit(entered[0]) );
	int timeLimit = stoi(entered);
	cout<<"time entered: "<<timeLimit<<endl;
	switch(option){
		case 1: 
			break;
		case 2:
			b.loadBoard();
			break;
		case 3:
			//loadBoard(); 
			break;
		case 4:
			break;
	}
	b.playGame();
	b.showBoard();

}


void Board::loadBoard(){
	cout<<"Enter path to file containing board: ";
	string file = "board.txt";
	//cin >> file;
	ifstream infile;
	char board[8][8];
	infile.open(file);
	//cout<<"opened file"<<endl;
	char c = 0; 
	int numRed=0, numWhite = 0;
	for (int i =0 ; i <8; i++){
		for( int j =0; j<8; j++){
			//cout<<"i: "<<i<<", j: "<<j<<endl;
			infile.get(c);
			board[i][j] = c;
			if(c == 'w' || c == 'W') numWhite++;
			if(c == 'r' || c == 'R') numRed++;
		}
		infile.get(c);
	}
	infile.close();
	if(numWhite>12){
		cout<<"Too many white pieces, 12 max allows"<<endl;
		exit(EXIT_FAILURE);
	}
	if(numRed>12){
		cout<<"Too many red pieces, 12 max allows"<<endl;
		exit(EXIT_FAILURE);
	}
	for( int i = 0; i <this->myTurn->pieces.size(); i++){
		this->myTurn->pieces[i]->x = 0; this->myTurn->pieces[i]->y = 0; this->myTurn->pieces[i]->alive = false;}
	for( int i = 0; i <this->myTurn->pieces.size(); i++){
		this->opponent->pieces[i]->x = 0; this->opponent->pieces[i]->y = 0; this->opponent->pieces[i]->alive = false;}
	for( int i= 0; i<8; i++){
		for(int j = 0; j<8; j++){
			this->pieces[i][j] = NULL;
		}
	}
	
	int numMyTurn =0 , numOpponent = 0;
	for(int i= 0 ; i<8; i++){
		for(int j= 0 ; j<8 ; j++){
			cout<<board[i][j];
			if(board[i][7-j] == 'r' || board[i][7-j] == 'R'){
				this->pieces[i][7-j] = this->myTurn->pieces[numMyTurn];
				this->myTurn->pieces[numMyTurn]->alive = true;
				if(board[i][7-j] == 'R')			
					this->myTurn->pieces[numMyTurn]->isKing = true;
				numMyTurn++;
			}
			if(board[i][7-j] == 'w' || board[i][7-j] == 'W' ){
				this->pieces[i][7-j] = this->opponent->pieces[numOpponent];
				this->opponent->pieces[numOpponent]->alive = true;
				if(board[i][7-j] == 'W')			
					this->opponent->pieces[numOpponent]->isKing = true;
				numOpponent++;
			}
		}
		cout<<endl;
	}
} // End of loadBoard(Board b)

void Board::playGame(){
	this->showBoard();
	auto moves = this->getMoves('r');
	char letters[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
	while(moves.size() != 0){
		cout<<"available moves"<<endl;
		for(int i=0; i<moves.size(); i++)
			cout<<moves[i].xOld+1<<letters[moves[i].yOld]<<"->"<<moves[i].xNew+1<<letters[moves[i].yNew]<<endl;
		this->executeMove(moves[0]);
		break;
	}	
}
