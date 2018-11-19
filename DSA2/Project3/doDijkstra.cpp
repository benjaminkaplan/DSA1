#include "graph.h"
#include <fstream>
#include <string>
//#include <time>
using namespace std;

Graph graph(1000);

string getSourceName(){
	string entered = "";
	while(!graph.contains(entered)){
		cout<<"Enter ID for starting vertex: ";
		cin>>entered;
	}

	return entered;	
}

void loadGraph(){
	ifstream infile;
	string entered;
	cout<<"Enter name of graph file: ";
	cin>>entered;
	infile.open(entered);

	string s1;
	string s2;
	int distance;
	string line = " ";
	while(infile>>s1>>s2>>distance){
		//getline(infile, line);
		graph.insert(s1, s2, distance);
		//cout<<"line: "<<line<<endl;
	}
	//start = clock();

}

void printGraph(){
	ofstream outfile;
	string entered;
	cout<<"Enter output file: ";
	cin>>entered;
	outfile.open(entered);
	graph.printGraph(outfile);	
}
int main(){
	loadGraph();
	string source = getSourceName();
	clock_t start = clock();
	graph.doDijkstra(source);
	clock_t stop = clock();
	double time = ((double)stop-start) / CLOCKS_PER_SEC;
	cout<<"Time for Dijkstra's Algorithm: "<<time<<endl;
	printGraph();
	return 0;
}
