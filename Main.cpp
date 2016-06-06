// ---
//
//Main file for Morse-tree applications
//Submitted by:
//Cody Wilson
//Nathanael Davidson
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
//#include "stdafx.h" //Useful depending on your project type
#include <iostream>
#include "MBinary_Tree.h"
#include "MBinary_Search_Tree.h"
#include "MTree_node.h"
#include <fstream>



using namespace std;

int main() {

	//****************************************************************************************************************
	//User input
	//Written by Cody Wilson
	// O(1)

	cout << "Written by Todd deFluiter, Nathanael Davidson and Cody Wilson\n";
		//Let the user know the purpose of the program
	cout << "The purpose of this program is to read a morse-code text document using 0's and 1's and write the corresponding message using a binary tree.\n\n\n";
	
		//Initialize key strings
	string input = "";
	string fileString = "";
	cout << "Please enter in the name of a file you would like to read, located in the project folder or press 1 to use the test file and hit enter.\n";
	cin >> input;
	
		//Allow for quick functionality or user-defined specific functionality
	if (input == "1")
		fileString = "morse_input.txt";
	else
		fileString = input;

	cout << "Here is what was input via the file: ";

	//*****************************************************************************************************************

		//Declartions of some file input necessities
	ifstream myReadFile;
	string line;
	char letter;
	string morse;
	
	Binary_Search_Tree* new_tree = new Binary_Search_Tree();	//This creates the tree.
	new_tree->insert("", NULL);									//This sets the root node to an empty node.


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
	//written by Todd deFluiter
	//assisted by both
	
	string line2;
	string temp_morse;
	ofstream ofile("out.txt");		//output file
	ifstream ifile(fileString);		//input file
	char inchar;
	if (ofile.is_open() & ifile.is_open()) {			//if openening succeded, start decoding
		while (getline(ifile, line2)) {					//read each line
			for (int i = 0; i < line2.length(); i++) {	//check each character
				inchar = (char)line2.at(i);
				cout << inchar;
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

	//**********************************************************************************************************************
	//Reading of output file to console window
	//Written by Cody Wilson with help from Nathanael Davidson's code and Stack Exchange (listed in MBinary_Search_Tree)

		//Let the user know what was written to file
	cout << "\nThis is the deciphered message and the contents of the output file: ";

		//This was the file that was just written
	myReadFile.open("out.txt");			
											
		//Read the file that was just written
	if (myReadFile.is_open()) {
		while (getline(myReadFile, line))
		{
			cout << line;
		}
	}
	else
			//Error check
		cout << "Files failed to write.\n";
	myReadFile.close();	

		//Nice for spacing 
	cout << endl;
	cout << endl;

		//Allow the user to see the decipher tree
	string option;
	cout << "Would you like to see a graphical representation of the tree? (Y/N)\n";
	cin >> option;

		//Logic for user input
	if (option == "Y")
	{
		cout << "Here is a sideways graphical representation of the beautiful tree: \n";

			//Print the tree
		new_tree->prettyPrint();
	}

	cout << endl;

	cout << "Please close the window to exit the program.";

		//Wait for the user to end the program before quitting
	while (1);
	//cout << "Search for 0: " << new_tree->search("0");

	return 0;
}