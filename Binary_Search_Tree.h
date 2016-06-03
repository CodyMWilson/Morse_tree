#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "Binary_Tree.h"
#include <vector>
#include <iomanip>

/** Definition of the Binary Search Tree class. 
    @param Item_Type The type of item to be stored in the tree
    Note: Item_Type must define the less-than operator as a 
    total order.
*/
template<typename Item_Type>
  class Binary_Search_Tree : public Binary_Tree<Item_Type>
{
  public:
  // Constructor
  /** Construct an empty Binary_Search_Tree */
  Binary_Search_Tree() : Binary_Tree<Item_Type>() {}

  // Public Member Functions
  /** Insert an item into the tree. 
      post: The item is in the tree.
      @param item The item to be inserted
      @return true if the item was not already
              in the tree, false otherwise
  */
  virtual bool insert(const Item_Type& item);

  /** Remove an item from the tree. 
      post: The item is no longer in the tree.
      @param item The item to be removed
      @return true if the item was in the tree,
              false otherwise
  */
  virtual bool erase(const Item_Type& item);


  /** Determine whether an item is in the tree.
      @param item The item sought
      @return A const pointer to the item if in the
              tree, or NULL if not
  */
  const Item_Type* find(const Item_Type& target) const;
 
  void prettyPrint();

  void prettyPrint(Tree_node<Item_Type>*& root, int indent);


  private:

  // Private Member Functions
  /** Insert an item into the tree. 
      post: The item is in the tree.
      @param local_root A reference to the current root
      @param item The item to be inserted
      @return true if the item was not already in the
              tree, false otherwise
  */
  virtual bool insert(Tree_node<Item_Type>*& local_root, 
              const Item_Type& item);

  /** Remove an item from the tree. 
      post: The item is no longer in the tree.
      @param local_root A reference to the current root
      @param item The item to be removed
      @return true if the item was in the tree,
              false otherwise
  */
  virtual bool erase(Tree_node<Item_Type>*& local_root, 
             const Item_Type& item);


  /** Determine whether an item is in the tree.
      @param local_root A reference to the current root
      @param target The item sought
      @return A const pointer to the item in the tree
  */
  const Item_Type* find(Tree_node<Item_Type>* local_root, 
                        const Item_Type& target) const;
  
  /** Find a replacement for a node that is being deleted.
      This function finds the rightmost local root that 
      does not have a right child. The data in this local_root
      replaces the data in old_root. The pointer to local_root
      is then saved in old_root and local_root is replaced
      by its left child.
      @param old_root Reference to the pointer to old parent
      @param local_root Reference to the pointer to local root
  */
  virtual void replace_parent(Tree_node<Item_Type>*& old_root, 
                      Tree_node<Item_Type>*& local_root);


}; // End binary search tree

  //Default implentation
// Implementation of member functions
template<typename Item_Type>
  bool Binary_Search_Tree<Item_Type>::insert(
    const Item_Type& item) {
  return insert(this->root, item);
}

//template<typename Item_Type>
//  bool Binary_Search_Tree<Item_Type>::insert(
//    Tree_node<Item_Type>*& local_root,
//    const Item_Type& item) {
//  if (local_root == NULL) {
//    local_root = 
//      new Tree_node<Item_Type>(item);
//    return true;
//  } else {
//    if (item < local_root->data)
//      return insert(local_root->left, item);
//    else if (local_root->data < item)
//      return insert(local_root->right, item);
//    else {
//      return false;
//    }
//  }
//}

template<typename Item_Type>
  bool Binary_Search_Tree<Item_Type>::erase(
    const Item_Type& item) {
  return erase(this->root, item);
}

template<typename Item_Type>
  bool Binary_Search_Tree<Item_Type>::erase(
    Tree_node<Item_Type>*& local_root,
     const Item_Type& item) {
  if (local_root == NULL) {
    return false;
  } else {
    if (item < local_root->data)
      return erase(local_root->left, item);
    else if (local_root->data < item)
      return erase(local_root->right, item);
    else { // Found item
      Tree_node<Item_Type>* old_root = local_root;
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

template<typename Item_Type>
void 
Binary_Search_Tree<Item_Type>::replace_parent(Tree_node<Item_Type>*& old_root,
					      Tree_node<Item_Type>*& local_root) {
  if (local_root->right != NULL) {
    replace_parent(old_root, local_root->right);
  } else {
    old_root->data = local_root->data;
    old_root = local_root;
    local_root = local_root->left;
  }
}


template<typename Item_Type>
  const Item_Type* Binary_Search_Tree<Item_Type>::find(
    const Item_Type& item) const {
  return find(this->root, item);
}

template<typename Item_Type>
  const Item_Type* Binary_Search_Tree<Item_Type>::find(
    Tree_node<Item_Type>* local_root, 
    const Item_Type& target) const {
  if (local_root == NULL)
    return NULL;
  if (target < local_root->data)
    return find(local_root->left, target);
  else if (local_root->data < target)
    return find(local_root->right, target);
  else
    return &(local_root->data);
}

  /* 
  @param local_root Reference to the current root
  @param item Data to be inserted
  @param location Vector of '1' and '0' character values encoding the desired location of the data to be inserted. '1' represents a right branch; '0' represents a left branch.
  @param start_index Index at which the functino begins reading the location vector. Pass this in as 0 in most cases. Each time the function calls itself this value increments by 1.
  @return true if the item was inserted, false otherwise
  */
  template<typename Item_Type>
  bool Binary_Search_Tree<Item_Type>::insert(Tree_node<Item_Type>*& local_root, const Item_Type& item, const vector<char> location, int start_index)
  {
	  if (local_root == NULL)
	  {
		  local_root = new Tree_node<Item_Type>(item);
		  return true;
	  }
	  else
	  {
		  if (location[start_index] == '0')
			  return insert(local_root->left, item, location, start_index + 1);
		  else if (location[start_index == '1')
			  return insert(local_root->right, item, location, start_index + 1);
		  else
			  return false;
	  }
  }

  template<typename Item_Type>
  inline void Binary_Search_Tree<Item_Type>::prettyPrint()
  {
	  return prettyPrint(this->root, 0);
  }

  //Found on Stack exchange to print a pretty visual here: http://stackoverflow.com/questions/13484943/print-a-binary-tree-in-a-pretty-way
  //Credit to dasblinkenlight
  template<typename Item_Type>
  void Binary_Search_Tree<Item_Type>::prettyPrint(Tree_node<Item_Type>*& p, int indent)
  {
	  if (p != NULL) {
		  if (p->right) {
			 prettyPrint(p->right, indent + 4);
		  }
		  if (indent) {
			  cout << setw(indent) << ' ';
		  }
		  if (p->right) cout << " /\n" << setw(indent) << ' ';
		  cout << p->data << "\n ";
		  if (p->left) {
			  cout << setw(indent) << ' ' << " \\\n";
			  prettyPrint(p->left, indent + 4);
		  }
	  }
  }


#endif
