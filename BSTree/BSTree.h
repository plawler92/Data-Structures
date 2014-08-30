#pragma once
#include<queue>

template<class T>
class BSTree{
public:
	BSTree();
	/*~BSTree();*/
	void insert(const T& d);
	bool search(const T& d);
	bool remove(const T& d);
	int size();
	void printInOrder();
	void printPreOrder();
	void printPostOrder();
	T findMax();
	T findMin();
	int heightOfTree();
	double percentLeaf();
	double percentInterior();	
	int getHeightDifference();
	void balanceLeftLeft();
	void balanceLeftRight();
	void balanceRightLeft();
	void balanceRightRight();
	int isBalanced();
	void printTestOrder();
	void printInTreeForm();
private:
	struct node{				
		T data;
		node* left;
		node* right;
	};
	node* root; 
	int num_elements;
	void insertHelper(const T& d, node*& p_node);
	bool searchHelper(const T& d, node*& p_node);
	bool removeHelper(node*& p_node, const T& d);
	void inOrderHelper(node*& p_node);
	void preOrderHelper(node*& p_node);
	void postOrderHelper(node*& p_node);
	void BSTreeHelper(node*& p_node);	
	int heightOfTreeHelper(node*& p_node);
	int left_height;
	int right_height;
	double num_interior;
	double num_leaf;
	void percentHelper(node*& p_node);	
	int getHeightDifferenceHelper(node*& p_node);
	int isBalancedHelper(node*& p_node);
	void printInTreeFormHelper(node*& p_node);
	void printTestOrderHelper(node*& p_node);
};

template<class T>
BSTree<T>::BSTree(){
	root = 0;
	num_elements = 0;
	left_height = 0;
	right_height = 0;
	num_interior = 0.0;
	num_leaf = 0.0;
}

template<class T>
bool BSTree<T>::search(const T& d){								
	return searchHelper(d, root);
}

template<class T>
bool BSTree<T>::searchHelper(const T& d, node*& p_node){		
	if(p_node == 0){
		return false;
	}
	else if(d == p_node->data){
		return true;
	}
	else if(d < p_node->data){
		return searchHelper(d, p_node->left);
	}
	else
		return searchHelper(d, p_node->right);
}

template<class T>
bool BSTree<T>::remove(const T& d){		
	return removeHelper(root, d);
}

template<class T>
bool BSTree<T>::removeHelper(node*& p_node, const T& d){	
	if (p_node==0){
		return false;   
	}
	if (d < p_node->data){
		removeHelper(p_node->left, d);
	}
	else if (d > p_node->data){
		removeHelper(p_node->right, d);
	}
	else{
		node* temp;
		if (p_node->left==0){
			temp = p_node->right;
			delete p_node;
			p_node = temp;
		}
		else if (p_node->right==0){

			temp = p_node->left;
			delete p_node;
			p_node = temp;
		}
		else {  
			temp = p_node->right;
			while(temp->left!=0){
				temp = temp->left;
			}
			p_node->data = temp->data;
			removeHelper(p_node->right,temp->data); 
		}
	}
	num_elements--;
	return true;
}

template<class T>
void BSTree<T>::insert(const T& d){
	insertHelper(d, root);
	num_elements++;
}

template<class T>
void BSTree<T>::insertHelper(const T& d, node*& p_node){
	if(p_node == 0){
		p_node = new node;
		p_node->data = d;
		p_node->left = 0;
		p_node->right = 0;
	}
	else if(d <= p_node->data){
		insertHelper(d, p_node->left);
		if(getHeightDifference() == 1 && num_elements > 2)
			balanceLeftLeft();
		/*else if(getHeightDifference() == -1 && num_elements > 2)
			balanceLeftRight();		
	*/}
	else if(d > p_node->data){
		insertHelper(d, p_node->right);
		if(getHeightDifference() == -1 && num_elements > 2)
			balanceRightRight();
		/*else if(getHeightDifference() == 1 && num_elements > 2)
			balanceRightLeft();*/
	}
}

template<class T>
int BSTree<T>::size(){
	return num_elements;
}

template<class T>
void BSTree<T>::printTestOrder(){
	cout<<root->data<<endl;
}

template<class T>
void BSTree<T>::printInOrder(){
	inOrderHelper(root);
}

template<class T>
void BSTree<T>::inOrderHelper(node*& p_node){
	if(p_node != 0){
		inOrderHelper(p_node->left);
		cout<<p_node->data<<endl;
		inOrderHelper(p_node->right);
	}
}

