#include<iostream>
#include"HashTable.h"
#include<fstream>
#include"Phrase.h"
#include"string"
#include"LinkList.h"
#include"Phrase.h"
using namespace std;

int doublePrime(int x);

int main(){

	ifstream text_phrases;
	string phrase;
	string phrase2;	
	int x = 1000;
	x = doublePrime(x);
	HashTable<Phrase> phrases(x);

	text_phrases.open("1000phrases.txt");
	while(!text_phrases.eof()){
		text_phrases>>phrase;
		text_phrases>>phrase2;
		text_phrases>>phrase2;
		Phrase p(phrase, phrase2);
		phrases.insert(phrase, p);					
	}
	phrases.printCollisionInfo();

	cout<<"Enter a word to translate: ";
	string word;
	cin>>word;
	Phrase trans;
	phrases.retrieve(word, trans);
	cout<<"The translation is "<<trans.getPhraseInForeign()<<endl;
	

	
	
	


	
	

	
	system("pause");
	return 0;
}

int doublePrime(int orig_size){
	int x = orig_size;
	x = x * 2;
	bool prime = false;
	while(true){
		for(int i = 2; i <x; i++){
			if(x%i == 0){				
				break;
			}
			else if(i == x-1){
				prime = true;
			}				
		}
		if(prime == true)
		{
			break;
		}
		else
			x++;
	}
	return x;
}  //working