#include <iostream>
#include "OrdLinkedList.h"

using namespace std;

int main(){
	OrdLinkedList<int> l;
	l.insert(1);
	l.insert(2);
	l.insert(3);
	l.insert(4);
	l.insert(10);

	l.remove(3);
	l.remove(10);
	l.print();


	l.insert(7);
	l.insert(3);

	l.print();
	
	int x = 0;

	l.next(x);
	cout<<x<<endl;

	l.next(x);
	l.next(x);
	cout<<x<<endl;

	l.previous(x);
	cout<<x<<endl;
	cout<<l[4]<<endl;

	


	
	
	



	system("pause");
	return 0;
}