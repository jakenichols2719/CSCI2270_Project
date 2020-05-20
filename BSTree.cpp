/*
 * BSTree.cpp
 *
 *  Created on: Apr 22, 2020
 *      Author: jaken
 */

#include "BSTree.h"

BSTree::BSTree() {
	root = NULL;
}

//inserts a value into binary search tree
void BSTree::insert(int key) {
	//create new node
	BSTNode* newNode = new BSTNode; newNode->key = key;
	if(root == NULL) { //set root to new node if no previous root existed
		root = newNode;
		return;
	}

	BSTNode* temp = root;
	int path_len = 0;
	while(true) {
		if(key < temp->key) { //left check
			//if there is nothing to the left, insert the new node
			if(temp->left == NULL) {
				temp->left = newNode;
				break;
			}
			//otherwise move to the left
			else {
				temp = temp->left;
				path_len++;
			}
		}
		if(key >= temp->key) { //right check
			//if there is nothing to the right, insert the new node
			if(temp->right == NULL) {
				temp->right = newNode;
				break;
			}
			//otherwise move to the right
			else {
				temp = temp->right;
				path_len++;
			}
		}
	}
	//path_len for debugging
	//std::cout << path_len << std::endl;
}

//search for a value in the tree
//returns the first node found with the given key, or NULL if none is found
BSTNode* BSTree::search(int key) {
	//empty case
	if(root == NULL) {
		std::cout << "Tree is empty. Cannot search." << std::endl;
		return NULL;
	}
	BSTNode* temp = root;
	while(true) {
		//found
		if(temp != NULL && key == temp->key) {
			return temp;
		}
		//not found; move left
		if(temp != NULL && key < temp->key) {
			temp = temp->left;
		}
		//not found; move right
		if(temp != NULL && key > temp->key) {
			temp = temp->right;
		}
		//tree exhausted; value not found
		if(temp == NULL) {
			std::cout << "Value not found in tree." << std::endl;
			return NULL;
		}
	}
}

//display tree utility function
void displayUtil(BSTNode* b) {
	if(b->left != NULL) displayUtil(b->left);
	std::cout << b->key << " ";
	if(b->right != NULL) displayUtil(b->right);
}
//displays tree with depth first; sorted by nature of BST
void BSTree::displayList() {
	displayUtil(root);
	std::cout << std::endl;
}

BSTree::~BSTree() {
	// TODO Auto-generated destructor stub
}

