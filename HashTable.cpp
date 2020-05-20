/*
 * HashTable.cpp
 *
 *  Created on: Apr 22, 2020
 *      Author: jaken
 */

#include "HashTable.h"

unsigned HashTable::hashFunction(int key) {
	return key % NUM_BUCKETS;
}

void HashTable::resolve_chain(HTNode* newNode, unsigned index) {
	//std::cout << "chain resolution " << index << std::endl;
	collisions++;
	HTNode* temp = table[index];
	while(true) {
		if(temp->next == NULL) {
			temp->next = newNode;
			break;
		}
		else {
			temp = temp->next;
		}
	}
}

void HashTable::resolve_linear(HTNode* newNode, unsigned index) {
	collisions++;
	//std::cout << "linear resolution " << index << std::endl;
	while(true) {
		index++;
		if(index == unsigned(NUM_BUCKETS)) {
			index = 0;
		}
		if(table[index] == NULL) {
			table[index] = newNode;
			break;
		}
	}
}

void HashTable::resolve_quadratic(HTNode* newNode, unsigned index) {
	collisions++;
	int i = 1;
	while(true) {
		index += i + (i^2);
		if(index >= unsigned(NUM_BUCKETS)) {
			index -= NUM_BUCKETS;
		}
		if(table[index] == NULL) {
			table[index] = newNode;
			break;
		}
		i++;
	}
}

HashTable::HashTable() {
	table = new HTNode*[NUM_BUCKETS];
	for(int n=0; n<NUM_BUCKETS; n++) {
		table[n] = NULL;
	}
}

void HashTable::insert(int key) {
	unsigned index = hashFunction(key);
	HTNode* newItem = new HTNode; newItem->key = key;
	if(table[index] == NULL) {
		table[index] = newItem;
	}
	else {
		resolve_chain(newItem, index);
	}
}

void HashTable::insert(int key, std::string resolution) {
	unsigned index = hashFunction(key);
	HTNode* newItem = new HTNode; newItem->key = key;
	if(table[index] == NULL) {
		table[index] = newItem;
	}
	else {
		if(resolution == "chain") {
			resolve_chain(newItem, index);
			return;
		}
		if(resolution == "linear") {
			resolve_linear(newItem, index);
			return;
		}
		if(resolution == "quadratic") {
			resolve_quadratic(newItem, index);
			return;
		}
		std::cout << "Invalid resolution type." << std::endl;
		return;
	}
}

HTNode* HashTable::search(int key, std::string mode = "chain") {
	//search mode for a hash table with chain collision resolution
	if(mode == "chain") {
		unsigned index = hashFunction(key);
		if(table[index] == NULL) {
			std::cout << "Table does not contain this value." << std::endl;
			return NULL;
		}
		//jump to location; if keys don't match, check attached chain
		HTNode* temp = table[index];
		while(temp != NULL) {
			if(temp->key == key) {
				return temp;
			}
			else {
				temp = temp->next;
			}
		}
		std::cout << "Table does not contain this value." << std::endl;
		return NULL;
	}
	//for linear collision resolution
	if(mode == "linear") {
		unsigned index = hashFunction(key);
		if(table[index] == NULL) {
			std::cout << "Table does not contain this value." << std::endl;
			return NULL;
		}
		//crawl indices until located correct value.
		//null values shouldn't be an issue here.
		HTNode* temp;
		while(temp != NULL) {
			temp = table[index];
			if(temp->key == key) {
				return temp;
			}
			else {
				index++;
			}
		}
		std::cout << "Table does not contain this value." << std::endl;
		return NULL;
	}
	//for quadratic resolution
	if(mode == "quadratic") {
		unsigned index = hashFunction(key);
		if(table[index] == NULL) {
			std::cout << "Table does not contain this value." << std::endl;
			return NULL;
		}
		//jump indices until located correct value.
		HTNode* temp;
		int i = 1;
		while(temp != NULL) {
			temp = table[index];
			if(temp->key == key) {
				return temp;
			}
			else {
				index += i + (i^2);
				i++;
			}
		}
		std::cout << "Table does not contain this value." << std::endl;
		return NULL;
	}

	return NULL;
}

void HashTable::displayTable() {
	for(int n=0; n<NUM_BUCKETS; n++) {
		HTNode* temp = table[n];
		while(temp != NULL) {
			std::cout << n << ": ";
			std::cout << temp->key << std::endl;
			temp = temp->next;
		}
	}
	std::cout << std::endl;
}

HashTable::~HashTable() {
	// TODO Auto-generated destructor stub
}

