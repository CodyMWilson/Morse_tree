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

	//cout << "Test cout\n";
	
	ifstream myReadFile;
	string line;
	char letter;
	string morse;
	
	Binary_Search_Tree* new_tree = new Binary_Search_Tree();	//This creates the tree.
	new_tree->insert("", NULL);									//This sets the root node to an empty node.

	//char output[1000];

	//******************************************************************************************************************
	//Create the decoding tree
	//Written by Nathanael Davidson
	//O(104)
	myReadFile.open("morse_key.txt");			//File contains a list of characters and their morse-code equivalents (0 represents a dot, 1 represents a dash)
												//Example: a 01
												//         b 1000
												//         . . .

	if (myReadFile.is_open()) {
		while (getline(myReadFile, line))
		{
			letter = (char)line.at(0);					//Character value = first character of each line
			for (int i = 2; i < line.size(); i++)
				morse.push_back(line.at(i));			//Morse code value = remaining contents of line after space
			new_tree->insert(morse, letter);			//Inserts values into the tree
			morse.clear();						//Clears morse string for next iteration of the loop
		}
	}
	myReadFile.close();		//Close morse key file


	/********************************************************************************************************************/
	//Decode and write to out.txt
	//writen by Todd deFluiter
	//assisted by both
	
	string line2;
	string temp_morse;
	ofstream ofile("out.txt");				//output file
	ifstream ifile("morse_input.txt");		//input file
	char inchar;
	if (ofile.is_open() & ifile.is_open()) {			//if openening succeded, start decoding
		while (getline(ifile, line2)) {					//read each line
			for (int i = 0; i < line2.length(); i++) {	//check each character
				inchar = (char)line2.at(i);
				if (inchar == '1' || inchar == '0') {	//prepare for decoding
					temp_morse.append(1, inchar);
				}
				if (inchar == '.') {
					ofile << new_tree->search(temp_morse);	//decode by character
					temp_morse = "";
				}
				if (inchar == ' ') {
					ofile << " ";
				}
			}
			ofile << "\n";									//end line
		}
		ifile.close();		//close things
		ofile.close();
	}
	else {
		cout << "files not found" << endl;
	}



	
	//new_tree->insert("001",'p', 0);
	cout << "Here is our beautiful tree:\n";

	new_tree->prettyPrint();		//Print out our beautiful tree

	cout << endl;

	//cout << "Search for 0: " << new_tree->search("0");

	return 0;
}