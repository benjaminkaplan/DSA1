#include <string>
#include <iostream>
#include <fstream>
using namespace std;

string detectMerge(string A, string B, string C){
	int lenA = A.length();
	int lenB = B.length();
	bool matches[lenA+1][lenB+1] = {false};
	int A_spots[lenA] = {0}, slot = 0;
	for(int i = 0; i <= lenA; i++){
		for(int j = 0; j <= lenB; j++){

			cout<<"i: "<<i<<", j: "<<j<<endl;
			// two empty strings have an empty string 
            		// as interleaving 
			if (i==0 && j==0) 
		                matches[i][j] = true; 
  
			// A is empty 
			else if (i==0 && B[j-1]==C[j-1]) 
        		        matches[i][j] = matches[i][j-1]; 
  
			// B is empty 
			else if (j==0 && A[i-1]==C[i-1]){
				matches[i][j] = matches[i-1][j]; 
				//A_spots[slot++] = i+j-1;
			}
  
			// Current character of C matches with current character of A, 
			// but doesn't match with current character of B 
			else if(A[i-1]==C[i+j-1] && B[j-1]!=C[i+j-1]){
				matches[i][j] = matches[i-1][j]; 
				//A_spots[slot++] = i+j-1;
			}

			// Current character of C matches with current character of B, 
			// but doesn't match with current character of A 
			else if (A[i-1]!=C[i+j-1] && B[j-1]==C[i+j-1]) 
				matches[i][j] = matches[i][j-1]; 
  
			// Current character of C matches with that of both A and B 
			else if (A[i-1]==C[i+j-1] && B[j-1]==C[i+j-1]){
				matches[i][j]=(matches[i-1][j] || matches[i][j-1]) ; 
				//A_spots[slot++] = i+j-1;
			}

		}
	}
	//int A_spots[lenA] = {0}, slot = 0;
	/*for(int i = 1 ;i<= lenA; i++){
		int true_in_row = 0;
		for(int j = 0; j <= lenB; j++){
			if((i>0 || j > 0) && (true_in_row % 2 == 0) && matches[i][j]){
				true_in_row++;
				A_spots[slot++] = i+j-1;
			}
		}
	}
	*/
	
	for(int i = 1 ;i<= lenA; i++){
		int true_in_row = 0;
		for(int j = 0; j <= lenB; j++){
			if((i>0 || j > 0) && true_in_row==0 && matches[i][j]){
				true_in_row++;
				A_spots[slot++] = i+j-1;
			}
		}
	}
	cout<<"================================="<<endl;
	for(int i =0 ; i<=lenA ; i++){
		for(int j =0 ; j<= lenB; j++){
			if(matches[i][j])
				cout<<"T";
			else
				cout<<"_";
		}
		cout<<endl;
	}
	if(!matches[lenA][lenB])
		return "***NOT A MERGE***";

	//for(int i =0 ;i <lenA; i++ )
	//	cout<<A_spots[i]<<endl;
	string result = C;
	for(int i=0 ;i <lenA; i++)
		result[A_spots[i]] = toupper(result[A_spots[i]]);
	return result;
}

int main(){
	string s = "hellow world";
	cout<<s<<endl;
	//cout<<"first letter of s: "<<s[-1]<<endl;

	//cout<<detectMerge("abbc", "abab", "ababbcab")<<endl;
	cout<<detectMerge("zzzzzzzzzzzzzzzzzzzzab", "zzzzzzzzzzzzzzzzzzzzac", "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzacab")<<endl;
	//cout<<detectMerge("ab", "ba", "abab")<<endl;
	//cout<<detectMerge("choco", "late", "latechoco")<<endl;
		//cout<<"found a merge"<<endl;
	return 0;
}

