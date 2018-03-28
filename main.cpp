#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
using namespace std;

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
    void insertTop(const T& t);
    void insertBottom(const T& t);
    T removeTop();
  public:
    virtual void push(T& t){;}
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
void SimpleList<T>::insertTop(const T& t){
  Node *node = new Node(t,top->next );
  if(node->next == bottom){
    cout<<"found empty list"<<endl;
    bottom->next = node;
  }
  top->next = node;
}
template<class T>
void SimpleList<T>::insertBottom(const T& t){
  Node *node = new Node(t,NULL);
  if(bottom->next == top){
    cout<<"NEW QUEUE FOUND"<<endl;
    top->next = node;
  }
  bottom->next = node;
  bottom = node;
}
template<class T>
T SimpleList<T>::removeTop(){
  T temp = top->next->data;
  top = top->next;
  return temp;
}

template<class T>
class Stack: public SimpleList<T>{
  public:
    Stack<T>(string& str){
      SimpleList<T>();//==========================FIGURE OUT HOW TO PASS str TO CONTRUCTOR
    }
    void push(const T& t){
      this->SimpleList<T>::insertTop(t);
    }
    T pop(){
      return this->SimpleList<T>::removeTop();
    }
};

template<class T>
class Queue: public SimpleList<T>{
  public:
    Queue<T>(string &str){
      SimpleList<T>();//SAME AS NOTE ABOVE FOR STACKS!!!!!!!
    }
    void push(const T& t){
      this->SimpleList<T>::insertBottom(t);
    }
    T pop(){
      return this->SimpleList<T>::removeTop();
    }
};
/*
template<class T>
bool checkDuplicateName(list<SimpleList<T> *> l){
  list<SimpleList<T> *>::iterator it;
  for (it = l.begin(); it != l.end(); ++it){
    cout << (*it)->getName()<<endl;
  }
  return false;
}
*/
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
  list<SimpleList<int> *> listSLi; // all integer stacks and queues
  list<SimpleList<double> *> listSLd; // all double stacks and queues
  list<SimpleList<string> *> listSLs; // all string stacks and queues
  /* Stack<int> s1(str);
  cout<<"name of s1 is "<<s1.getName()<<endl;
  s1.push(2);
  s1.push(1);
  s1.push(3);
  s1.push(4);
  s1.push(5.2);
  cout<<s1.pop()<<endl;
  cout<<s1.pop()<<endl;
  cout<<s1.pop()<<endl;
  cout<<s1.pop()<<endl;
  Stack<double> s2(str);
  Queue<double> s3(str);
  s3.push(1.05);
  s3.push(20);
  cout<<s3.pop()<<endl;
  */
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


  return 0;
}
