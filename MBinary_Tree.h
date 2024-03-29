// ---
//
//MBinary_tree file for Morse-tree applications
//Submitted by:
//Cody Wilson
//Nathaniel Davidson
//Todd Defluiter
//6/6/2016
//

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

/** Class for a binary tree. */

#pragma once
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include "MTree_node.h"

  class Binary_Tree
{
  public:

  // Constructors and Functions

  /** Construct an empty Binary_Tree. */
Binary_Tree() : root(NULL) {}

  /** Construct a Binary_Tree with two subtrees.
      @param the_data The data at the root
      @param left_child The left subtree
      @param right_child The right subtree
  */
Binary_Tree(const string the_morse,
			const char the_letter,
            const Binary_Tree& left_child
              = Binary_Tree(),
            const Binary_Tree& right_child
               = Binary_Tree()):
  root(new Tree_node(the_morse, the_letter, left_child.root,
                             right_child.root)) {}

  /** Virtual destructor to avoid warnings */
  virtual ~Binary_Tree() {} // Do nothing.


  /** Return the left subtree. */
  Binary_Tree get_left_subtree() const;

  /** Return the right subtree. */
  Binary_Tree get_right_subtree() const;

  /** Return the data field of the root.
      @throws std::invalid_argument if empty tree
  */
  const string& get_morse() const;

  const char& get_letter() const;

  /** Indicate that this is the empty tree. */
  bool is_null() const;

  /** Indicate that this tree is a leaf. */
  bool is_leaf() const;

  /** Return a string representation of this tree. */
  virtual std::string to_string() const;

  /** Read a binary tree */
  static Binary_Tree read_binary_tree(std::istream& in);

  /** Return a string representation of the root */
  std::string root_to_string() const {
    return root->to_string();
  }



  protected:

  // Protected constructor
  /** Construct a Binary_Tree with a given node as the root */
Binary_Tree(Tree_node* new_root) : root(new_root) {}

  // Data Field
  Tree_node* root;

 private:



  

};  // End Binary_Tree

// Overloading the ostream insertion operator.

  std::ostream& operator<<(std::ostream& out, 
                           const Binary_Tree& tree)
{
  return out << tree.to_string();
}

// Overloading the istream extraction operator
  std::istream& operator>>(std::istream& in, 
                           Binary_Tree& tree)
{
  tree = Binary_Tree::read_binary_tree(in);
  return in;
}

// Implementation of member functions


// Accessors
/** Return the left-subtree. */
  Binary_Tree 
    Binary_Tree::get_left_subtree() const {
  if (root == NULL) {
    throw std::invalid_argument("get_left_subtree on empty tree");
  }
  return Binary_Tree(root->left);
}


/** Return the right-subtree */
Binary_Tree
Binary_Tree::get_right_subtree() const {
  if (root == NULL) {
    throw std::invalid_argument("get_right_subtree on null tree");
  }
  return Binary_Tree(root->right);
}

/** Return the data field of the root
    @throws std::invalid_argument if null tree
*/

const string& Binary_Tree::get_morse() const {
  if (root == NULL) {
    throw std::invalid_argument("get_morse on null tree");
  }
  return root->morse_sequence;
}

const char& Binary_Tree::get_letter() const {
	if (root == NULL) {
		throw std::invalid_argument("get_letter on null tree");
	}
	return root->letter;
}

bool Binary_Tree::is_null() const {
  return root == NULL;
}

/** Indicate that this tree is a leaf. */
  bool Binary_Tree::is_leaf() const {
  if (root != NULL) {
    return root->left == NULL && root->right == NULL;
  } else
    return true;
}

/** Return a string representation of this tree */
std::string Binary_Tree::to_string() const {
  std::ostringstream os;
  if (is_null())
    os << "NULL\n";
  else {
    os << *root << '\n';
    os << get_left_subtree().to_string();
    os << get_right_subtree().to_string();
  }
  return os.str();
}


  Binary_Tree Binary_Tree::
    read_binary_tree(std::istream& in) {
  std::string next_line;
  getline(in, next_line);
  if (next_line == "NULL") {
    return Binary_Tree();
  } else {
    string the_morse;
	char the_letter;
    std::istringstream ins(next_line);
    ins >> the_morse;
	ins >> the_letter;
    Binary_Tree left = read_binary_tree(in);
    Binary_Tree right = read_binary_tree(in);
    return Binary_Tree(the_morse, the_letter, left, right);
  }
}






#endif

