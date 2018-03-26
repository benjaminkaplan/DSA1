#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
using namespace std;

template<typename T>
class Node{
  T data;
  Node* next;
};

template<typename T>
class SimpleList{
    Node<T>* first;
    Node<T>* last;
    string getName(){return this.name;}
  private:
      string name;
  protected:

};


void parseLine(string& str){
    stringstream ss(str);
    string temp;
    while(ss>>str){
      //ss>>str;
      cout<<str<<endl;
    }
}

int main()
{
    cout << "Hello world!" << endl;
    ifstream input;
    input.open("commands.txt");
    string str;
    while(getline(input,str) ){
       //cout<<str<<endl;
       parseLine(str);    
    }
    
    return 0;

}
