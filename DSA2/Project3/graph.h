#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <list>
#include <iostream>
#include <string>
#include "hash.h"
using namespace std;
class Graph{
public:

private:
	//class Edge;
	class Node;
	class Edge{
	public:
		Node* next;
		Node* prev;
		int cost;
	};

	class Node{
	public:
		bool known;
		string name;
		int distance;
		list<Edge> adjacent;
		list<Node*> path;
	};

	hashTable *nodes_table;
	list<Node*> nodes;
	int capacity;
	
public:
	Graph(int size);
	int insert(string &source, string &dest, int cost); // returns 0 on success, 1 if node exists
	void printGraph(ofstream &outfile);
	void doDijkstra(string &source);	
	bool contains(string &name);
};


#endif
