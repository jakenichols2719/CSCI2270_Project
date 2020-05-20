/*
 * BSTree.h
 *
 *  Created on: Apr 22, 2020
 *      Author: jaken
 */

#ifndef BSTREE_H_
#define BSTREE_H_
#include <iostream>
#include <string>
#include <stdlib.h>

struct BSTNode {
public:
	int key;
	BSTNode* left = NULL;
	BSTNode* right = NULL;
};

class BSTree {
private:
	BSTNode* root = NULL;
public:
	BSTree();
	void insert(int key);
	BSTNode* search(int key);
	void displayList();
	virtual ~BSTree();
};

#endif /* BSTREE_H_ */
