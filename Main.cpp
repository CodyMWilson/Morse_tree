// ---
//Base node for Binary Tree 
//Cody Wilson
//5/27/2016
//Builds and runs
//
//
// ---

#pragma once
#include "stdafx.h"
#include <iostream>
#include "Tree_node.h"
#include "Binary_Tree.h"
#include "Binary_Search_Tree.h"
#include "BST_insert.h"

using namespace std;

int main() {

	char chars[100];
	char char1 = 'h';
	chars[0] = char1;

	for (int i = 0; i < 9; i++)
	{
		chars[i + 1] = chars[i] + 1;
	}

	Binary_Search_Tree<char> new_tree;

	for (int i = 9; i > 0; i--)
	{
		new_tree.insert(chars[i]);
		new_tree.insert(chars[i] - 1);
	}
	
	new_tree.insert('a');
	new_tree.insert('b');

	//new_tree.insert('a');

	//new_tree.insert('z');

	//new_tree.insert('l');

	cout << new_tree << endl;
	
	//char location = new_tree.find(3);
	//cout << location;
	//cout << new_tree.find(3);

	new_tree.prettyPrint();
	cout << endl;

	const char* p;
	p = new_tree.find('k');

	cout << *p;

	return 0;
}