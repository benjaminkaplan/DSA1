#include "hash.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
hashTable::hashTable(int size): capacity(getPrime(size)) , filled(0), data(getPrime(size)){ 
}

int hashTable::insert(const std::string &key, void *pv ){
	string hash_key = key;
	int pos = hashTable::hash(hash_key);
	hashItem item;
	item.isOccupied  = true;
	item.isDeleted = false;
	item.key = hash_key;
	item.pv = pv;
	while( this->data[pos].isOccupied ){ //search for open slot				
		if( !this->data[pos].key.compare(key) && !this->data[pos].isDeleted){ //same key found
			return 1;
		}
		pos++;
		if(pos >= this->capacity)
			pos = 0;
		
	}
	this->data[pos] = item;
	this->filled++;
	float filled_percentage = (float)this->filled/(float)this->capacity;	
	if(filled_percentage > 0.5){
		if(!this->rehash()); // return 2 on failure
			return 2;
	}
	return 0;
}

bool hashTable::rehash(){
	int size = getPrime(this->capacity);
	vector<hashItem> old_table = this->data;
	vector<hashItem> new_table(1);
	try{
		new_table.resize(size);
	}
	catch(std::bad_alloc& ba ){
		return false;
	}
	this->capacity = size;
	this->filled = 0;
	this->data = new_table;
	for(int i = 0 ; i < old_table.size(); i++){
			if(old_table[i].isOccupied){ //is occupied
				this->insert(old_table[i].key,old_table[i].pv);
			}
	}
	return true;
}

bool hashTable::contains(const std::string &key){
	if(findPos(key) >= 0 )
		return true;
	return false;
}	

int hashTable::findPos(const std::string &key){
	string hash_key = key;	
	int pos = hash(hash_key);
	while(this->data[pos].isOccupied){
		if(!this->data[pos].isDeleted){ //is NOT deleted
			if(!this->data[pos].key.compare(hash_key)) // is same key
				return pos;
		}
		pos++;
		if(pos >= this->capacity)
			pos = 0;
	}
	return -1;
}

int hashTable::hash(const std::string &key){ //returns hash table position
	const char* Key_Ptr = key.c_str();   //hash function taken from Weiss textbook pg. 184
	unsigned int hash_val = 0;
	while( *Key_Ptr )
		hash_val = (hash_val << 5) + *Key_Ptr++;
	hash_val = hash_val % (this->capacity); 
	return (hash_val);
}


unsigned int hashTable::getPrime(int size){
	unsigned int primes[] = {53, 97 , 193 , 389 , 769 , 1543 , 
				3079 , 6151 , 12289 , 24593 , 49157 , 
				98317 , 196613 , 393241 , 786433 , 
				1572869 , 3145739 , 6291469 , 
				12582917 , 25165843 ,50331653 , 
				100663319 , 201326611 , 402653189 , 
				805306457 , 1610612741}; // list of primes taken from
							 //https://planetmath.org/goodhashtableprimes
	for( int i = 0; i < 26; i++){
		if( primes[i] > 2*size)
			return primes[i];
	}
	return 1610612741; // run out of sizes
}

void* hashTable::getPointer(const std::string &key, bool *b ){
	string hash_key = key;
	int pos;
	if( (pos = findPos(hash_key)) >= 0 && (!(this->data[pos].isDeleted)) ){
		if(b)		
			*b = true;
		return this->data[pos].pv;
	}
	if(b)
		*b = false;

	return NULL;
}

int hashTable::setPointer(const std::string &key, void *pv){
	string hash_key = key;
	int pos;
	if( (pos = findPos(hash_key)) >= 0 && !(this->data[pos].isDeleted) ){
		this->data[pos].pv = pv;
		return 0;
	}
	return 1;
}

bool hashTable::remove(const std::string &key){
	string hash_key = key;
	int pos;
	if((pos = findPos(key)) >= 0){
		this->data[pos].isDeleted = true;
		return true;
	}
	else
		return false;
}
