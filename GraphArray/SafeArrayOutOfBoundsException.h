#pragma once

using namespace std;

class SafeArrayOutOfBoundsException{
public:
	void what();
};

void SafeArrayOutOfBoundsException::what(){
	cout<<"Array pointer is out of bounds."<<endl;
	system("pause");
	exit(0);
}