// ---
//Base node for Binary Tree 
//Cody Wilson
//5/27/2016
//Builds and runs
//
//
// ---

#pragma once
//#include "stdafx.h"
#include <iostream>
#include "MBinary_Tree.h"
#include "MBinary_Search_Tree.h"
#include "MTree_node.h"
#include <fstream>


using namespace std;

int main() {

	
	ifstream myReadFile;
	string line;
	vector<char> morse;
	char letter;
	int n;

	Binary_Search_Tree* new_tree = new Binary_Search_Tree();

	myReadFile.open("morse_key.txt"); //Change to your directory to work correctly (properties etc...)
	char output[1000];
	if (myReadFile.is_open()) {
		while (getline (myReadFile, line) )
		{
			cout << line << '/n'; //Read in functionality
			letter = (char)line.at(0);	
			
			n = 2;
			while (line.at(n) != '/n') {
				morse.push_back(line.at(n));
			}
			new_tree->insert(morse, letter);
			n = 0;
			morse.clear();
		}
	}
	myReadFile.close();

	char chars[100];
	char char1 = 'h';
	chars[0] = char1;

	for (int i = 0; i < 9; i++)
	{
		chars[i + 1] = chars[i] + 1;
	}

	//new_tree.insert('a');

	//new_tree.insert('z');

	//new_tree.insert('l');

	cout << new_tree << endl;
	
	//char location = new_tree.find(3);
	//cout << location;
	//cout << new_tree.find(3);

	new_tree->prettyPrint();
	cout << endl;

	return 0;
}