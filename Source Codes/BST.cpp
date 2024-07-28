﻿#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"
#include <string>


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

// extra function added

//(b)
bool BST::deepestNodes()
{
	if (empty())//check empty or not
	{
		cout << "The tree is empty!" << endl;
		return false;
	}
	else
	{
		cout << finddeepestNodes(root) << endl;
		return true;
	}
}

int BST::finddeepestNodes(BTNode* cur)
// using level method
{
	int level = -1, maxLevel = 0; 
	int result;
	finddeepestNodes2(cur, level, maxLevel, &result);
	return result;
}

void BST::finddeepestNodes2(BTNode* cur, int level, int& maxLevel, int* result)
{
	if (cur != NULL)// find deepest nodes
	{
		finddeepestNodes2(cur->left, ++level, maxLevel, result);
		if (level > maxLevel)
		{
			*result = cur->item.id;
			maxLevel = level;
		}
		finddeepestNodes2(cur->right, level, maxLevel, result);
	}
}


//(c)
bool BST::display(int order, int source) {
	// check empty or not
	if (root == NULL) {
		cout << "BST is empty ! "<<endl;
		return false;
	}
	// print file
	if (source == 2) 
	{
		
		ofstream outputFile("student_info.txt");
		if (outputFile.fail()) 

		{
			cout << "Cannot open it!!" << endl;
			return false;

		}
		if (order == 1)
		{
		
			displayToFileAscending(root, outputFile);
			cout << "Insert Successfully ! " << endl;

			
		}
	    if (order == 2) 
		{

			displayToFileDescending(root, outputFile);
			cout << "Insert Successfully ! " << endl;

		}
		

		outputFile.close();
	}

	else if(source == 1) 
	{
		if (order == 1) {
			displayAscending(root);
		}
		else if (order == 2) {
			displayDescending(root);
		}
	}
	
	return true;
}

void BST::displayAscending(BTNode* cur) {
	if (cur == NULL) return;
	//display ascending
	displayAscending(cur->left);
	cur->item.print(cout);
	displayAscending(cur->right);


}

void BST::displayDescending(BTNode* cur) {
	if (cur == NULL) return;
	//display descending
	displayDescending(cur->right);
	cur->item.print(cout);
	displayDescending(cur->left);

}

void BST::displayToFileAscending(BTNode* cur, ostream& output) {
	if (cur == NULL) return;


	displayToFileAscending(cur->left, output);
	cur->item.print(output);
	displayToFileAscending(cur->right, output);


}

void BST::displayToFileDescending(BTNode* cur, ostream& output) {
	if (cur == NULL) return;


	displayToFileDescending(cur->right, output);
	cur->item.print(output);
	displayToFileDescending(cur->left, output);


}


//(d)
bool BST::cloneSubtree(BST t1, type item) {
	// check empty
	if (t1.empty()) {
		cout << "Cannot clone subtree." << endl;
		cout << endl;
		cout<< "The tree is empty !!!" << endl;
		return false;
	}

	BTNode* node = NULL;
	// find nodes
	if (!t1.findNode(t1.root, item, node)) {
		cout << "Cannot clone subtree." << endl;
		cout << endl;
		cout << "Item not found in the tree !!!" << endl;
		return false;
	}

	BST t2;
	cloneSubtree2(node, t2);
	cout << endl;
	cout << "------------------------------------------------------------------------------------------" << endl;
	cout << "Tree t1 after function call (pre-order traversal): ";
	cout << endl;
	t1.preOrderPrint();
	cout << endl;
	cout << endl;
	cout << "------------------------------------------------------------------------------------------" << endl;
	cout << "Tree t2 after cloning subtree (pre-order traversal): ";
	cout << endl;
	t2.preOrderPrint();

	return true;
}

bool BST::findNode(BTNode* cur, type item, BTNode*& resultNode) {
	if (cur == NULL) {
		return false;
	}

	if (cur->item.compare2(item)) {
		resultNode = cur;
		return true;
	}

	if (findNode(cur->left, item, resultNode)) {
		return true;
	}

	return findNode(cur->right, item, resultNode);
}

void BST::cloneSubtree2(BTNode* node, BST& t2) {
	if (node == NULL) {
		return;
	}

	// insert t2
	t2.insert(node->item);

	
	cloneSubtree2(node->left, t2);
	cloneSubtree2(node->right, t2);
}


//(e)
bool BST::printLevelNodes() {
	// check empty
	if (empty()) {
		cout << "Empty tree!" << endl;
		return false;
	}
	
	printLevelNodes2();

	return true;
}

void BST::printLevelNodes2() {

	Queue q;

	if (empty()) return; 

	
	q.enqueue(root); 

	int level = 1; 

	while (!q.empty()) {

		int size = q.size(); 
		cout << "Level " << level << " nodes: ";

		
		for (int i = 0; i < size; ++i) {
			BTNode* cur;
			q.dequeue(cur);

			
			cout << cur->item.id << " ";

			
			if (cur->left != NULL)
				q.enqueue(cur->left);
			if (cur->right != NULL)
				q.enqueue(cur->right);
		}

		cout << endl;
		level++;
	}
}



//(f)
bool BST::printPath() {
	//check empty
	if (empty()) {
		cout << "Empty tree!" << endl;
		return false;
	}

	cout << "Below are all the external paths for the tree:" << endl;
	cout << endl;
	// print
	printExternalPaths(root, "");

	return true;
}

void BST::printExternalPaths(BTNode* cur, string path) {
	if (cur == NULL) 
		return;

	// check both side null or not
	if (cur->left == NULL && cur->right == NULL) {
		cout << path  << " " << cur->item.id << endl;
	}
	else {
		
		if (cur->left != NULL) {
			printExternalPaths(cur->left, path + " " + to_string(cur->item.id));
		}
		if (cur->right != NULL) {
			printExternalPaths(cur->right, path + " " + to_string(cur->item.id));
		}
	}
}


