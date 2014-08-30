#pragma once

using namespace std;

template<class t>
class LinkList{
public:
	LinkList<t>();
	~LinkList<t>();
	void insertAtFront(const t& elem);			
	void insertAtRear(const t& elem);			
	bool removeFromFront();						
	bool removeFromRear();						
	bool remove();								
	bool first(t& elem);
	bool last(t& elem);
	bool next(t& elem);
	bool previous(t& elem);
	bool currentFunc(t& elem);
	bool isEmpty();
	void print();
	int LinkList_length();								

private:
	//create node struct here
	struct node{
		t data;
		node* next;
		node* previous;	
	};
	node* front;
	node* back;
	node* current;
	int list_length;
	bool at_start;
};

template<class t>
LinkList<t>::LinkList(){
	front = new node;
	back = new node;
	current = new node;	
	list_length = 0;
	front =  NULL;
	back = NULL;
	current = NULL;
}

template<class t>
LinkList<t>::~LinkList(){
	current = front;
	while(current != NULL){				
		front = current;
		current = current->next;
		delete front;
	}	
	
}

template<class t>
void LinkList<t>::insertAtFront(const t& elem){
	node* temp = new node;
	temp->data = elem;
	
	temp->next = front;
	front = temp;
	front->previous = NULL;
	
	if(temp->next){
		temp->next->previous = front;
	}
	if(back == NULL){
		back = front;
		current = front;
	}
	list_length++;
}

template<class t>
void LinkList<t>::insertAtRear(const t& elem){
	node* temp = new node;
	temp->data = elem;
	temp->previous = back;
	temp->next = NULL;
	back = temp;	
	if(temp->previous){
		temp->previous->next = back;
	}
	if(front == NULL){
		front = back;
		current = front;
	}	
	list_length++;
}	

template<class t>						
bool LinkList<t>::removeFromFront(){
	if(front != NULL){
		node* temp = new node;
		temp = front;
		front = temp->next;
		delete temp;
		list_length--;
		return true;
	}
	else
		return false;
}

template<class t>
bool LinkList<t>::removeFromRear(){
	if(back != NULL){
		node* temp = new node;
		temp = back;
		back = temp->previous;
		back->next = NULL;
		delete temp;
		list_length--;
		return true;
	}
	else
		return false;
}

template<class t>
bool LinkList<t>::remove(){
	node* temp = new node;
	if(current->previous != NULL && current->next != NULL){		
		current->previous->next = current->next;
		current->next->previous = current->previous;			
	}
	if(current->previous == NULL && current->next != NULL){
		current->next->previous = NULL;
	}
	if(current->next == NULL && current->previous != NULL){
		current->previous->next = NULL;
	}
	if(current->next != NULL){
		temp = current->next;
	}
	else if(current->previous != NULL){
		temp = current->previous;
	}
	delete current;	
	return true;
	list_length--;
} 

template<class t>
bool LinkList<t>::first(t& elem){
	if(front != NULL){
		current = front;
		elem = current->data;
		return true;
	}
	else{
		return false;
	}
}

template<class t>
bool LinkList<t>::last(t& elem){
	if(back != NULL){
		current = back;
		elem = current->data;
		return true;
	}
	else {
		return false;
	}
}

template<class t>
bool LinkList<t>::next(t& elem){
	if(current->next != NULL){
		current = current->next;
		elem = current->data;
		return true;
	}
	else
		return false;
}

template<class t>
bool LinkList<t>::previous(t& elem){
	if(current->previous != NULL){
		current = current->previous;
		elem = current->data;
		return true;
	}
	else
		return false;
}

template<class t>
bool LinkList<t>::currentFunc(t& elem){
	if(current != NULL){
		elem = current->data;
		return true;
	}
	else
		return false;
}

template<class t>
int LinkList<t>::LinkList_length(){
	return list_length;
}

template<class t>
void LinkList<t>::print(){
	node* temp = new node;
	temp = front;
	while(temp != NULL){
		temp->data.print();		
		temp = temp->next;
	}		
}

template<class t>
bool LinkList<t>::isEmpty(){
	if(list_length > 0)
		return false;
	else
		return true;
}







