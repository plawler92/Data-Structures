#pragma once
#include"SafeArrayOutOfBoundsException.h"

using namespace std;

template<class t>

class SafeArray{
public:
	SafeArray<t>();
	SafeArray<t>(int start_size);
	SafeArray<t>(SafeArray<t>& pass_in_arr);	
	t& at(int pos);
	t& operator[](int pos);
	int size();
	void resize(int new_size);
	void push_back(t& val_to_add);
	void push_back(SafeArray<t>& arr_to_add);
	void pop_back();
	~SafeArray();			

private:
	t* p_array;
	int array_size;
	int capacity;
};

template<class t>
SafeArray<t>::SafeArray(){
	array_size = 0;
	capacity = array_size;
	p_array = new int[0];
}

template<class t>
SafeArray<t>::SafeArray(int start_size){
	array_size = start_size;
	capacity = array_size;
	p_array = new t[array_size];
}

template<class t>
SafeArray<t>::SafeArray(SafeArray<t>& pass_in_arr){					
	array_size = pass_in_arr.size();
	capacity = array_size;
	p_array = new t[array_size];
	for(int i = 0; i<pass_in_arr.size();i++){
		p_array[i] = pass_in_arr[i];
	}		
}

template<class t>
t& SafeArray<t>::at(int pos){
	if(pos < 0 || pos >= array_size){
		cout<<"Array pointer out of bounds"<<endl;
		system("pause");
		exit(0);
	}
	else{
		return p_array[pos];
	}
}

template<class t>
t& SafeArray<t>::operator[](int pos){
	try{
		if(pos < 0 || pos >= array_size){			]]
			throw SafeArrayOutOfBoundsException();
		}
	}
	catch(SafeArrayOutOfBoundsException &e){
		e.what();
	}
	return p_array[pos];
}


template<class t>
int SafeArray<t>::size(){
	return array_size;
}

template<class t>
void SafeArray<t>::resize(int new_size){
	if(new_size > array_size){
		t* new_array = new t[new_size];
		for(int i = 0; i <array_size;i++){
			new_array[i] = p_array[i];
		}
		delete [] p_array;
		p_array = new_array;
	}
	else{
		t* new_array = new t[new_size];
		for(int i = 0; i < new_size;i++){
			new_array[i] = p_array[i];
		}
		delete [] p_array;
		p_array = new_array;
	}
	array_size = new_size;
	capacity = array_size;
	cout<<"Vector resized due to a call to the resize function."<<endl;
}

template<class t>
void SafeArray<t>::push_back(t& val_to_add){
	if(array_size == capacity){
		capacity = capacity *2;		
		t* new_array = new t[capacity];
		for(int i = 0; i <array_size;i++){
			new_array[i] = p_array[i];
		}
		delete [] p_array;
		p_array = new_array;
	}
	p_array[array_size] = val_to_add;
	array_size++;
	cout<<"Vector resized due to a call to the push back function."<<endl;
}

template<class t>
void SafeArray<t>::push_back(SafeArray<t>& arr_to_add){		
	for(int i = 0; i < arr_to_add.size();i++){
		push_back(arr_to_add[i]);
	}
	cout<<"Vector resized due to a call to the push back function."<<endl;
}

template<class t>
void SafeArray<t>::pop_back(){	
	t* new_array = new t[array_size-1];
	for(int i = 0; i < array_size-1;i++){
		new_array[i] = p_array[i];
	}
	delete [] p_array;
	p_array = new_array;
	array_size--;
	if(array_size < (capacity / 2)){
		capacity = capacity / 2;
	}
	cout<<"Vector resized due to a call to the pop back function."<<endl;
}

template<class t>
SafeArray<t>::~SafeArray(){
	delete [] p_array;
}




