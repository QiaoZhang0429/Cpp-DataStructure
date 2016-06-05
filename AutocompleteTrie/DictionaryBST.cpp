/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 *  Modified by: Qiao Zhang
 *  Date: 20160218
 */
 
#include "util.hpp"
#include "DictionaryBST.hpp"
#include <set>

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
	return dict.insert(word).second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
	return dict.find(word) != dict.end();
}

/* Destructor */
DictionaryBST::~DictionaryBST(){}
