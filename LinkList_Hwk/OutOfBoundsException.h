#pragma once

using namespace std;

class OutOfBoundsException{
public:
	void what();
};

void OutOfBoundsException::what(){
	cout<<"The position entered attempts to access a node that does not exist."<<endl;
	system("pause");
	exit(0);
}