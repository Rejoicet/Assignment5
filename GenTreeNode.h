#include <iostream>
using namespace std;

template <class T>
class BST;

template <class T>
class TreeNode {
public:
  TreeNode();
  TreeNode(T key);
  virtual ~TreeNode();

  T key;
  /*in this example our key will be our value too.
  If not, we will declare values as member variables*/
  TreeNode *left;
  TreeNode *right;

private:
  friend class BST<T>;
  friend class Simulation;
};

template <class T>
TreeNode<T>::TreeNode ()
{
  left = NULL;
  right = NULL;
}

template <class T>
TreeNode<T>::TreeNode (T k)
{
  left = NULL;
  right = NULL;
  key = k;
}

template <class T>
TreeNode<T>::~TreeNode() {}
