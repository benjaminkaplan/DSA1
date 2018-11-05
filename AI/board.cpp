#include <iostream>
#include <string>
#include <vector>

#include "board.h"
using namespace std;

void Board::showBoard(){
	//cout<<"in showboard"<<endl;
	cout<<"  A   B   C   D   E   F   G   H  "<<endl;
	cout<<" ___ ___ ___ ___ ___ ___ ___ ___ "<<endl;
	//cout<<"|";
	
	for(int r = 0 ; r<8; r++){
		for(int c = 0; c<8 ;c++){
			cout<<'|';
			if(this->pieces[r][c]){
				if( this->pieces[r][c]->color == 'r'){
					if(this->pieces[r][c]->isKing) cout<<"{R}";
					else cout<<" r ";
				}
			
				if( this->pieces[r][c]->color == 'w'){
					if(this->pieces[r][c]->isKing) cout<<"{W}";
					else cout<<" w ";
				}
			}
			else cout<<"   ";
		}cout<<'|'<<" "<<r+1<<endl;
		cout<<"|___|___|___|___|___|___|___|___|"<<endl;		
		
	}
	cout<<endl;
	for(int i = 0; i< 8; i++){
		for(int j= 0 ; j<8; j++){
			if(this->pieces[i][j] && this->pieces[i][j]->color == 'r') cout<<"r";
			else if(this->pieces[i][j] && this->pieces[i][j]->color == 'w') cout<<"w";
			else cout<<"0";
		} cout<<endl;
	}
};

vector<Move> Player::getMoves(){
	cout<< "in the get move functon"<<endl;
	vector<Move> moves;
	for( int i = 0; i < this->pieces.size(); i++){
		if(this->pieces[i]->x+1 < 8 && this->pieces[i]->y+1 < 8){
			Move m = Move(this->pieces[i]->x, this->pieces[i]->y, this->pieces[i]->x+1, this->pieces[i]->y+1);
			moves.push_back(m);

		}
	}
	return moves;
}

vector<Move> Board::getMoves(char player){ // red is 'r', white is 'w'
	char other = 'w'; if(player == 'w') other = 'r';
	//cout<<"in the get moves"<<endl;
	vector<Move> moves;
	vector<Move> capMoves;
	//cout<<"made the moves vector"<<endl;
	//cout<<"player 1 has: "<<this->myTurn->pieces.size()<<endl;
	bool capMove = false;
	char color;
	int offset = 0;
	if( player == 'w') offset =-1; if( player == 'r') offset = 1;
	for( int i = 0; i <8; i++){
	for( int j= 0 ; j<8; j++){
		//cout<<"in the for loop"<<endl;
		//cout<<this->myTurn->pieces[i]->x+1<<endl;

		if(this->pieces[i][j] && this->pieces[i][j]->color == player && !this->pieces[i][j]->isKing){
			//cout<<"found pieces"<<endl;
			if(!this->pieces[i+offset*1][j+1] && i+offset*1<8 && j+1<8){
				//cout<<"adding move: "<<i<<j<<"->"<<i+offset*1<<j+1<<endl;
				moves.push_back(Move(i, j, i+1*offset, j+1));
			}
			if(!this->pieces[i+offset*1][j-1] && i+offset*1<8 && j-1>=0){
				//cout<<"adding move: "<<i<<j<<"->"<<i+offset*1<<j-1<<endl;
				moves.push_back(Move(i, j, i+1*offset, j-1));
			}
		//}
		//if(this->pieces[i][j] && this->pieces[i][j]->color == player && !this->pieces[i][j]->isKing){
			//cout<<"found pieces"<<endl;
			if(!this->pieces[i+offset*2][j+2] && i+offset*2<8 && j+2<8
				&& this->pieces[i+offset*1][j+1] && this->pieces[i+offset*1][j+1]->color == other){
				//cout<<"adding move: "<<i<<j<<"->"<<i+offset*2<<j+2<<endl;
				capMoves.push_back(Move(i, j, i+2*offset, j+2, i+1*offset, j+1));
			}
			if(!this->pieces[i+offset*2][j-2] && i+offset*2<8 && j-2>=0
				&& this->pieces[i+offset*1][j-1] && this->pieces[i+offset*1][j-1]->color == other){
				//cout<<"adding move: "<<i<<j<<"->"<<i+offset*2<<j-2<<endl;
				capMoves.push_back(Move(i, j, i+2*offset, j-2, i+1*offset, j-1));
			}
		}
	} //end of j in Board::getMoves
	} // end of i
	if(capMoves.size())
		return capMoves;
	return moves;
}

void Board::executeMove(Move move){
	this->pieces[move.xNew][move.yNew] = this->pieces[move.xOld][move.yOld];
	this->pieces[move.xOld][move.yOld] = NULL;
	if(move.capMove){
		this->pieces[move.xCap][move.yCap] = NULL;
	}
}
