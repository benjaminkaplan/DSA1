#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
using namespace std;

template<typename T>
class Node{
  public:
    T data;
    Node* next;
    Node(T t, Node* node){data = t; next = node;}
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


void parseLine(string& str){ //NOT USED
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
    string line;
    while(getline(input,line) ){
       //cout<<str<<endl;
       stringstream ss(line);
       ss>>str;
       //cout<<"PROCESSING COMMAND: "<<line<<endl;
       if(!(line.compare(0,6,"create"))) { //confirms presence of CREATE command
         cout<<"create found"<<endl;
         continue;
       }
       if(!(line.compare(0,4,"push"))){ //confirms presence of CREATE command
         cout<<"push found"<<endl;
       }
       if(!(line.compare(0,3,"pop"))){ //confirms presence of CREATE command
         cout<<"pop found"<<endl;
       }
    }

    return 0;

}
