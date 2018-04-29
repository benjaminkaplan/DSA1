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
#include <bitset>

  int indices0[256];
  int indices1[256];
  int indices2[256];
  int indices3[256];
  Data* col3chars[50000*sizeof(Data*)][256];
  Data* nums[1100000*sizeof(Data*)];
  
void sortDataList(list<Data *> &l, int field) {
  // Fill in this function

  if(field == 2){
	Data* temp = NULL;
	unsigned t = 0;
	
	while( !l.empty()){ // First pass, remove from list
	  temp = l.front();
	  t = (temp->val2);
	  t = t & (255);
	  col3chars[indices3[t]][t] = temp;
	  indices3[t]++;
      l.pop_front();
	}
    int count = 0;
	for(int i = 0 ; i < 256; i++){ // Drop into holder array
	  int n = indices3[i];
      for(int j = 0; j<n; j++){	
	    nums[count] = col3chars[j][i];  
		count++;
	  }  
    }
	for(int q = 0; q< count; q++){ // 2nd pass
	  temp = nums[q];
      t = ((temp->val2)>>8) & 255;
	  col3chars[indices2[t]][t] = temp;
	  indices2[t]++;
	}
	count = 0;
	for(int i = 0 ; i < 256; i++){ // return to holder array #2
	  int n = indices2[i];
      for(int j = 0; j<n; j++){	
	    nums[count] = col3chars[j][i];  
		count++;
	  }  
    }	
	for(int q = 0; q< count; q++){ // 3rd pass
	  temp = nums[q];
      t = ((temp->val2)>>(16)) & 255;
	  col3chars[indices1[t]][t] = temp;
	  indices1[t]++;
	}
	count = 0;
	for(int i = 0 ; i < 256; i++){ // return to holder array #3
	  int n = indices1[i];
      for(int j = 0; j<n; j++){	
	    nums[count] = col3chars[j][i];  
		count++;
	  }  
    }
	for(int q = 0; q< count; q++){ // 4th pass
	  temp = nums[q];
      t = ((temp->val2)>>(24)) & 255;
	  col3chars[indices0[t]][t] = temp;
	  indices0[t]++;
	}
	count = 0;
	for(int i = 0 ; i < 256; i++){ // return to holder array (list) #4
	  int n = indices0[i];
      for(int j = 0; j<n; j++){	
	    l.push_back(col3chars[j][i]);
	  }  
    }
	  
	
  
  }

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
	auto it = l.begin();
	while( it != l.end()){
	  temp = (*it);
	  int t = temp->val3;
	  col3chars[indices3[t]][t] = temp;
	  indices3[t]+=1;
      it++;
	}
	it = l.begin();
    for(int i = 33 ; i < 127; i++){
	  int n = indices3[i];
      for(int j = 0; j<n; j++){	
	    (*it) = col3chars[j][i];
        it++;		
	  }  
    }
  }
   
  
}
