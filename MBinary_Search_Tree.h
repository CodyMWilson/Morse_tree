#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "MBinary_Tree.h"
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
  virtual bool insert(const vector<char>& the_morse, const char& the_letter);

  /** Remove an item from the tree. 
      post: The item is no longer in the tree.
      @param item The item to be removed
      @return true if the item was in the tree,
              false otherwise
  */
  virtual bool erase(const vector<char>& the_morse);


  /** Determine whether an item is in the tree.
      @param item The item sought
      @return A const pointer to the item if in the
              tree, or NULL if not
  */
  const string* find(const string& target) const;
 
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
              const vector<char>& the_morse, const char& the_letter, int start_index);

  /** Remove an item from the tree. 
      post: The item is no longer in the tree.
      @param local_root A reference to the current root
      @param item The item to be removed
      @return true if the item was in the tree,
              false otherwise
  */
  virtual bool erase(Tree_node*& local_root, 
             const vector<char>& the_morse);


  /** Determine whether an item is in the tree.
      @param local_root A reference to the current root
      @param target The item sought
      @return A const pointer to the item in the tree
  */
  const string* find(Tree_node* local_root, 
                        const string& target) const;
  
  /** Find a replacement for a node that is being deleted.
      This function finds the rightmost local root that 
      does not have a right child. The data in this local_root
      replaces the data in old_root. The pointer to local_root
      is then saved in old_root and local_root is replaced
      by its left child.
      @param old_root Reference to the pointer to old parent
      @param local_root Reference to the pointer to local root
  */
  virtual void replace_parent(Tree_node*& old_root, 
                      Tree_node*& local_root);


}; // End binary search tree

  /*bool less_than_morse(vector<char> first, string second) {
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
  */
  //Default implentation
// Implementation of member functions

  bool Binary_Search_Tree::insert(
	  const vector<char>& the_morse, const char& the_letter) {
  return insert(this->root, the_morse, the_letter, 0);
}


  bool Binary_Search_Tree::insert(
    Tree_node*& local_root,
	  const vector<char>& the_morse, const char& the_letter, int start_index) {
	  if (local_root == NULL)
	  {
		  local_root = new Tree_node(the_morse, the_letter);
		  return true;
	  }
	  else
	  {
		  if (the_morse[start_index] == '0')
			  return insert(local_root->left, the_morse, the_letter, start_index + 1);
		  else if (the_morse[start_index] == '1')
			  return insert(local_root->right, the_morse, the_letter, start_index + 1);
		  else
			  return false;
	  }
}
  bool Binary_Search_Tree::erase(
    const vector<char>& the_morse) {
  return erase(this->root, the_morse);
}

  bool Binary_Search_Tree::erase(
    Tree_node*& local_root,
     const vector<char>& the_morse) {
  if (local_root == NULL) {
    return false;
  } 
 /* else {
	if (local_root->letter == NULL) {
		if (the_morse.at(0) == '0') {
			return erase(local_root->left, the_morse);
		}
		else {
			return erase(local_root->right, the_morse);
		}
	}
    else if (less_than_morse(the_morse, local_root->morse_sequence))
      return erase(local_root->left, the_morse);
    else if (less_than_morse(local_root->morse_sequence, the_morse))
      return erase(local_root->right, the_morse);
    else { // Found item
      Tree_node* old_root = local_root;
      if (local_root->left == NULL) {
        local_root = local_root->right;
      } else if (local_root->right == NULL) {
        local_root = local_root->left;
      } else {
        replace_parent(old_root, old_root->left);
      }
      delete old_root;      
      return true;
    }
  }
}

*/
void Binary_Search_Tree::replace_parent(Tree_node*& old_root,
					      Tree_node*& local_root) {
  if (local_root->right != NULL) {
    replace_parent(old_root, local_root->right);
  } else {
    old_root->morse_sequence = local_root->morse_sequence;
	old_root->letter = local_root->letter;
    old_root = local_root;
    local_root = local_root->left;
  }
}



  const string* Binary_Search_Tree::find(
    const string& target) const {
  return find(this->root, target);
}


  const string* Binary_Search_Tree::find(
    Tree_node* local_root, 
    const string& target) const {
  if (local_root == NULL)
    return NULL;
  if (local_root->letter == NULL) {
	  if (target.at(0) == '0') {
		  return find(local_root->left, target);
	  }
	  else {
		  return find(local_root->right, target);
	  }
  }
  else if (less_than_morse(target, local_root->morse_sequence))
    return find(local_root->left, target);
  else if (less_than_morse(local_root->morse_sequence, target))
    return find(local_root->right, target);
  else
    return &(local_root->morse_sequence);
}

/*
  template<typename Item_Type>
  bool Binary_Search_Tree<Item_Type>::insert(Tree_node<Item_Type>*& local_root, const Item_Type& item)
  {
	  if (local_root == NULL)
	  {
		  local_root = new Tree_node<Item_Type>(item);
		  return true;
	  }
	  else
	  {
		  if (item < local_root->data)
			  return insert(local_root->left, item);
		  else if (local_root->data < item)
			  return insert(local_root->right, item);
		  else
			  return false;
	  }
  }
  */


  inline void Binary_Search_Tree::prettyPrint()
  {
	  return prettyPrint(this->root, 0);
  }

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
		  cout << p->letter << " " << p->morse_sequence << "\n ";
		  if (p->left) {
			  cout << setw(indent) << ' ' << " \\\n";
			  prettyPrint(p->left, indent + 4);
		  }
	  }
  }


#endif
