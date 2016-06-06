#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
 
#include "MBinary_Tree.h"
#include "MTree_node.h"
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <typeinfo>

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

  //Who wrote it
  //What it does
  bool less_than_morse(string first, string second) {
	  int i = 0;
	  if (first == second) {
		  return false;
	  }
	  if (first.length() < second.length()) {
		  if (second.at(first.length()) == '0') {
			  return false;
		  }
		  return true;
	  }
	  if (first.length() > second.length()) {
		  if (first.at(second.length()) == '0') {
			  return true;
		  }
		  return false;
	  }
	  for (int i = 0; i < second.length(); i++) {
		  if (second.at(i) == NULL) {
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

	//Who wrote it
  //What it does
  bool Binary_Search_Tree::insert(
	  const string& the_morse, const char& the_letter) {
  return insert(this->root, the_morse, the_letter, 0);
}


  bool Binary_Search_Tree::insert(
	  Tree_node*& local_root,
	  const string& the_morse, const char& the_letter, int start_index) {
		  
		if (local_root == NULL)
		{
			local_root = new Tree_node(the_morse, the_letter);
			return true;
		}
		else
		{
			if (local_root->morse_sequence.size() > the_morse.size()) {
				insert(local_root->morse_sequence, local_root->letter);
				local_root->morse_sequence = the_morse;
				local_root->letter = the_letter;
				return true;
			}
			else {
				if (the_morse[start_index] == '0')
					return insert(local_root->left, the_morse, the_letter, start_index + 1);
				else if (the_morse[start_index] == '1')
					return insert(local_root->right, the_morse, the_letter, start_index + 1);
				else
					return false;
			}
		  }
  }


  //Modified by Cody Wilson for morse_tree functionality
  //This function takes a morse-code input calls the overloaded function with reference to the root of the tree
  const char Binary_Search_Tree::search(
    const string& target) const {
  return search(this->root, target);
}

  //Modified by Cody Wilson with help from Todd Defliuter from generic "find" function
  //This function takes a morse-code input and returns a corresponding character
  //Took two revisions, but settled on this simplified version. The original version used a case statement
  // and listed out every possible option, but it dawned on me that there was a much simplier solution.
  //	Order: O(n), n=level of the tree
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
  
  //Modified by Cody Wilson from a function found online
  //Calls Pretty-print function below
  inline void Binary_Search_Tree::prettyPrint()
  {
	  return prettyPrint(this->root, 0);
  }

  //Modified to work for our tree by Cody Wilson
  //Found on Stack exchange to print a pretty visual here: http://stackoverflow.com/questions/13484943/print-a-binary-tree-in-a-pretty-way
  //Credit to dasblinkenlight
  //Note: This tree prints sideways with the left printing the tip of the tree
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
