/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 *  Modified by: Qiao Zhang
 *  Date: 20160218
 */

#include "util.hpp"
#include "DictionaryTrie.hpp"
#include "limits.h"

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrieNode::DictionaryTrieNode(){
	isWord = false;
	freq = INT_MIN;
	max_freq = INT_MIN;
	for(int i = 0; i < 27; i++)
		children.push_back(NULL);
}

/* Destructor */
DictionaryTrieNode::~DictionaryTrieNode(){
	;
}

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){
	root = new DictionaryTrieNode;
	valid_node_count = 0;
	for(int i = 0; i < 26; i++){
		index[(char)('a'+i)] = i;
		letter[i] = 'a'+i;
	}
	index[' '] = 26;
	letter[26] = ' ';
}

/* print the subtree for debugging*/
void DictionaryTrie::print(){
	DictionaryTrieNode* p = root;
	std::queue<DictionaryTrieNode*> q;
	q.push(p);
	while(!q.empty()){
		p = q.front();
		q.pop();
		std::cout << p->freq << " " << p->max_freq << " " << p->isWord << std::endl;
		for(int i = 0; i < p->children.size(); i++){
			if(p->children[i])
				q.push(p->children[i]);
		}
	}
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
	if(word.length() == 0)
		return false;
	DictionaryTrieNode* p = root;
	for(int i = 0; i < word.length(); i++){
		if(((word[i] < 'a') || (word[i] > 'z')) && (word[i] != ' '))
			return false;
		if(p->children[index[(char)word[i]]] == NULL){
			p->children[index[(char)word[i]]] = new DictionaryTrieNode();
		}
		p = p->children[index[(char)word[i]]];
	}
	if(p->isWord)
		return false;
	p->isWord = true;
	p->freq = freq;
	p->max_freq = std::max(p->max_freq, (int)freq);
	valid_node_count++;
	
	/* update maximum frequency */
	p = root;
	for(int i = 0; i < word.length(); i++){
		p->max_freq = std::max(p->max_freq, (int)freq);
		p = p->children[index[(char)word[i]]];
	}
  return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
	if(word.length() == 0)
		return true;
	if(root == NULL)
		return false;
	std::unordered_map<char, int> index_tmp;
	for(int i = 0; i < 26; i++)
		index_tmp[(char)('a'+i)] = i;
	index_tmp[' '] = 26;
	DictionaryTrieNode* p = root;
	for(int i = 0; i < word.length(); i++){
		if(p->children[index_tmp[(char)word[i]]] == NULL)
			return false;
		p = p->children[index_tmp[(char)word[i]]];
	}
	return p->isWord;
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
	if(root == NULL)
		return words;
	if(num_completions <= 0)
		return words;
	if(prefix.length() == 0)
		return words;
	DictionaryTrieNode* p = root;
	for(int i = 0; i < prefix.length(); i++){
		if(((prefix[i] < 'a') || (prefix[i] > 'z')) && (prefix[i] != ' '))
			return words;
		if(p->children[index[(char)prefix[i]]] == NULL)
			return words;
		p = p->children[index[(char)prefix[i]]];
	}

	/* Breadth first search and prority queue for traversing and words maintainence*/
	std::priority_queue<std::pair<DictionaryTrieNode*, std::string>, std::vector<std::pair<DictionaryTrieNode*, std::string> >, TrieNodePairCompMin> completions;//min heap
	DictionaryTrieNode* subroot = p;
	std::priority_queue<std::pair<DictionaryTrieNode*, std::string>, std::vector<std::pair<DictionaryTrieNode*, std::string> >, TrieNodePairCompMax> bfs;//max heap
	std::pair<DictionaryTrieNode*, std::string> tmp(subroot, "");
	int min_freq = INT_MIN;
	bfs.push(tmp);
	while(!bfs.empty()){
		tmp = bfs.top();
		bfs.pop();
		if(tmp.first->isWord){
			if(completions.size() < num_completions){
				completions.push(tmp);
			}
			else{
			  min_freq = completions.top().first->freq;
			  if(tmp.first->freq > min_freq){
					completions.pop();
					completions.push(tmp);
					min_freq = completions.top().first->freq;
				}
			}
		}
		for(int i = 0; i < tmp.first->children.size(); i++){
			if(tmp.first->children[i] && (tmp.first->max_freq > min_freq)){
				std::pair<DictionaryTrieNode*, std::string> dummy(tmp.first->children[i], tmp.second + letter[i]);
				bfs.push(dummy);
			}
		}
	}

	while(!completions.empty()){
		words.push_back(prefix + completions.top().second);
		completions.pop();
	}
	reverse(words.begin(), words.end());
  return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){
	deleteAll(root);
}

/* Core for destructor */
void DictionaryTrie::deleteAll(DictionaryTrieNode* root){
	if(root == NULL)
		return ;
	for(int i = 0; i < root->children.size(); i++){
		deleteAll(root->children[i]);
	}
	delete root;
}
