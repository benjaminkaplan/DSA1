#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
using namespace std;

template<typename T>
class Node{
  public:
    T data;
    Node* next;
    Node* previous;
    Node(T t, Node<T>* n,Node<T>* p){data = t; next = n; previous = p;}
};

template<typename T>
class SimpleList{
  public:
    Node<T>* first;
    Node<T>* last;
    string getName(){return this.name;}
    virtual void push(Node<T>&);
    virtual void pop();
  private:
      string name;
  protected:

};

template<typename T>
class Stack: public SimpleList<T>{ //Stack inherits SimpleList
  public:
    Node<T>* nodes;
    void push(Node<T>& n){
      //Node<T>* temp;
      n->prev = this.last;
      this.last->next = NULL;
      this.last = n;}
    Node<T>* pop(){
      Node<T>& temp = this.last;
      this.last = this.last->prev;
      return temp;
    }

};


template<typename T>
class Queue: public SimpleList<T>{
  public:
    Node<T>* nodes;
    //void pushQueue(Node<T>& n){cout<<"push Queue\n"<<endl;}
    //void popQueue(){cout<<"poppped queue\n"<<endl;}
    void push(Node<T>& n){
      n->prev = this.last;
      this.last->next = NULL;
      this.last = n;
    }
    Node<T>* pop(){
      Node<T>* temp = this.first;
      this.first = this.first->next;
      return temp;
    }
};


void parseLine(string& str){ //NOT USED
    stringstream ss(str);
    string temp;
    while(ss>>str){
      //ss>>str;
      cout<<str<<endl;
    }
}

void createList(string line){
  stringstream ss(line);
  string str;
  string name;
  ss>>str; name = str;
  //cout<<"the name is "<<name<<endl;
  if(!line.compare(0,1,"i")){
    //cout<<"dealing with integer================================================\n"<<endl;
    ss>>str;
    if(!str.compare("stack"))
      ;//CALL STACK CONTRUCTOR
    if(!str.compare("queue"))
      ;//CALL QUEUE CONSTRUCTOR
  }
}

int main()
{
    list<SimpleList<int> *> listSLi; // all integer stacks and queues
    list<SimpleList<double> *> listSLd; // all double stacks and queues
    list<SimpleList<string> *> listSLs; // all string stacks and queues

    cout << "Hello world!" << endl;
    ifstream input;
    input.open("commands.txt");
    string str;
    string line;
    while(getline(input,line) ){
       //cout<<str<<endl;
       //stringstream ss(line);
       //ss>>str;
       //cout<<"PROCESSING COMMAND: "<<line<<endl;
       if(!(line.compare(0,6,"create"))) { //confirms presence of CREATE command
         cout<<"create found"<<endl;
         createList(line.substr(7,string::npos) );
         continue;
       }
       else if(!(line.compare(0,4,"push"))){ //confirms presence of CREATE command
         cout<<"push found"<<endl;
       }
       else if(!(line.compare(0,3,"pop"))){ //confirms presence of CREATE command
         cout<<"pop found"<<endl;
       }
    }

    return 0;

}
