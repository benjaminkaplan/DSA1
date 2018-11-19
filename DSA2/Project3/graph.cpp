#include <iostream>
#include <string>
#include "hash.h"
#include "heap.h"
#include "graph.h"
#include <list>
#include <limits.h>
#include <fstream>

Graph::Graph(int size) : capacity(0){
	this->nodes_table = new hashTable(size*2);
};

int Graph::insert(string &source, string &dest, int cost){ // returns 0 on success, 1 if node exists
	Node *node1;
	Node *node2;
	if( !contains(source) ) //Node not found
		node1 = NULL;
	else
		node1 = (Node*) nodes_table->getPointer(source);

	if( !contains(dest) ) //Node not found
		node2 = NULL;
	else
		node2 = (Node*) nodes_table->getPointer(dest);

	Edge edge;
	if(!node1){
		node1 = new Node;
		node1->name = source;
		node1->distance = INT_MAX;
		node1->known = false;
		nodes_table->insert(source, node1);
		nodes.push_back(node1);
		this->capacity++;
	}
	if(!node2){
		node2 = new Node;
		node2->name = dest;
		node2->distance = INT_MAX;
		node2->known = false;
		nodes_table->insert(dest, node2);
		nodes.push_back(node2);
		this->capacity++;
	}
	edge.cost = cost;
	edge.next = node2;
	node1->adjacent.push_back(edge);
	return 0;
}

bool Graph::contains(string &name){
	if(nodes_table->contains(name))
		return true;
	return false;
}

void Graph::printGraph(ofstream &out){
	for(auto it = nodes.begin(); it != nodes.end(); it++){
		out<<(*it)->name<<": ";
		if((*it)->distance == INT_MAX)
			out<<"NO PATH"<<endl;
		else{
			out<<(*it)->distance<<" [";
			for(auto next_node = (*it)->path.begin(); next_node != (*it)->path.end(); next_node++){
				if((*it)->path.size() == 1)
					out<<(*next_node)->name;
				else
					out<<", "<<(*next_node)->name;
			}
			out<<"]"<<endl;
		}
	}
}

void Graph::doDijkstra(string &source_name){
	Node *source_node = (Node*) nodes_table->getPointer(source_name);
	source_node->distance = 0;
	source_node->path.push_back(source_node);
	heap* graph_heap  = new heap(capacity);
	graph_heap->insert(source_name, source_node->distance, source_node);
	for(auto it = nodes.begin(); it !=nodes.end(); it++){
		if((*it)->name.compare(source_name))
			graph_heap->insert((*it)->name, (*it)->distance, (*it));
	}
	Node *temp_node;
	for(int i = 0; i< this-> capacity; i++){
		graph_heap->deleteMin(NULL, NULL, &temp_node);
		for(auto it = temp_node->adjacent.begin(); it != temp_node->adjacent.end() && temp_node->distance!= INT_MAX; it++){
			if (!it->next->known && ( (it->next->distance) > (it->cost + temp_node->distance) ) ) {
				it->next->path.clear();
				it->next->path.insert(it->next->path.begin(), temp_node->path.begin(), temp_node->path.end());
				it->next->path.push_back(it->next);
				it->next->distance = (it->cost + temp_node->distance);
				graph_heap->setKey(it->next->name, (it->cost + temp_node->distance));
			}
		}
		temp_node ->known = true; 
	}
}

