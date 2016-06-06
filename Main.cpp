// ---
//
//Main file for Morse-tree applications
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
//#include "stdafx.h" //Useful depending on your project type
#include <iostream>
#include "MBinary_Tree.h"
#include "MBinary_Search_Tree.h"
#include "MTree_node.h"
#include <fstream>
#include <exception>



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

	cout << "\nHere is what was input via the file: ";

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
	//Written by Cody Wilson with help from Nathaniel Davidson's code and Stack Exchange (listed in MBinary_Search_Tree)

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
	cout << "Would you like to see a graphical representation of the decipher tree? (Y/N)\n";
	cin >> option;

		//Logic for user input
	if (option == "Y")
	{
		cout << "Here is a sideways graphical representation of the beautiful decipher tree: \n";

			//Print the tree
		new_tree->prettyPrint();
	}

	cout << endl;

	//****************************************************************************************************
	//Atbash cipher functionality
	//Written by Cody Wilson with heavy references to code worked on by everyone
	//Stretch goal = slightly buggy but mostly functional
	//O(n*p) on input where n is the number of characters in the file and p is the number of lines
	//O(n) on output where n is the number of characters in the file

	bool moveForward = false;
	string option2;
	while (moveForward == false) {
		cout << "Would you like to decipher or cipher an atbash code? The same cipher process is used to decipher. (Y/close window/What)\n";
		cout << "Close the window if you wish to exit the program.";
		cin >> option2;
		cout << endl;
		cout << endl;

		if (option2 == "What" || option2 == "what")
		{
			cout << "An Atbash cipher is a cipher in which the letters of any alphabet are replaced by letters that are their corresponding distance away from the center of the respective alphabet.\n";
			cout << "For example, a would be z in an Atbash cipher.\n";
			cout << endl;
			cout << endl;
		}
		if (option2 == "Y")
		{
			moveForward = true;
		}
	}

		//Initialize key strings
		string input2 = "";
		string fileString2 = "";
		cout << "Please enter in the name of a text file you would like to read, located in the project folder or press 1 to use the test file and hit enter. Note that only lower case can be currently used.\n";
		cin >> input2;

		//Allow for quick functionality or user-defined specific functionality
		if (input2 == "1")
			fileString2 = "atbash_input.txt";
		else
			fileString2 = input2;

		cout << "Here is what was input via the atbash file: ";
		try {
			//Actual input taken from functionality of morse-code input and tweaked for functionality
			string line3;
			string temp_atbash;
			ofstream ofile2("atbash_out.txt");		//output file
			ifstream ifile2(fileString2);			//input file
			char inchar2;
			if (ofile2.is_open() & ifile2.is_open()) {			//if openening succeded, start decoding
				while (getline(ifile2, line3)) {				//read each line
					for (int i = 0; i < line3.length(); i++) {	//check each character
						inchar2 = (char)line3.at(i);
						cout << inchar2;
						if (int(inchar2) >= 97 || int(inchar2) <= 122)	//prepare for decoding
						{
							char decoded_atbash;

							//Decodes the cipher
							//Below is a walkthrough of how the math works
							//Does not use a tree, but in the same spirit of the rest of the program
							//Note: There is a character output at the end of each word that needs debugging
							//Functional, tested and works
							//int(inchar2) - 97) casts the ascii character to an integer and normalizes it to a = 0, b = 1 etc...
							// 13 - (previous) finds the distance away from the middle of the alpahbet (26 - 13)
							// 13 + (previous) - 1 simply takes and mirrors the distance from the center of the alphabet. The minus one is for calibration.
							//  Thus, 'a' becomes 'x' as distance 13 away from the center of the alphabet 
							//char(97 + previous)  un-normalizes the text to maintain location in the ascii alphabet
							decoded_atbash = char(97 + 13 + (13 - (int(inchar2) - 97)) - 1); //Normalizes and decodes the cipher

							ofile2 << decoded_atbash; //writes to file
						}

						if (inchar2 == ' ') {
							ofile2 << " ";
						}
							//Works but breaks semi-functionality
							//Needs debugging
						else
						{ /*throw out_of_range("This input is not a lowercase character."); */}
					}
					ofile2 << "\n"; //end line
				}
				ifile2.close();		//close things
				ofile2.close();
			}
			else {
				cout << "files not found" << endl;
			}

			//Let the user know what was written to file
			cout << "\nThis is the deciphered atbash message and the contents of the output file: ";

			//This was the file that was just written
			myReadFile.open("atbash_out.txt");

			//Read the file that was just written
			if (myReadFile.is_open()) {
				while (getline(myReadFile, line))
				{
					cout << line;
				}
			}
			else {
				cout << "files not found" << endl;
			}
		}
			//Works too well, there's a bug that I need to fix before this will work correctly
		catch (out_of_range& e1)
		{
			cerr << e1.what() << endl;
		}
		//End of atbash cipher functionality
		//****************************************************************************************

			cout << "\n\nPlease close the window to exit the program.";


		while (1);



	return 0;
}