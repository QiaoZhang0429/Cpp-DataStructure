#include <iostream>
#include <fstream>
#include "DictionaryTrie.hpp"
#include "DictionaryBST.hpp"
#include "DictionaryHashtable.hpp"
#include "util.hpp"
using namespace std;

int main(){
	/* test case 1*/
	/*
	DictionaryTrie dict;
	cout<<dict.insert("hello",5)<<endl;
	cout<<dict.insert("hell",1)<<endl;
	cout<<dict.insert("and",10)<<endl;
	cout<<dict.insert("dog",15)<<endl;
	cout<<dict.insert("alphabet",3)<<endl;
	cout<<dict.insert("world",4)<<endl;
	cout<<dict.find("and")<<endl;
	cout<<dict.find("dog")<<endl;
	cout<<dict.find("hel")<<endl;
	cout<<dict.find("g")<<endl;
	//dict.print();
	*/

	/* test case 2*/
	/*
	DictionaryBST dict;
	cout<<dict.insert("hello")<<endl;
	cout<<dict.insert("hell")<<endl;
	cout<<dict.insert("and")<<endl;
	cout<<dict.insert("dog")<<endl;
	cout<<dict.insert("alphabet")<<endl;
	cout<<dict.insert("world")<<endl;
	cout<<dict.find("and")<<endl;
	cout<<dict.find("dog")<<endl;
	cout<<dict.find("hel")<<endl;
	cout<<dict.find("hello")<<endl;
	cout<<dict.find("g")<<endl;
	*/

	/* test case 3*/
	/*
	DictionaryHashtable dict;
	cout<<dict.insert("hello")<<endl;
	cout<<dict.insert("hell")<<endl;
	cout<<dict.insert("and")<<endl;
	cout<<dict.insert("dog")<<endl;
	cout<<dict.insert("alphabet")<<endl;
	cout<<dict.insert("world")<<endl;
	cout<<dict.find("and")<<endl;
	cout<<dict.find("dog")<<endl;
	cout<<dict.find("hel")<<endl;
	cout<<dict.find("hello")<<endl;
	cout<<dict.find("g")<<endl;	
	*/

	/* test case 4*/
	DictionaryTrie dict;
	ifstream infile;
	infile.open("unique_freq_dict.txt");
	Utils::load_dict(dict, infile);
	infile.close();
	cout<<dict.find("and")<<endl;
	cout<<dict.find("dog")<<endl;
	cout<<dict.find("hel")<<endl;
	cout<<dict.find("g")<<endl;
	cout<<dict.valid_node_count<<endl;
	vector<string> word = dict.predictCompletions("man", 10);
	for(int i = 0; i < word.size(); i++)
		cout<<word[i]<<endl;
		
	return 0;
}