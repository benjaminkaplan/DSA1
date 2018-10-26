#include <iostream>
#include <string>
#include <vector>

#include "board.h"
using namespace std;
/*
class Board;
Board::Board(){
	cout<<"In board consturctor"<<endl;
}
*/
void Board::showBoard(){
	cout<<"in showboard"<<endl;
	cout<<"  A   B   C   D   E   F   G   H  "<<endl;
	cout<<" ___ ___ ___ ___ ___ ___ ___ ___ "<<endl;
	//cout<<"|";
	for(int r = 7 ; r>=0; r--){
		for( int i = 1; i< 34; i++){
			if(i % 4 == 1)
				cout<<"|";
			else if( i%4 == 3){
				if(this->pieces[r][i/4]){
					if(this->pieces[r][i/4]->color == 'r' && this->pieces[r][i/4]->alive)
							cout<<'R';
				}
				if(this->pieces[r][i/4]){
					if(this->pieces[r][i/4]->color == 'w' && this->pieces[r][i/4]->alive)
							cout<<'W';
				}
				else
					cout<<" ";
			}
			else 
				cout<<" ";
			
		}
		cout<<endl;
		//cout<<"|   |   |   |   |   |   |   |   |"<<endl;
		cout<<"|___|___|___|___|___|___|___|___|"<<endl;		
		
	}
	cout<<endl;
};
