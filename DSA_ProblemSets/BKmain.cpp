#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
using namespace std;

bool emptyListFlag = false;

template<class T>
class SimpleList{  //Node is a struct inside the SimpleList<T> class
  protected:
    struct Node{
      T data;
      Node* next;
      Node(T t = 0, Node* n = NULL) : data(t), next(n) {}
    };
    void insertTop(const T t);
    void insertBottom(const T t);
    T removeTop();
  public:
    virtual void push(T t)=0; // these functions will be resolved at run time so they are pure virtual
    virtual T pop() =0;       // in the base class
    string getName(){return this->name;} // used for findList() function
    SimpleList<T>(string& str): name(str), top(new Node) , bottom(new Node){top->next = bottom; bottom->next = top;}
    SimpleList<T>(string& str, int i): name(str), top(new Node(string(),NULL)) , bottom(new Node(string(),NULL)){
      top->next = bottom;  // this second constructor for simple list was created because the zero parameter version
      bottom->next = top;  // would not work with a string because default values of the struct are 0, and a string
      top->data= "";       // object cannot be NULL or 0. Therefore, when creating a new string list, the sentinel nodes
      bottom->data = "";   // are specified as string()
    }
  private:
    Node* top;
    Node* bottom;
    string name;
};

template<class T>
void SimpleList<T>::insertTop(const T t){ // inserts node at top of list
  Node *node = new Node(t,NULL );         //used for Stack push() function
  if(top->next == bottom){
    bottom->next = node;
  }
  node->next = top->next;
  top->next = node;
}
template<class T>
void SimpleList<T>::insertBottom(const T t){ // inserts node at bottom of list
  Node *node = new Node(t,bottom);           //used for Queue push() function
  if(bottom->next == top){
    top->next = node;
  }
  else{
    bottom->next->next = node;
  }
  bottom->next = node;
}
template<class T>
T SimpleList<T>::removeTop(){ // removes node from top of list
  if(top->next == bottom){    //used for both versions of pop() - both are identical
    emptyListFlag = true;     // returns the data stored in the popped node
    bottom->next = top;
  }
  T temp = top->next->data;
  top->next = top->next->next;
  return temp;
}

template<class T>
class Stack: public SimpleList<T>{
  public:
    Stack<T>(string& str):SimpleList<T>(str){}
    Stack<T>(string& str,int i):SimpleList<T>(str,i){} // 2 parameter constructor indicates string list
    void push(const T t){
      this->SimpleList<T>::insertTop(t);
    }
    T pop(){
      T temp = this->SimpleList<T>::removeTop();
      if(emptyListFlag){                               // emptyListFlag is set by pop() function in case of
        cout<<"ERROR: This list is empty!"<<endl;;        // popping an empty list
        emptyListFlag = false;
      }
      else
        cout<<"Value popped: "<<temp<<endl;          // normally, this line executes
      return temp;
    }
};

template<class T>
class Queue: public SimpleList<T>{
  public:
    Queue<T>(string&str): SimpleList<T>(str){}
    Queue<T>(string&str, int i): SimpleList<T>(str,i){} // 2 parameter constructor indicates string list
    void push(const T t){
      this->SimpleList<T>::insertBottom(t);
    }
    T pop(){
      T temp = this->SimpleList<T>::removeTop();
      if(emptyListFlag){
        cout<<"ERROR: This list is empty!"<<endl;        // Please see notes for pop() above
        emptyListFlag = false;
      }
      else
        cout<<"Value popped: "<<temp<<endl;
      return temp;
    }
};

template<class T>
SimpleList<T>* findList(list<SimpleList<T> *>& l,string& s){  // finds if list of given name
  typename list<SimpleList<T>* >::iterator SL = l.begin();    // is present in the correct list
  string temp;
  while(SL != l.end()){                                       // returns pointer to SimpleList<T> of the
    if(!s.compare((*SL)->getName()))                          // given name, or NULL if none is found
        return (*SL);
    SL++;
  }
  return NULL;
}

