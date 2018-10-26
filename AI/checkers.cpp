#include "board.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
	cout<<"Hello wolrd!"<<endl;
	Piece p1 = Piece(0,0,'r', "p1");
	cout<<"piece name:"<<p1.name<<", coords: ("<<p1.x<<p1.y<<"), color: "<<p1.color<<endl; 
	Board b = Board();
	cout<<"created board"<<endl;
	b.showBoard();
}
