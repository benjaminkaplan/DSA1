#include <iostream>
#include <fstream>
#include "hash.h"
using namespace std;
int main(){
	cout <<"Enter name of dictionary: ";
	string dict_name = "";
	cin >> dict_name;
	cout << "Enter name of input file: ";
	string input_name = "";
	cin >> input_name;
	//cout<<dict_name<<endl;
	//cout<<input_name<<endl;
	cout << "Enter name of output file: ";
	string output_name;
	cin >> output_name;
	ifstream dict_file;
	cout<<dict_name<<endl;
	dict_file.open(dict_name);
	string line = "a";
	hashTable table = hashTable(100) ;
	while( line.length() ){
		getline(dict_file,line);
		
	}
	dict_file.close();
	return 0;
}