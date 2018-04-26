// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2018

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  unsigned int val1;
  unsigned int val2;
  char val3;
  string val4;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->val1 >> pData->val2 >> pData->val3 >> pData->val4;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->val1 << " " 
	   << (*ipD)->val2 << " " 
	   << (*ipD)->val3 << " " 
	   << (*ipD)->val4 << endl;
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &, int field);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.  Executing sort..." << endl;

  int field = 0;
  cout << "Enter an integer from 1 - 4, representing field to sort: ";
  try {
    cin >> field;
    if (field < 1 || field > 4) {
      cerr << "Error: invalid field" << endl;
      exit(1);
    }
  }
  catch (...) {
    cerr << "Error: invalid field" << endl;
    exit(1);
  }
    
  clock_t t1 = clock();
  sortDataList(theList, field);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.


//Data* col3arr[110000*sizeof(Data*)];
int indices[128];
Data* col3chars[110000*sizeof(Data*)][128];
Data* col2chars[110000*sizeof(Data*)][128];
void sortDataList(list<Data *> &l, int field) {
  // Fill in this function
  if( field == 1){
    list<Data*>::iterator ahead = l.begin();
    list<Data*>::iterator it = l.begin();
    it++;
    for(; it != l.end(); it++){
      for(auto it2 = it; it2 != l.begin(); it2--){
        ahead = it2; ahead--;
		if( (*it2)->val1 < (*ahead)->val1)
			swap(*it2,*ahead);
		else
			break;
	  }
    }
  }
  else if(field == 3){
    Data* temp = NULL;
	while( !l.empty()){
	  temp = l.back(); 
	  int t = temp->val3;
	  col3chars[indices[t]][t] = temp;
	  indices[t]++;
      l.pop_back();
	}	
	for(int c = 33; c<127; c++){
	  int n = indices[c];
	  for( int r = 0; r<n;r++ ){
        l.push_back(col3chars[r][c]);
      }	  
	}
  }
  else if(field == 2){
    unsigned i = 10;
	unsigned j = i<<2;
	unsigned k = j & ~(32);
	cout<<"J: "<<j<<endl;
	cout<<"K: "<<k<<endl;
  /*	
	Data* temp = NULL;
	int index = 0;
	while( !l.empty()){
	  temp = l.back(); 
	  unsigned int t = temp->val2;	  
	  index = t & ~(2);
	  cout<< "T is : "<<t<<"\tindex: "<<index<<endl;
	  col3chars[indices[index]][index] = temp;
	  indices[index]++;
      l.pop_back();
	}
  */
  } 
    
  
}
