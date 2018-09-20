#include "hash.h"
#include <string>
using namespace std;
hashTable::hashTable(int size): capacity(getPrime(size)) , filled(0), data(getPrime(size)){
  //capacity  = getPrime(size); // The current capacity of the hash table.
  //filled = 0; // Number of occupied items in the table.
  //vector<hashItem> data(getPrime(size));
}

int hashTable::insert(const std::string &key, void *pv ){
	string hash_key = key;
	int pos = hashTable::hash(hash_key);
	hashItem item;
    item.isOccupied  = true;
	item.isDeleted = false;
	item.key = hash_key;
	item.pv = pv;
	if(!this->data[pos].isOccupied){ //entry is empty
		if( !this->data[pos].key.compare(key) )
			return 1;
		this->data[pos] = item;
	}
	
	else if(this->data[pos].isOccupied){ //entry is taken
		//std::vector<hashItem>::iterator it = this->data[pos];
		while( item.isOccupied){ //search for open slot
			if( !this->data[pos].key.compare(key) )
				return 1;
			pos++;
		}
		this->data[pos] = item;
	}
	filled++;
	if((this->filled / this->capacity) > 0.5)
		if(!this->rehash() )
			return 2;
	return 0;
}

bool hashTable::rehash(){
	int size = getPrime(this->capacity);
	vector<hashItem> old_table = this->data;
	vector<hashItem> new_table(size);
	this->data = new_table;
	for(int i = 0 ; i < old_table.size(); i++){
		if(!old_table[i].isDeleted){ //not deleted
			if(old_table[i].isOccupied){ //is occupied
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

int findPos(const std::string &key){
	int pos = hash(key);
	while(this->data[pos].isOccupied){
		if(!this->data[pos].isDeleted){
			if(!this->data[pos].key.compare(key))
				return pos;
		}
		pos++
	}
	return -1;
}

int hashTable::hash(const std::string &key){
	const char* Key_Ptr = key.c_str();
	int hash_val = 0;
	while( *Key_Ptr )
		hash_val = (hash_val << 5) + *Key_Ptr++;
	return hash_val % this->capacity;
}


static int getPrime(int size){
	int primes[] = {53, 97 , 193 , 389 , 769 , 1543 , 3079 , 6151 , 12289 , 24593 , 49157 , 98317 , 196613 , 393241 , 786433 , 1572869 , 3145739 , 6291469 , 12582917 , 25165843 ,50331653 , 100663319 , 201326611 , 402653189 , 805306457 , 1610612741}; // list of primes taken from 
																								 //https://planetmath.org/goodhashtableprimes
	for( int i = 0; i < 26; i++){
		if( primes[i] > size)
			return primes[i];
	}
	return 0; // run out of sizes
}
