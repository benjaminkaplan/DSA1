#include <string>
#include <iostream>
#include <fstream>
using namespace std;

bool matches[1001][1001] = {false}; //global array of booleans
int path[1001] = {0}; // used to find indices for letters to highlight

bool match(const string A, const string B, const string C, int i, int j){
	return ((matches[i-1][j] && (C[i+j-1] == A[i-1])) || (matches[i][j-1] && (C[i+j-1] == B[j-1]))); 
}

void getPath(const string A, const string B){
	int i = A.length(), j = B.length(), slot = 0;
	
	while(i >0  || j> 0){
		if(matches[i-1][j] && !matches[i][j-1]&& i-1>=0){ // upward motions indicate letter from first string
			i--;
			path[slot++] = i+j;
		}
		else if(matches[i][j-1] && j-1>=0) // sideways motions indicate letter from second string
			j--;			
	}
}

string detectMerge(const string A, const string B, const string C){
	if(A.length() + B.length() != C.length())
		return "*** NOT A MERGE ***";
	for(int i =0 ; i<1001; i++){ // clear the arrays
		path[i] = 0;
		for(int j =0 ; j<1001; j++)
			matches[i][j] = false;
	}
	matches[0][0] = true; // starting point
	for(int i =0; i<= A.length(); i++){ // fill in the array recursively by checking previous values
		for(int j =0; j<= B.length(); j++){
			if(!i && !j)
				continue;
			matches[i][j] = match(A, B, C, i,j);
		}
	}

	if(!matches[A.length()][B.length()]) // the string are not a merge
		return "*** NOT A MERGE ***";
	getPath(A, B); // indices in merged string to highlight 
	string result = C;
	for(int i = 0 ;i < A.length(); i++){
		result[path[i]] = toupper(result[path[i]]); // returns correctly formatted string, highlighting letters from string A
	}
	return result;
}

int main(){
	string in_name, out_name;
	cout<<"Enter name of input file: ";
	cin>>in_name;
	cout<<"Enter name of output file: ";
	cin>>out_name;
	ifstream infile;
	ofstream outfile;
	infile.open(in_name);
	outfile.open(out_name);	
	string A, B, C;
	while(infile>>A>>B>>C){
		outfile<<detectMerge(A,B,C)<<endl; // runs the algorithm
	}
	//outfile<<endl; // fixes newline issue at end of file
	infile.close();
	outfile.close();
	return 0;
}

