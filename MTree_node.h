#pragma once
#include <sstream>
#include <string>
#include <vector>

using namespace std;

//This is the example Binary Tree Node from page 458.
//
struct Tree_node
{
	vector<char> morse_sequence;
	char letter;
	Tree_node* left;
	Tree_node* right;

	//Constructor
	Tree_node(const vector<char> the_morse,
		const char the_letter,
		Tree_node* left_val = NULL,
		Tree_node* right_val = NULL) : morse_sequence(the_morse), letter(the_letter), left(left_val), right(right_val)
	{ }

	//Deconstructor
	virtual ~Tree_node() { }

	//to-string
	virtual string to_string() const {
		ostringstream os;
		os << letter << " ";
		for (int i = 0; i < morse_sequence.size(); i++)
			os << morse_sequence[i];
		return os.str();
	}
};

//Overloading an ostream insertion operator
ostream& operator<<(ostream& out, const Tree_node& node)
{
	return out << node.to_string();
}


