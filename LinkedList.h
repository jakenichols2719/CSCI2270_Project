/*
 * LinkedList.h
 *
 *  Created on: Apr 21, 2020
 *      Author: jaken
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>

struct LLNode {
public:
	int key;
	LLNode* next = NULL;
};

class LinkedList {
private:
	LLNode* head = NULL;
public:
	LinkedList();
	void insert(int key);
	LLNode* search(int key);
	void displayList();
	virtual ~LinkedList();
};

#endif /* LINKEDLIST_H_ */
