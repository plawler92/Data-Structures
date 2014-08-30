#include"SafeArray.h"
#include"LinkList.h"

#pragma once

using namespace std;

template<class t>
class HashTable{
public:
	HashTable<t>();
	HashTable<t>(int init_size);
	~HashTable<t>();
	void insert(const string& key, const t& value);
	void printCollisionInfo();
	bool remove(const string& key);
	bool retrieve(const string& key, t& elem);
	bool isEmpty();
	
private:
	unsigned int hash(const string& something);	
	SafeArray<LinkList<t>> table;
	int length;
	int arr_size;
};

template<class t>
HashTable<t>::HashTable():table(1){
	length = 0;
	arr_size = 1;
}

template<class t>
HashTable<t>::HashTable(int init_size):table(init_size){	
	length = 0;	
	arr_size = init_size;
}

template<class t>
HashTable<t>::~HashTable(){			
	//probably won't need to put anything in here
}

template<class t>
void HashTable<t>::insert(const string& key, const t& value){	
	unsigned int key_num = hash(key);	
	table[key_num].insertAtFront(value);	
	length++;
}

template<class t>
bool HashTable<t>::remove(const string& key){
	unsigned int key_num = hash(key);
	t pointer;
	if(table[key_num].first(pointer)){
		if(pointer == key){			
			table[key_num].removeFromFront();
			return true;
		}
		else{
			while(table[key_num].next(pointer)){
				if(pointer == key){					
					table[key_num].remove();	
					return true;
				}
			}
		}
	}
	return false;
}

template<class t>
bool HashTable<t>::retrieve(const string& key, t& elem){
	unsigned int key_num = hash(key);
	t pointer;
	if(table[key_num].first(pointer)){
		if(pointer == key){
			elem = pointer;			
			return true;
		}
		else{
			while(table[key_num].next(pointer)){
				if(pointer == key){
					elem = pointer;
					return true;
				}
			}
		}
	}
	return false;	
}

template<class t>
unsigned int HashTable<t>::hash(const string& something){
	unsigned int key_num = 0;
	string key = something;
	char add_val;
	for(int i = 0; i < key.size(); i++)
	{
		add_val = key[i];
		if(add_val % 2 == 0)
			add_val = add_val / 2;
		else 
			add_val += 7;
		if(i % 2 == 0)
			add_val += 7;
		else
			add_val +=31;
		key_num += add_val * 33;	
	}
	key_num = key_num % arr_size;
	return key_num;	
}

template<class t>
void HashTable<t>::printCollisionInfo(){
	
	int avg_length = 0;
	int num_filled = 0;
	int num_empty = 0;
	int longest = 0;
	for(int i = 0; i <arr_size; i ++){
		if(table[i].isEmpty()){
			num_empty++;
		}
		else{
			num_filled++;
			avg_length += table[i].LinkList_length();
			if(table[i].LinkList_length() > longest)
				longest = table[i].LinkList_length();
		}
	}
    avg_length = avg_length / num_filled;
	cout<<"There are "<<num_empty<<" empty lists."<<endl;
	cout<<"There are "<<num_filled<<" non empty lists."<<endl;
	cout<<"The average list length is "<<avg_length<<"."<<endl;
	cout<<"The longest list length is "<<longest<<"."<<endl;
}

template<class t>
bool HashTable<t>::isEmpty(){
	if(length > 0)
		return false;
	else
		return true;
}
		


