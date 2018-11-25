#include <iostream>
using namespace std;

template <class T>
class BST {
public:
  BST();
  virtual ~BST();

  void insert (T value);
  bool contains (T value);
  bool deleteNode (T value);
  bool deleteRec (T key);

  bool isEmpty();

  void printTree (); //iterative in-order traversal
  void recPrint(TreeNode<T> *node);
  /*recursive in-order traversal. We put the node here
  instead of the root because we may have to print a sub-tree.*/
  void printAll();  //pre-order traversal
  void recPrintAll(TreeNode<T> *node);

  void exit();
  void recexit(TreeNode<T> *node);

  void individualInfo(T k);
  unsigned int facultyInfo(T k);

  TreeNode<T> *getSuccessor (TreeNode<T> *d);

private:
  TreeNode<T> *root;
  friend class Simulation;
};

template <class T>
BST<T>::BST()
{
  root = NULL;
}

template <class T>
BST<T>::~BST ()
{
  //what do we do here?

  //my guess would be to iterative and delete? I'll need to research that.
}

template <class T>
void BST<T>::printTree()
{
  recPrint (root);
}

template <class T>
void BST<T>::recPrint(TreeNode<T> *node)
{
  if (node == NULL) {
    return;
  }
  else {
    recPrint (node -> left);
    cout << node -> key.IDnum << endl;
    //cout << node -> key.name << endl;
    recPrint (node -> right);
  }
}

template <class T>
void BST<T>::printAll()
{
  recPrintAll (root);
}

template <class T>
void BST<T>::recPrintAll (TreeNode<T> *node)
{
  if (node == NULL) {
    return;
  }
  else {
    recPrintAll (node -> left);
    node -> key.printinfo();
    recPrintAll (node -> right);
  }
}

template <class T>
bool BST<T>::isEmpty ()
{
  return root == NULL;
}

template <class T>
void BST<T>::insert (T value)
{
  /*
  if (contains(value) == true) {
    cout << "The id '" << value << "' you are trying to insert exists already! Please use a unique id to insert." << endl;
    exit(1);
  }*/

  TreeNode<T> *node = new TreeNode<T> (value);

  if (isEmpty()) {
    root = node;
  }
  else { //not an empty tree
    TreeNode<T> *current = root;
    TreeNode<T> *parent; //empty node

    while (true)
    {
      parent = current;

      if (value < current->key) { //we go left
        current = current -> left;
        if (current == NULL) { //we found an insertion point
          parent -> left = node;
          break;
        }
      }
      else { // we go right
        current = current -> right;
        if (current == NULL) { //we found insertion point
          parent -> right = node;
          break;
        }
      }
    }
  }
}

template <class T>
bool BST<T>::contains (T value)
{
  if (isEmpty()) {
    return false;
  }
  else { //not an empty tree, let's attempt to look for it
    TreeNode<T> *current = root;

    while (true) { //begin searching for value
      if (current == NULL) {
        return false;
      }
      else if (current -> key == value) {
        break;
      }
      else if (value < current -> key) { //go left
          current = current -> left;
        }
        else { //go right
          current = current -> right;
        }
    }
    return true;
  }
}

template <class T>
bool BST<T>::deleteRec (T k)
{/*
  if (contains(k) == false) {
    return false;
  }*/
    //else { //find node and attempt to delete
      TreeNode<T> *parent = root;
      TreeNode<T> *current = root;
      bool isLeft = true;

      //now we need to find it

      while (current -> key != k) {
        if (k < current -> key) {
          isLeft = true;
          parent = current;
          current = current -> left;
        }
        else { //go right
          isLeft = false;
          parent = current;
          current = current -> right;
        }

        if (current == NULL)
          return false;
      }

      //at this point, we found the node that needs to be deleted

      //node has no children, leaf TreeNode

      if (current -> left == NULL && current -> right == NULL) {
        if (current == root)
          root = NULL;
          else if (isLeft) {
            parent -> left = NULL; //we now have to see what we have to do about this in the destructor
          }
            else {
              parent -> right = NULL;
            }
      }

      //now we need to check if the node has one child

      else if (current -> right == NULL) { //no right child, then it must be a left node
        if (current == root)
          root = current -> left;
          else if (isLeft)
            parent -> left = current -> left;
            else //right child
              parent -> right = current -> left;
      }

      else if (current -> left == NULL) { //no left child, opposite of ^^
        if (current == root)
          root = current -> right;
          else if (isLeft)
            parent -> left = current -> right;
            else //right child
              parent -> right = current -> right;
      }

      else { //node has 2 children, at this point we begin to cry!!!
        TreeNode<T> *successor = getSuccessor(current);

        if (current == root)
          root = successor;
          else if (isLeft)
            parent -> left = successor;
            else
              parent -> right = successor;

        successor -> left = current -> left;
      }
      return true;
//} //Big Oh average runtime would be logN and worst would be linear. It is not a nested loop.

//d is the node we are deleting

}

template <class T>
TreeNode<T> *BST<T>::getSuccessor (TreeNode<T> *d)
{
  TreeNode<T> *sp = d; //successor parent
  TreeNode<T> *successor = d; //should be one right, all the way left
  TreeNode<T> *current = d -> right;

  while (current != NULL) {
    sp = successor;
    successor = current;
    current = current -> left;
  }

  if (successor != d -> right) {
    sp -> left = successor -> right;
    successor -> right = d -> right;
  }

  return successor;

}

template<class T>
void BST<T>::exit ()
{
  recexit(root);
}

template <class T>
void BST<T>::recexit (TreeNode<T> *node)
{
  if (node == NULL) {
    return;
  }
  else {
    node -> key.printexit();
    recexit (node -> left);
    recexit (node -> right);
  }
}

template <class T>
void BST<T>::individualInfo (T k)
{
  TreeNode<T> *parent = root;
  TreeNode<T> *current = root;

  //now we need to find it
  while (current -> key != k) {
    if (k < current -> key) {
      parent = current;
      current = current -> left;
    }
    else { //go right
      parent = current;
      current = current -> right;
    }
  }
  current -> key.printinfo();
}

template <class T>
unsigned int BST<T>::facultyInfo (T k)
{
  TreeNode<T> *parent = root;
  TreeNode<T> *current = root;

  //now we need to find it
  while (current -> key != k) {
    if (k < current -> key) {
      parent = current;
      current = current -> left;
    }
    else { //go right
      parent = current;
      current = current -> right;
    }
  }
  return current -> key.getAdvisorID();
}

/*template <class T>
unsigned int BST<T>::adviseeInfo (T k)
{
  TreeNode<T> *parent = root;
  TreeNode<T> *current = root;

  //now we need to find it
  while (current -> key != k) {
    if (k < current -> key) {
      parent = current;
      current = current -> left;
    }
    else { //go right
      parent = current;
      current = current -> right;
    }
  }
  current -> key.listsize();
}*/
