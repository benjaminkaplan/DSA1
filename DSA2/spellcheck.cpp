#include <iostream>
#include <fstream>
#include "hash.h"
#include <ctime>
using namespace std;

bool contains_number(const std::string &str)
{
    return (str.find_first_of("0123456789") != std::string::npos);
}   

int main(){
	
	
	cout <<"Enter name of dictionary: ";
	string dict_name = "";
	cin >> dict_name;
	cout << "Enter name of input file: ";
	string input_name = "";
	cin >> input_name;
	cout << "Enter name of output file: ";
	string output_name = "";
	cin >> output_name;
	
	ifstream input_file;
	input_file.open(input_name);
	ifstream dict_file;
	dict_file.open(dict_name);
	ofstream output_file;
	output_file.open(output_name);

	hashTable table = hashTable(1000) ;	
	string line = "a";
	int start_s=clock();
	char letter = 'a';
	string word = "";
	while( (letter = dict_file.get()) != EOF ){
		if(letter == '\n'){
			table.insert(word);
			word = "";
		}else{
			if(letter != '\r'){ //protects against pesky carriage returns
				word += tolower(letter);
			}
		}
	}
	int stop_s=clock();
	dict_file.close();
	cout << "Total time (in seconds) to load dictionary: " << (stop_s-start_s)/double(CLOCKS_PER_SEC) << endl;

	int line_counter = 1;
	int word_length = 0;
	bool long_flag = false;
	start_s = clock();
	while( (letter = input_file.get() ) != EOF){ //word separators 0-9, -, ', A-Z, a-z
		if( (letter >= '0' && letter <= '9' )|| 
		     letter =='-' || 
                     letter== '\''  || 
                    (letter >= 'A' && letter <= 'Z') ||
    		    (letter >= 'a' && letter <= 'z') ){
			if(!long_flag){
				word += tolower(letter);
				word_length++;
			}
		
		} else{
			if(word.length() && !table.contains(word) && !long_flag && !contains_number(word)){
				output_file<<"Unknown word at line "<<line_counter<<": "<<word<<endl;
			}
			word = "";
			word_length = 0;
			long_flag = false;
		}	
		if(letter == '\n')
			line_counter++;
		if(word_length > 20 && !long_flag){
			output_file<< "Long word at line "<<line_counter<<", starts: " << word.substr(0,20)<<endl;
			long_flag= true;
		}
	}
	stop_s=clock();
	cout << "Total time (in seconds) to check document: " << (stop_s-start_s)/double(CLOCKS_PER_SEC) << endl;
	input_file.close();
	output_file.close();
	return 0;
}

