#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
 
#include "MBinary_Tree.h"
#include "MTree_node.h"
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <typeinfo>

//Main code for binary tree implemented by Cody Wilson from book source code

/** Definition of the Binary Search Tree class. 
    @param Item_Type The type of item to be stored in the tree
    Note: Item_Type must define the less-than operator as a 
    total order.
*/

  class Binary_Search_Tree : public Binary_Tree
{
  public:
  // Constructor
  /** Construct an empty Binary_Search_Tree */
  Binary_Search_Tree() : Binary_Tree() {}

  // Public Member Functions
  /** Insert an item into the tree. 
      post: The item is in the tree.
      @param item The item to be inserted
      @return true if the item was not already
              in the tree, false otherwise
  */
  virtual bool insert(const string& the_morse, const char& the_letter);

  /** Remove an item from the tree. 
      post: The item is no longer in the tree.
      @param item The item to be removed
      @return true if the item was in the tree,
              false otherwise
  */
  //virtual bool erase(const string& the_morse);


  /** Determine whether an item is in the tree.
      @param item The item sought
      @return A const pointer to the item if in the
              tree, or NULL if not
  */
  virtual const char search(const string& target) const;

  //Used to find the node with the data that we are seeking
  //virtual const void search_Branch(const string& target, string branch) const;
 
  //Functions found online
  void prettyPrint();

  void prettyPrint(Tree_node*& root, int indent);


  private:

  // Private Member Functions
  /** Insert an item into the tree. 
      post: The item is in the tree.
      @param local_root A reference to the current root
      @param item The item to be inserted
      @return true if the item was not already in the
              tree, false otherwise
  */
  virtual bool insert(Tree_node*& local_root, 
              const string& the_morse, const char& the_letter, int start_index);


  /** Determine whether an item is in the tree.
      @param local_root A reference to the current root
      @param target The item sought
      @return The char value at the morse location
  */
  virtual const char search(Tree_node* local_root, 
                        const string& target) const;


}; // End binary search tree

  //Morse code comparing function
  //Written by Todd deFluiter
  //This function is a function to replace < for morse code so that "00" is less than "0"
  bool less_than_morse(string first, string second) {
	  int i = 0;
	  if (first == second) {  //check if they are equal
		  return false;
	  }
	  if (first.length() < second.length()) {			//if the first is shorter than the second,
														//the difference depends on the next digit in the second
		  if (second.at(first.length()) == '0') {
			  return false;
		  }
		  return true;
	  }
	  if (first.length() > second.length()) {			//or the opposite
		  if (first.at(second.length()) == '0') {
			  return true;
		  }
		  return false;
	  }
	  for (int i = 0; i < second.length(); i++) {		//If they are the same length normal things apply
		  if (second.at(i) == NULL) {					//account for the first node being empty
			  if (first.at(i) == 0) {
				  return true;
			  }
			  else {
				  return false;
			  }
		  }
		  if (first.at(i) < second.at(i)) {				
			  return true;
		  }
		  if (first.at(i) > second.at(i)) {
			  return false;
		  }
	  }
	  if (first.at(second.length()) == 0) {
		  return true;
	  }
	  return false;
  }


// Implementation of member functions ---------------------------------------------------------------

//Overloading the insert function
  bool Binary_Search_Tree::insert(
	  const string& the_morse, const char& the_letter) {
  return insert(this->root, the_morse, the_letter, 0);
}
  /* Insert function definition
     Written by Nathanael Davidson
     Inserts character value and morse-code equivalent to tree at a location dependent on its morse-code value
	 
	 @param local root A reference to the current root
	 @param the_morse Morse code value
	 @param the_letter Character value
	 @param start_index Index to begin reading the_morse at (should be passed in as 0 initially)
	 @return true if a node is inserted, false otherwise

     O(10)
  */
  bool Binary_Search_Tree::insert(
	  Tree_node*& local_root,
	  const string& the_morse, const char& the_letter, int start_index) {
		  
		if (local_root == NULL)					//Check for node contents
		{
			local_root = new Tree_node(the_morse, the_letter);			//If empty, create node here
			return true;
		}
		else
		{
			if (local_root->morse_sequence.size() > the_morse.size())		//Compare size of morse string currently in node to size of string passed in
			{
				insert(local_root->morse_sequence, local_root->letter);		//If existing string is larger, insert contents of current node back into tree
				local_root->morse_sequence = the_morse;						//Replace contents of current node with values passed in
				local_root->letter = the_letter;
				return true;
			}
			else {
				if (the_morse[start_index] == '0')
					return insert(local_root->left, the_morse, the_letter, start_index + 1);	//If morse code value at current index = 0, insert node to left branch
				else if (the_morse[start_index] == '1')
					return insert(local_root->right, the_morse, the_letter, start_index + 1);	//If value = 1, insert to right branch
				else
					return false;		//Return false if no node is inserted
			}
		  }
  }

  const char Binary_Search_Tree::search(
    const string& target) const {
  return search(this->root, target);
}

  //Modified by Cody Wilson for morse_tree functionality
  //This function takes a morse-code input and returns a corresponding character
  const char Binary_Search_Tree::search(
	  Tree_node* local_root,
	  const string& target) const {

	  Tree_node *searchPtr = local_root; //Declare a new tree pointer for tree traversal
	  int target_length = target.size();

	  for (int i = 0; i < target_length; i++)
	  {
		  if (target.at(i) == '0') //check for branch direction
				//If 0, branch left
			  searchPtr = searchPtr->left;
		  else
				//If 1, branch right
			  searchPtr = searchPtr->right;
	  }

	  return searchPtr->letter;
  }
  
  //Calls Pretty-print function below
  inline void Binary_Search_Tree::prettyPrint()
  {
	  return prettyPrint(this->root, 0);
  }

  //Implemented by Cody Wilson
  //While not part of the problem description, it sounded useful to print the tree so I found some code to do that.
  //Found on Stack exchange to print a pretty visual here: http://stackoverflow.com/questions/13484943/print-a-binary-tree-in-a-pretty-way
  //Credit to dasblinkenlight
  void Binary_Search_Tree::prettyPrint(Tree_node*& p, int indent)
  {
	  if (p != NULL) {
		  if (p->right) {
			 prettyPrint(p->right, indent + 4);
		  }
		  if (indent) {
			  cout << setw(indent) << ' ';
		  }
		  if (p->right) cout << " /\n" << setw(indent) << ' ';
		  cout << p->letter << endl;// " " << p->morse_sequence << "\n ";
		  if (p->left) {
			  cout << setw(indent) << ' ' << " \\\n";
			  prettyPrint(p->left, indent + 4);
		  }
	  }
  }


#endif
