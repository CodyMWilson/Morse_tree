// ---
//
//Main file for More-tree applications
//Submitted by:
//Cody Wilson
//Nathaniel Davidson
//Todd Defluiter
//6/6/2016
//
//The purpose of this program is to input a file of morse code and it's corresponding letter and write the 
// message to a file output. 
//Code was worked on collaboratively, based on example code from chapter 8 of Objects, Data Structures and 
// Design using C++ by Elliot Koffman and Paul Wolfgang.
//Specific code referenced from p. 457 - 479 and online at http://bcs.wiley.com/he-bcs/Books?action=resource&bcsId=2949&itemId=0471467553&resourceId=7105&chapterId=21532
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

	cout << "Test cout\n";
	
	ifstream myReadFile;
	string line;
	char letter;
	string morse;
	
	Binary_Search_Tree* new_tree = new Binary_Search_Tree();
	new_tree->insert("", NULL);

	myReadFile.open("morse_key2.txt"); //Change to your directory to work correctly (properties etc...)
	char output[1000];
	if (myReadFile.is_open()) {
		while (getline(myReadFile, line))
		{
			cout << line << endl; //Read in functionality
			letter = (char)line.at(0);
			for (int i = 2; i < line.size(); i++)
				morse.push_back(line.at(i));
			new_tree->insert(morse, letter);
			morse.clear();
		}
	}
	myReadFile.close();
	
	string line2;
	string temp_morse;
	ofstream ofile("out.txt");
	ifstream ifile("morse_input.txt");
	char inchar;
	if (ofile.is_open() & ifile.is_open()) {
		while (getline(ifile, line2)) {
			for (int i = 0; i < line2.length(); i++) {
				inchar = (char)line2.at(i);
				if (inchar == '1' || inchar == '0') {
					temp_morse.append(1, inchar);
				}
				if (inchar == '.') {
					ofile << new_tree->search(temp_morse);
					temp_morse = "";
				}
				if (inchar == ' ') {
					ofile << " ";
				}
			}
			ofile << "\n";
		}
		ifile.close();
		ofile.close();
	}
	else {
		cout << "files not found" << endl;
	}



	
	//new_tree->insert("001",'p', 0);

	new_tree->prettyPrint();

	cout << endl;

	cout << "Search for 0: " << new_tree->search("0");

	return 0;
}