template<class T>
void BSTree<T>::printPreOrder(){
	preOrderHelper(root);
}

template<class T>
void BSTree<T>::preOrderHelper(node*& p_node){
	if(p_node != 0){
		cout<<p_node->data<<endl;
		preOrderHelper(p_node->left);
		preOrderHelper(p_node->right);
	}
}

template<class T>
void BSTree<T>::printPostOrder(){
	postOrderHelper(root);
}

template<class T>
void BSTree<T>::postOrderHelper(node*& p_node){
	if(p_node != 0){
		postOrderHelper(p_node->left);
		postOrderHelper(p_node->right);
		cout<<p_node->data<<endl;
	}
}

template<class T>
T BSTree<T>::findMax(){
	node* temp = root;
	while(temp->right != 0)
		temp = temp->right;
	return temp->data;		
}

template<class T>
T BSTree<T>::findMin(){
	node* temp = root;
	while(temp->left != 0)
		temp = temp->left;
	return temp->data;	
}

template<class T>
int BSTree<T>::heightOfTree(){	
	return heightOfTreeHelper(root);
}

template<class T>
int BSTree<T>::heightOfTreeHelper(node*& p_node){		// working
	if(p_node == 0)
		return 0;
	else{
		left_height = heightOfTreeHelper(p_node->left);
		right_height = heightOfTreeHelper(p_node->right);
		if(left_height > right_height)
			return left_height+1;
		else
			return right_height+1;
	}
}

template<class T>
double BSTree<T>::percentLeaf(){		// working
	num_interior = 0.0;
	num_leaf = 0.0;
	percentHelper(root);
	return num_leaf/num_elements*100;
}

template<class T>
double BSTree<T>::percentInterior(){	// working
	num_interior = 0.0;
	num_leaf = 0.0;
	percentHelper(root);
	return num_interior/num_elements*100;
}

template<class T>
void BSTree<T>::percentHelper(node*& p_node){	// working
	if(p_node != 0){
		if(p_node->right == 0 && p_node->left == 0)
			num_leaf++;
		else
			num_interior++;
		percentHelper(p_node->left);
		percentHelper(p_node->right);
	}	
}

template<class T>
int BSTree<T>::getHeightDifference(){
	int x = getHeightDifferenceHelper(root);
	if(x < -1)
		return getHeightDifferenceHelper(root->right);
	else if (x > 1)
		return getHeightDifferenceHelper(root->left);
}

template<class T>
int BSTree<T>::getHeightDifferenceHelper(node*& p_node){
	return heightOfTreeHelper(p_node->left)-heightOfTreeHelper(p_node->right);	
}

template<class T>
void BSTree<T>::balanceLeftLeft(){
	node* temp = root->left;
	root->left = temp->right;
	temp->right = root;
	root = temp;
}

template<class T>
void BSTree<T>::balanceLeftRight(){
	node* temp = root->left;
	node* temp2 = temp->right;
	temp->right=temp2->left;
	temp2->left = temp;
	root->left = temp2;
	balanceLeftLeft();	
}

template<class T>
void BSTree<T>::balanceRightLeft(){
	node* temp = root->right;
	node* temp2 = temp->right;
	temp->left=temp2->right;
	temp2->right=temp;
	root->right=temp2;
	balanceRightRight();
}

template<class T>
void BSTree<T>::balanceRightRight(){
	node* temp = root->right;
	root->right = temp->left;
	temp->left = root;
	root = temp;
}

template<class T>
void BSTree<T>::printInTreeForm(){
	int total_elem = 2;
	for(int i = 1; i < heightOfTree();i++){
		total_elem = total_elem * 2;
	}
	total_elem--;
	
	
	T *arr = new T[num_elements];
	int c = 0;	

	queue<node*> q;	
	q.push(root);
	while(!q.empty()){		
		arr[c] = q.front()->data;
		c++;
		if(q.front()->left != 0){			
				q.push(q.front()->left);
		}		
		if(q.front()->right != 0){			
				q.push(q.front()->right);
		}		
		q.pop();		
	}
	int exp = 2;
	int spaces_between_vals = 12;
	for(int i = 1; i< num_elements+1; i++){
		for(int j = 0; j <spaces_between_vals; j++){
			cout<<" ";
		}
		if(i == 1)
			cout<<"   ";
		cout<<arr[i-1];		
		if(i == (exp-1)){							
			cout<<endl;
			exp = exp*2;
			if(spaces_between_vals > 4)				
				spaces_between_vals -= 4;
		}
	}
	cout<<endl;
	delete [] arr;
}




