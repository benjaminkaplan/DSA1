#include "hash.h"
#include <string>
#include <iostream>
#include <fstream>
#include "heap.h"
#include "hash.h"
#include <limits.h>

using namespace std;

heap::heap(int size): capacity(size){
  data.resize(capacity+1);
  mapping = new hashTable(capacity*2);
  node n;
  n.key = INT_MIN; // place smallest element at head, cannot use position 0 because 0*2 = 0
  filled = 0;
  this->data[0] =n;  //sentinel node
}

int heap::insert(const std::string &id, int key, void *pv ){
	if(this->filled >= this->capacity)
		return 1; // filled heap
	if(this->mapping->contains(id))
		return 2; // node with given id already exists
	this->filled++;
	node* n = &(this->data[filled]);
	n->id = id;
	n->key = key;
	n->pData = pv;
	this->mapping->hashTable::insert(id, n);
	this->data[filled] = *n;
	this->percolateUp(this->filled); //Need to figure out percolation
	return 0;
}

int heap::setKey(const std::string &id, int key){
	void * temp;
	bool up_down = false;
	if( !(temp = this->mapping->getPointer(id)) )
		return 1;
	node* n = static_cast<node*>(temp);
	if(n->key < key){
		up_down = true;
	}
	else if(n->key > key){
		up_down = false;
	}
	n->key = key;
	if(up_down)
		this->percolateDown(getPos(n));
	else
		this->percolateUp(getPos(n));
	return 0;
}

int heap::deleteMin(std::string *pId , int *pKey , void *ppData ){
	if(!(this->filled))
		return 1;
	node n = this->data[1]; // smallest element
	if(pId)
		*pId = n.id;
	if(pKey)
		*pKey = n.key;
	if(ppData)
		*(void**) ppData = n.pData;

	this->setKey(this->data[1].id, INT_MAX); // will percolate the smallest node to the filled position
	this->mapping->remove(this->data[filled].id);
	filled--;
	return 0;
}

int heap::remove(const std::string &id, int *pKey , void *ppData ){
	void * temp;
	if( !(temp = this->mapping->getPointer(id)) ){
		return 1;
	}
	node* n = static_cast<node*>(temp);
	if(pKey)
		*pKey = n->key;
	if(ppData){
		*(void**) temp = static_cast<void*>(ppData);
	}
	setKey(id, INT_MIN); // setKey to smallest and do a deleteMin
	this->deleteMin(NULL,NULL,NULL);
	return 0;
}

void heap::percolateUp(int posCur){ 
	while(this->data[posCur/2].key > this->data[posCur].key && posCur>0){ // if parent > child
		mapping->setPointer(this->data[posCur].id, &(this->data[posCur/2]));
		mapping->setPointer(this->data[posCur/2].id, &(this->data[posCur]));
		node temp = this->data[posCur];
		this->data[posCur] = this->data[posCur/2];
		this->data[posCur/2] = temp;
		posCur/=2;
	}
}

void heap::percolateDown(int posCur){ 	
	//mapping->setPointer(this->data[filled].id, &(this->data[posCur]));
	//mapping->setPointer(this->data[posCur].id, &(this->data[filled]));
	if(this->data[posCur].key == INT_MAX){ // switch with last position if we came from deleteMin, indicated by INT_MAX 
		mapping->setPointer(this->data[filled].id, &(this->data[posCur]));
		mapping->setPointer(this->data[posCur].id, &(this->data[filled]));

		node temp = this->data[posCur]; 	
		this->data[posCur] = this->data[filled];
		this->data[filled] = temp;
	}
	int child = posCur;
	while(posCur*2 <= filled){
		child = 2 * posCur;
		if(this->data[child+1].id != ""){ // find smallest child
			if(this->data[child+1].key < this->data[child].key)
				child++;
		}
		if(this->data[child].key < this->data[posCur].key){ // if child > parent
			mapping->setPointer(this->data[child].id, &(this->data[posCur]));
			mapping->setPointer(this->data[posCur].id, &(this->data[child]));
			node temp = this->data[posCur]; 
			this->data[posCur] = this->data[child];
			this->data[child] = temp;
		}
		else
			break;
		posCur = child;
	}
}

int heap::getPos(node *pn){
	int pos = pn - &data[0];
	return pos;
}

