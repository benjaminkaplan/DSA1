#include "hash.h"
#include <string>
#include <iostream>
using namespace std;
hashTable::hashTable(int size): capacity(getPrime(size)) , filled(0), data(getPrime(size)){
  //capacity  = getPrime(size); // The current capacity of the hash table.
  //filled = 0; // Number of occupied items in the table.
  //vector<hashItem> data(getPrime(size));
	/*
	cout<<"prime: "<<getPrime(size)<<endl;
	cout<<"capacity: "<<this->capacity<<endl;
	cout<<"filledd: "<<this->filled<<endl;
	*/
}

int hashTable::insert(const std::string &key, void *pv ){
	//cout<<"filled"<<this->filled<<endl;
	string hash_key = key;
	int pos = hashTable::hash(hash_key);
	hashItem item;
	item.isOccupied  = true;
	item.isDeleted = false;
	item.key = hash_key;
	item.pv = pv;
	if(!this->data[pos].isOccupied){ //entry is empty
		//cout<<"entry was empty, inserting slot "<<pos<<endl;
		//cout<<"sameness chaeck: "<<this->data[pos].key.compare(key)<<endl;
		//if( !this->data[pos].key.compare(key) )
		//	cout<<"same key found"<<endl;
		//	return 1;
		this->data[pos] = item;
	}
	
	else if(this->data[pos].isOccupied){ //entry is taken
		//std::vector<hashItem>::iterator it = this->data[pos];

		while( this->data[pos].isOccupied){ //search for open slot
			if(pos >= this->capacity)
				pos = 0;	
			//cout<<"entry is TAKEN, current occupant: "<<hash_key<<"\t slot: "<<pos<<endl;
			
			if( !this->data[pos].key.compare(key) )
				return 1;
			pos++;
		}
		this->data[pos] = item;
	}
	this->filled++;
	float filled_percentage = (float)this->filled/(float)this->capacity;	
	//cout<<"filled percentage: "<<filled_percentage<<"\tfilled: "<<this->filled<<"\tcapacity: "<<this->capacity<<endl;
	if(filled_percentage > 0.5){
		//cout<<"rehashing"<<endl;	
		if(!this->rehash()); // return true on failure
			return 2;
	}
	return 0;
}

bool hashTable::rehash(){
	int size = getPrime(this->capacity + 1);
	vector<hashItem> old_table = this->data;
	vector<hashItem> new_table(size);
	this->capacity = size;
	this->filled = 0;
	this->data = new_table;
	for(int i = 0 ; i < old_table.size(); i++){
		if(!old_table[i].isDeleted){ //not deleted
			if(old_table[i].isOccupied){ //is occupied
				//cout<<"inserting: "<<old_table[i].key<<endl;
				this->insert(old_table[i].key,old_table[i].pv);
			}
		}
	}

	return true;
}

bool hashTable::contains(const std::string &key){
	if(findPos(key) > 0 )
		return true;
	return false;
}	

int hashTable::findPos(const std::string &key){
	string hash_key = key;	
	int pos = hash(hash_key);
	while(this->data[pos].isOccupied){
		if(!this->data[pos].isDeleted){ //is NOT deleted
			if(!this->data[pos].key.compare(hash_key)) //same key
				return pos;
		}
		pos++;
	}
	return -1;
}

int hashTable::hash(const std::string &key){
	const char* Key_Ptr = key.c_str();
	unsigned int hash_val = 0;
	while( *Key_Ptr )
		hash_val = (hash_val << 5) + *Key_Ptr++;
	hash_val = hash_val % (this->capacity); 
	return (hash_val);
}


unsigned int hashTable::getPrime(int size){
	unsigned int primes[] = {53, 97 , 193 , 389 , 769 , 1543 , 3079 , 6151 , 12289 , 24593 , 49157 , 98317 , 196613 , 393241 , 786433 , 1572869 , 3145739 , 6291469 , 12582917 , 25165843 ,50331653 , 100663319 , 201326611 , 402653189 , 805306457 , 1610612741}; // list of primes taken from 
																								 //https://planetmath.org/goodhashtableprimes
	for( int i = 0; i < 26; i++){
		if( primes[i] > size)
			return primes[i];
	}
	return 0; // run out of sizes
}