void createList(string& name, string& value,list<SimpleList<int> *>& listSLi, list<SimpleList<double> *>& listSLd, list<SimpleList<string> *>& listSLs){
  if(!name.compare(0,1,"i")){                                    // creates instance of SimpleList<T> object with given name and data type,
    SimpleList<int> *pSLi;                                       // adds it to list of SimpleList<T> objects.
    if(listSLi.size() && findList(listSLi,name)){                // Check if name is taken and if list is empty
      cout<<"ERROR: This name already exists!"<<endl;
      return;
    }
    if(!value.compare(0,5,"stack")){                             // Breaks up type of list by data type (int,double,string) and
      pSLi = new Stack<int>(name);                               // then by list type (Stack,Queue)
    }
    if(!value.compare(0,5,"queue")){
      pSLi = new Queue<int>(name);
    }
    listSLi.push_front(pSLi);
  }
  if(!name.compare(0,1,"d")){
    SimpleList<double> *pSLd;
    if(listSLd.size() && findList(listSLd,name)){
      cout<<"ERROR: This name already exists!"<<endl;
      return;
    }
    if(!value.compare(0,5,"stack")){
      pSLd = new Stack<double>(name);
    }
    if(!value.compare(0,5,"queue")){
      pSLd = new Queue<double>(name);
    }
    listSLd.push_front(pSLd);
  }
  if(!name.compare(0,1,"s")){
    SimpleList<string> *pSLs;
    if(listSLs.size() && findList(listSLs,name)){
      cout<<"ERROR: This name already exists!"<<endl;
      return;
    }
    if(!value.compare(0,5,"stack")){
      pSLs = new Stack<string>(name,1);
    }
    if(!value.compare(0,5,"queue")){
      pSLs = new Queue<string>(name,1);
    }
    listSLs.push_front(pSLs);
  }
}//END OF createList()

void pushList(string& name, string& value,list<SimpleList<int> *>& listSLi, list<SimpleList<double> *>& listSLd, list<SimpleList<string> *>& listSLs){
  if(!name.compare(0,1,"i")){                                 // Pushes for each given data type and name
    SimpleList<int>* SLi = findList(listSLi,name);
    if(SLi);{    //checks that list of given name exists
      SLi->push(stoi(value)); //converts string of value to correct data type and pushes
      return;
    }
  }
  if(!name.compare(0,1,"d")){
    SimpleList<double>* SLd = findList(listSLd,name);
    if(SLd){
      SLd->push(stod(value));
      return;
    }
  }
  if(!name.compare(0,1,"s")){
    SimpleList<string>* SLs = findList(listSLs,name);
    if(SLs){
      SLs->push(value);
      return;
    }
  }
  cout<<"ERROR: This name does not exist!"<<endl; // If the SL* pointer is NULL every time, then the list does not exist
}

void popList(string& name, list<SimpleList<int> *>& listSLi, list<SimpleList<double> *>& listSLd, list<SimpleList<string> *>& listSLs){
  if(!name.compare(0,1,"i")){                               //Very similar to pushList above, uses same strategy for pops
    SimpleList<int>* SLi = findList(listSLi,name);          // output of pop is written out in pop() function
    if(SLi && !emptyListFlag){
      SLi->pop();
      return;
    }
  }
  if(!name.compare(0,1,"d")){
    SimpleList<double>* SLd = findList(listSLd,name);
    if(SLd && !emptyListFlag){
      SLd->pop();
      return;
    }
  }
  if(!name.compare(0,1,"s")){
    SimpleList<string>* SLs = findList(listSLs,name);
    if(SLs && !emptyListFlag){
        SLs->pop();
        return;
    }
  }
  cout<<"ERROR: This name does not exist!"<<endl;
}


int main(){
  string infile;
  string outfile;
  cout<<"Enter name of input file: ";         //takes input from user to command list and output file
  cin>>infile;
  cout<<"Enter name of output file: ";
  cin>>outfile;
  ofstream out(outfile);             // FILE REDIRECTION
  streambuf *coutbuf = cout.rdbuf(); //save old buf
  cout.rdbuf(out.rdbuf()); //redirect cout to temp
  list<SimpleList<int> *> listSLi; // all integer stacks and queues
  list<SimpleList<double> *> listSLd; // all double stacks and queues
  list<SimpleList<string> *> listSLs; // all string stacks and queues
  ifstream input;
  input.open(infile);
  string line;
  //getline(input,line);
  while(getline(input,line)){
    if(!line.compare("")){ // prevents processing of empty line at end of file
      break;
    }
    cout<<"PROCESSING COMMAND: "<<line<<endl; // Every line is always written back out first
    stringstream ss(line);
    string iter;
    string command;  // command, name and type (if applicable) are gathered first and then
    string name;     // passed to functions
    string value;
    ss>>iter;
    command = iter;
    ss>>iter;
    name = iter;
    ss>>iter;
    value = iter;
    
    if(!(command.compare("create"))) { //confirms presence of CREATE command
      createList(name,value, listSLi, listSLd,listSLs);
      continue;
    }
    else if(!(command.compare("push"))){ //confirms presence of PUSH command
      pushList(name, value,listSLi,listSLd,listSLs);
    }
    else if(!(command.compare("pop"))){ //confirms presence of POP command
      popList(name,listSLi,listSLd,listSLs);
    }
    
  }
  cout<<""<<endl; //matches number of bytes for EOF
  out.close();

  return 0;

}
