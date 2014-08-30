#pragma once

#include "OutOfBoundsException.h"

using namespace std;

template<class t>
class OrdLinkedList{
public:
	OrdLinkedList<t>();
	~OrdLinkedList<t>();
	void insert(const t& elem);
	bool find(const t& elem);
	bool remove(const t& elem);
	t at(int pos);
	t operator[](int pos);
	int length();
	bool first(t& elem);
	bool last(t& elem);
	bool next(t& elem);
	bool previous(t& elem);
	bool isEmpty();
	void print();
private:
	struct node{
		t data;
		node* next;
		node* previous;	
	};
	node* front;
	node* back;
	node* current;
	int current_pos;
	int list_length;
};

template<class t>
OrdLinkedList<t>::OrdLinkedList(){
	front = new node;
	back = new node;
	current = new node;
	front = NULL;
	back = NULL;
	current = NULL;
	list_length = 0;
	current_pos = 0;
}

template<class t>
OrdLinkedList<t>::~OrdLinkedList(){
	current = front;
	//while current->next != true delete current; delete front;
}

template<class t>
void OrdLinkedList<t>::insert(const t& elem){
	list_length++;
	node* temp = new node;
	temp->data = elem;
	node* temp2 = new node;	
	temp2 = current;	
	if(isEmpty()){		
		temp->next = NULL;
		temp->previous = NULL;		
		front = temp;
		back = temp;	
		current = temp;
	}
	else if(elem == front->data){
		temp->previous = front;
		temp->next = front->next;
		front->next = temp;		
	}
	else if(elem == back->data){
		temp->previous = back->previous;
		temp->next = back;
		back->previous = temp;		
	}
	else if(elem == current->data){
		temp->previous = current;
		temp->next = current->next;
		current->next = temp;	
	}
	else if(elem < front->data){	
		temp->next = front;
		temp->previous = NULL;
		front->previous = temp;
		front = temp;		
	}
	else if(elem > back->data){		
		temp->previous = back;
		temp->next = NULL;
		back->next = temp;
		back = temp;	
	}
	
	else if(elem < temp2->data && front != temp2 && back != temp2){		
		while(temp2!= NULL){
			if(elem < temp2->data && elem > temp2->previous->data){
				temp->previous = temp2->previous;
				temp->next = temp2;
				temp2->previous->next = temp;
				temp2->next->previous = temp;
				break;
			}
			else if(elem == temp2->data){
				temp->next = temp2->next;
				temp->previous = temp2;
				temp2->next = temp;
				break;
			}
			temp2=temp2->previous;
		}	
	}
	else if(elem > temp2->data && front != temp2 && back != temp2){
		while(temp2 != NULL){
			if(elem > temp2->data && elem < temp2->next->data){
				temp->next = temp2->next;
				temp->previous = temp2;
				temp2->next->previous = temp;				
				temp2->previous->next = temp;
				break;
			}
			else if(elem == temp2->data){
				temp->next = temp2->next;
				temp->previous = temp2;
				temp2->next = temp;
				break;
			}
			temp2=temp2->next;
		}	
	}
	else{
		temp2 = front;											
		while(temp2 != NULL){
			if(elem > temp2->data && elem < temp2->next->data){				
				temp->next = temp2->next;
				temp->previous = temp2;
				temp2->next = temp;
				temp->next->previous = temp;
				break;
			}
			else if(elem == temp2->data){
				temp->next = temp2->next;
				temp->previous = temp2;
				temp2->next = temp;
				break;
			}
			temp2=temp2->next;
		}
	}
}

template<class t>
bool OrdLinkedList<t>::find(const t& elem){	
	node* temp = new node;
	if(isEmpty() == false){
		if(current->data <= elem){
			temp = current;
		}
		else 
			temp = front;		
		while(temp != NULL){
			if(temp->data == elem){
				return true;				
			}
			temp = temp->next;
		}		
	}
	return false;
}

template<class t>
bool OrdLinkedList<t>::remove(const t& elem){
	bool found = false;
	node* temp = new node;
	node* temp2 = new node;
	if(elem >= current->data)
		temp = current;
	else
		temp = front;
	while(temp != NULL){
		if(temp->data == elem){
			temp2=temp->next;
			if(temp->previous != NULL)
				temp->previous->next = temp->next;
			else{
				temp->next->previous = NULL;
				front = temp->next;
			}
			if(temp->next != NULL)
				temp->next->previous = temp->previous;
			else{				
				temp->previous->next = NULL;
				back = temp->previous;
			}
			delete temp;
			temp = temp2;
			found = true;
		}
		else
			temp = temp->next;		
	}
	return found;
}

template<class t>
bool OrdLinkedList<t>::first(t& elem){
	if(front != NULL){
		current = front;
		current_pos = 0;
		elem = current->data;
		return true;
	}
	else
		return false;
}

template<class t>
bool OrdLinkedList<t>::last(t& elem){
	if(back != NULL){
		current = back;
		current_pos = list_length-1;
		elem = current->data;
		return true;
	}
	else
		return false;
}

template<class t>
bool OrdLinkedList<t>::next(t& elem){
	if(current->next != NULL){
		current = current->next;
		elem = current->data;
		current_pos++;
		return true;
	}
	else
		return false;
}

template<class t>
bool OrdLinkedList<t>::previous(t& elem){
	if(current->previous != NULL){
		current = current->previous;
		elem = current->data;
		current_pos--;
		return true;
	}
	else
		return false;
}

template<class t>
t OrdLinkedList<t>::at(int pos){
	node* search = new node;
	try{
		if(current_pos >= pos && pos >= 0)
		{
			if(current_pos - pos > pos || current_pos == 0){
				search = front;
				for(int i = 0; i <pos;i++){
					search=search->next;
				}
				return search->data;
			}
			else{
				search = current;
				for(int i = current_pos; i >pos;i--){
					search=search->previous;
				}
				return search->data;
			}
		}
		else if(current_pos < pos && pos <= list_length-1){
			if(pos-current_pos < list_length - pos - 1){
				search = current;
				for(int i = current_pos; i <pos;i++){
					search = search->next;
				}
				return search->data;
			}
			else{
				search = back;
				for(int i = list_length-1; i >pos;i--){
					search=search->previous;
				}
				return search->data;
			}
		}
		else{
			throw OutOfBoundsException();			
		}
	}
	catch(OutOfBoundsException &e){
		e.what();
	}
}

template<class t>
t OrdLinkedList<t>::operator[](int pos){
	return at(pos);
}		

template<class t>
bool OrdLinkedList<t>::isEmpty(){
	if(front == NULL && back == NULL){
		return true;
	}
	else 
		return false;
}

template<class t>
void OrdLinkedList<t>::print(){
	node* print_node = front;
	while(print_node != NULL){
		cout<<print_node->data<<endl;
		print_node = print_node->next;
	}	


	cout<<endl<<endl<<endl;
	print_node = back;
	while(print_node != NULL){
		cout<<print_node->data<<endl;
		print_node = print_node->previous;
	}
}

