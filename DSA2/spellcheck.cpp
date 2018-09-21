#include <iostream>
#include <fstream>
#include "hash.h"
#include <ctime>
using namespace std;
int main(){
	
	
	cout <<"Enter name of dictionary: ";
	string dict_name = "";
	//cin >> dict_name;
	dict_name = "wordlist_small.txt";
	cout << "Enter name of input file: ";
	string input_name = "";
	//cin >> input_name;
	input_name = "lyrics.txt";
	cout << "Enter name of output file: ";
	string output_name = "";
	//cin >> output_name;
	output_name = "outfile.txt";
	
	ifstream input_file;
	input_file.open(input_name);
	ifstream dict_file;
	dict_file.open(dict_name);
	ofstream output_file;
	output_file.open(output_name);
	hashTable table = hashTable(100) ;	
	string line = "a";
	int start_s=clock();
	while( line.length() ){
		getline(dict_file,line);
		table.insert(line);
	}
	int stop_s=clock();
	cout << "Total time (in seconds) to check document: " << (stop_s-start_s)/double(CLOCKS_PER_SEC) << endl;

	int line_counter = 1;
	int word_length = 0;
	string word = "";
	char letter = 'a';
	while( (letter = input_file.get() ) != EOF){
		while( (letter >= 48 && letter <= 57 )|| 
		        letter =='-' || 
                        letter== '\''  || 
                       (letter >= 65 && letter <= 122) ){
			word += letter;
		}
		cout<<word<<endl;
		word = "";
	}
	//cout<<"pos of zygote: "<<table.contains("Zionism")<<endl;
	dict_file.close();
	input_file.close();
	return 0;
}
