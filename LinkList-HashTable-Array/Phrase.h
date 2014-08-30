#pragma once
#include<string>

using namespace std;

class Phrase{
public:
	Phrase();
	Phrase(string english, string foreign);
	string getPhraseInEnglish();
	string getPhraseInForeign();
	bool operator==(string p);
	void print();
	

private:
	string english_word;
	string foreign_word;
};

Phrase::Phrase(){

}

Phrase::Phrase(string english, string foreign){
	english_word = english;
	foreign_word = foreign;
}

string Phrase::getPhraseInEnglish(){
	return english_word;
}

string Phrase::getPhraseInForeign(){
	return foreign_word;
}

bool Phrase::operator==(string p){
	return getPhraseInEnglish() == p;
}

void Phrase::print(){
	cout<<english_word<<" "<<foreign_word<<endl;
}




