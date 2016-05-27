// ---
//Base node for Binary Tree 
//Cody Wilson
//5/27/2016
//Builds and runs
//
//
// ---


#include "stdafx.h"
#include <sstream>

using namespace std;

		//This is the example Binary Tree Node from page 458.
	template<typename Item_Type>
	struct Tree_node
	{
		Item_Type data;
		Tree_node<Item_Type>* left;
		Tree_node<Item_Type>* right;

		//Constructor
		Tree_node(const Item_Type& the_data,
			Tree_node<Item_Type>* left_val = NULL,
			Tree_node<Item_Type>* right_val = NULL) : data(the_data), left(left_val), right(right_val) 
		{ }

		//Deconstructor
		virtual ~Tree_node() { }

		//to-string
		virtual string to_string() const {
			ostringstream os
				os << data;
			return os.str();
		}
	};

	//Overloading an ostream insertion operator
	template<typename Item_Type>
	ostream& operator<<(ostream& out, const Tree_node <Item_Type>& node)
	{
		return out << node.to_string();
	}

int main() {


	return 0;
}