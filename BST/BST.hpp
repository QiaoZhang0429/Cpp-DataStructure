#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

  /** Height of this BST. */
  unsigned int iheight;
  
public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(0), isize(0), iheight(0) {  }


  /** Default destructor.
      Delete every node in this BST.
   */ // TODO
  virtual ~BST() {
    deleteAll(root);
  }

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return  true if the item was added to this BST
   *  as a result of this call to insert,
   *  false if an item equal to this one was already in this BST.
   *  Note: This function should use only the '<' or "==" operator when comparing
   *  Data items. (should not use >, <=, >=)
   */ // TODO
  virtual bool insert(const Data& item) {
    if(root == 0){
      root = new BSTNode<Data>(item);
      iheight = 1;
      isize ++ ;
      return true;
    }
    BSTNode<Data> *p = root;
    int count = 0;
    while (p){
      if(p->data == item) return false;
      if((item < p->data) && (p -> left)) {
        p = p -> left;
        count ++ ;
      }
      else if ((item < p->data) && !(p -> left)) {
        BSTNode<Data>* newNode;
        newNode = new BSTNode<Data>(item); 
        newNode->parent = p;
        p -> left = newNode;
        count ++;
        if(iheight < count){
          iheight = count;
        }
        isize ++ ;
        return true;
      }
      else if ((p->data < item) && (p -> right)) { 
        p = p -> right;
        count ++ ;
      }
      else if ((p->data < item) && !(p -> right)) {
        BSTNode<Data>* newNode;
        newNode = new BSTNode<Data>(item); 
        newNode->parent = p;
        p -> right = newNode;
        count ++;
        if(iheight < count){
          iheight = count;
        }
        isize ++ ;
        return true;
      }
    }
    return false;
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' or "==" operator when comparing
   *  Data items. (should not use >, <=, >=)
   */ // TODO
  iterator find(const Data& item) const {
    if(root == 0){
      return end();
    }
    BSTNode<Data> *p = root;
    while (p){
      if(p->data == item) return typename BST<Data>::iterator(p);
      if ((item < p->data)) {
        p = p -> left;
      }
      else if (p->data < item) { 
        p = p -> right;
      }
    }
    return end();
  }

  
  /** Return the number of items currently in the BST.
   */ // TODO
  unsigned int size() const {
    return isize;
  }
  
  /** Return the height of the BST.
   */ // TODO
  unsigned int height() const {
    return iheight;
  }


  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const {
    return root == NULL;
  }

  /** Return an iterator pointing to the first item in the BST (not the root).
   */ // TODO
  iterator begin() const {
    return typename BST<Data>::iterator(first(root));

  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(0);
  }

  /** Perform an inorder traversal of this BST.
   */
  void inorder() const {
    inorder(root);
  }


private:

  /** Recursive inorder traversal 'helper' function */

  /** Inorder traverse BST, print out the data of each node in ascending order.
      Implementing inorder and deleteAll base on the pseudo code is an easy way to get started.
   */ // TODO
  void inorder(BSTNode<Data>* n) const {
    /* Pseudo Code:
      if current node is null: return;
      recursively traverse left sub-tree
      print current node data
      recursively traverse right sub-tree
    */
    if(n == NULL) 
      return ;
    inorder(n->left);
    BSTNode<Data>& newNode = *n;
    std::cout << newNode << std::endl;
    inorder(n->right);
  }

  /** Find the first element of the BST
   */ 
  static BSTNode<Data>* first(BSTNode<Data>* root) {
    if(root == 0) return 0;
    while(root->left != 0) root = root->left;
    return root;
  }

  /** do a postorder traversal, deleting nodes
   */ // TODO
  static void deleteAll(BSTNode<Data>* n) {
    /* Pseudo Code:
      if current node is null: return;
      recursively delete left sub-tree
      recursively delete right sub-tree
      delete current node
  */
    if(n == 0) return ;
    else{
      deleteAll(n->left);
      deleteAll(n->right);
      delete n;
      n = 0;
    }
  }


 };


#endif //BST_HPP
