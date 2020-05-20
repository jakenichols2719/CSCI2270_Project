/*
 * HashTable.h
 *
 *  Created on: Apr 22, 2020
 *      Author: jaken
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <string>
#include <iostream>
#include <stdlib.h>

struct HTNode {
	int key;
	HTNode* next = NULL;
};

class HashTable {
private:
	int NUM_BUCKETS = 40009;
	int collisions = 0;
	HTNode** table; //array of HTNode pointers
	unsigned hashFunction(int key);
	void resolve_chain(HTNode* newNode, unsigned index);
	void resolve_linear(HTNode* newNode, unsigned index);
	void resolve_quadratic(HTNode* newNode, unsigned index);
public:
	HashTable();
	void insert(int key); //auto-resolves with chaining
	void insert(int key, std::string resolution); //pick collision method
	HTNode* search(int key, std::string mode);
	void displayTable();
	virtual ~HashTable();
};

#endif /* HASHTABLE_H_ */
