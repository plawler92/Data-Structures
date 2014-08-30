#include<iostream>
#include"BSTree.h"

using namespace std;

int main(){

	BSTree<int> t;	
	t.insert(5);
	t.insert(7);
	t.insert(6);
	t.insert(3);
	t.insert(4);
	t.insert(1);
	t.insert(10);
	t.printPreOrder();
	cout<<endl;
	t.printInOrder();
	cout<<endl;
	t.printPostOrder();
	cout<<endl;
	t.printInTreeForm();
	cout<<"Max: "<<t.findMax()<<endl<<"Min: "<<t.findMin()<<endl;
	cout<<"Percent Interior: "<<t.percentInterior()<<"%"<<endl;
	cout<<"Percent Leaf: "<<t.percentLeaf()<<"%"<<endl;
	cout<<"Tree has a height of: "<<t.heightOfTree()<<endl;
	t.remove(10);
	t.remove(5);
	t.printPreOrder();
	cout<<endl;
	t.printInOrder();
	cout<<endl;
	t.printPostOrder();
	cout<<endl;
	if(t.search(4))
		cout<<"value succesfully found"<<endl;
	else
		cout<<"val not found in tree"<<endl;
	if(t.search(10))
		cout<<"value succesfully found"<<endl;
	else
		cout<<"val not found in tree"<<endl;

	system("pause");
	return 0;
}

