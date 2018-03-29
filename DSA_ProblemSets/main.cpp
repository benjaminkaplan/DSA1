#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
using namespace std;

bool emptyListFlag = false;

template<class T>
class SimpleList{
  protected:
    struct Node{
      T data;
      Node* next;
      Node(T t= 0, Node* n = NULL) : data(t), next(n) {}
    };
    Node* top;
    Node* bottom;
    void insertTop(const T t);
    void insertBottom(const T t);
    T removeTop();
  public:
    virtual void push(T t){;}
    virtual T pop() {;}
    void insertPublic(const T& t){insertTop(t);}
    void insertBottomPublic(const T& t){insertBottom(t);}
    T removePublic(){removeTop();}
    string getName(){return this->name;}

    SimpleList<T>():name("s1"), top(new Node) , bottom(new Node){top->next = bottom;bottom->next = top;} //Constructorc
    SimpleList<T>(string& str): top(new Node) , bottom(new Node){name = str; top->next = bottom; bottom->next = top;}
  private:
    string name;
};

template<class T>
void SimpleList<T>::insertTop(const T t){
  Node *node = new Node(t,top->next );
  if(node->next == bottom){
    cout<<"New Stack Found"<<endl;
    bottom->next = node;
  }
  top->next = node;
}
template<class T>
void SimpleList<T>::insertBottom(const T t){
  Node *node = new Node(t,bottom);
  if(bottom->next == top){
    cout<<"NEW QUEUE FOUND"<<endl;
    top->next = node;
    //node->next = bottom;
  }
  else{
    bottom->next->next = node;
  }
  bottom->next = node;

}
template<class T>
T SimpleList<T>::removeTop(){
  if(top->next == bottom){
    //cout<<"ERROR: This list is empty! (Removve top)"<<endl;
    cout<<"found empty list in removeTop()"<<endl;
    emptyListFlag = true;
  }
  T temp = top->next->data;
  top->next = top->next->next;
  return temp;
}

template<class T>
class Stack: public SimpleList<T>{
  public:
    Stack<T>(string& str){
      SimpleList<T>();//==========================FIGURE OUT HOW TO PASS str TO CONTRUCTOR
    }
    void push(const T t){
      this->SimpleList<T>::insertTop(t);
    }
    T pop(){
      T temp = this->SimpleList<T>::removeTop();
      if(emptyListFlag){
        cout<<"ERROR: This list is empty!"<<endl;
        !emptyListFlag;
      }
      else
        cout<<"Value popped: "<<temp<<endl;
      return temp;
    }
};

template<class T>
class Queue: public SimpleList<T>{
  public:
    Queue<T>(string &str){
      SimpleList<T>();//SAME AS NOTE ABOVE FOR STACKS!!!!!!!
    }
    void push(const T t){
      this->SimpleList<T>::insertBottom(t);
    }
    T pop(){
      T temp = this->SimpleList<T>::removeTop();
      if(emptyListFlag){
        cout<<"ERROR: This list is empty!"<<endl;
        !emptyListFlag; //emptyListFlag will now be false
        //return NULL;
      }
      else
        cout<<"Value popped: "<<temp<<endl;
      return temp;
    }
};

template<class T>
SimpleList<T>* findList(list<SimpleList<T> *>& l,string& s){
  typename list<SimpleList<T>* >::iterator SL = l.begin();
  cout<<"name is "<<(*SL)->getName()<<endl;
  cout<<"In the findList() function"<<endl;
  string temp;
  while(SL != l.end()){
    if(!s.compare((*SL)->getName()))
        return (*SL);
    SL++;
  }
  return NULL;
}

void createList(string& line, list<SimpleList<int> *> listSLi, list<SimpleList<double> *> listSLd, list<SimpleList<string> *> listSLs){
  stringstream ss(line);
  string iter;
  string name;
  string type;
  ss>>iter;
  name = iter; cout<<name<<endl;
  if(!line.compare(0,1,"i")){
    ss>>iter;
    type = iter; cout<<iter<<endl;
    if(!type.compare(0,5,"stack")){
      cout<<"this is a stack"<<endl;
      SimpleList<int> *pSLi;
      pSLi = new Stack<int>(name);
      listSLi.push_front(pSLi);
    }
  }
}


int main(){
  cout<<"hello world\n"<<endl; //string str = "hello";
  string str2 = "hello";
  list<SimpleList<int> *> listSLi; // all integer stacks and queues
  list<SimpleList<double> *> listSLd; // all double stacks and queues
  list<SimpleList<string> *> listSLs; // all string stacks and queues
   Stack<int> s1(str2);
  Stack<double> s2(str2);
  SimpleList<int>* s3;
  s3 = new Queue<int>(str2);
  cout<<"Queue stuff coming================="<<endl;
  s3->push(15);
  s3->push(20);
  s3->pop();
  cout<<s3->pop()<<endl;
  cout<<s3->pop()<<endl;
  listSLi.push_front(s3);
  string str3 = "s1";
  findList(listSLi, str3);
  /*
  ifstream input;
  input.open("commands.txt");
  string str;
  string line;
  while(getline(input,line) ){
    if(!(line.compare(0,6,"create"))) { //confirms presence of CREATE command
      //cout<<"create found"<<endl;
      string temp = line.substr(7,string::npos);
      createList(temp, listSLi, listSLd,listSLs);
      continue;
    }
    else if(!(line.compare(0,4,"push"))){ //confirms presence of CREATE command
      //cout<<"push found"<<endl;
    }
    else if(!(line.compare(0,3,"pop"))){ //confirms presence of CREATE command
      //cout<<"pop found"<<endl;
    }
  }
  */

  return 0;
}
