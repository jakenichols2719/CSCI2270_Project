/*
 * LinkedList.cpp
 *
 *  Created on: Apr 21, 2020
 *      Author: jaken
 */

#include "LinkedList.h"

LinkedList::LinkedList() {
	head = NULL;
}

void LinkedList::insert(int key) {
	LLNode* toInsert = new LLNode; toInsert->key = key;
	if(head == NULL) {
		head = toInsert;
		return;
	}

	LLNode* temp = head;
	while(temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = toInsert;
}

LLNode* LinkedList::search(int key) {
	if(head == NULL) {
		std::cout << "List is empty. Cannot search." << std::endl;
		return NULL;
	}
	LLNode* temp = head;
	while(temp != NULL) {
		if(temp->key == key) {
			return temp;
		}
		temp = temp->next;
	}
	std::cout << "Value not found." << std::endl;
	return NULL;
}

void LinkedList::displayList() {
	LLNode* temp = head;
	std::string fullList = "";
	int n = 0;
	while(temp != NULL) {
		std::cout << temp->key << " ";
		n++;
		if(n == 100) {
			//Eclipse IDE doesn't like me printing the list in one line.
			std::cout << std::endl;
			n = 0;
		}
		temp = temp->next;
	}
}

LinkedList::~LinkedList() {
	// TODO Auto-generated destructor stub
}

