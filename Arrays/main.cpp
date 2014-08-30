#include <iostream>
#include "SafeArray.h"
#include "SafeArrayOutOfBoundsException.h"


using namespace std;

int main(){


	SafeArray<int > s(10);	

	for(int i = 0; i < 20; i++){
		s[i] = i;
		cout<<s[i]<<endl;
	}

	SafeArray<int> s2(s);

	cout<<endl<<endl<<endl;

	for(int i = 0; i < s2.size(); i++){	
		cout<<s2[i]<<endl;
	}


	system("pause");
	return 0;
}