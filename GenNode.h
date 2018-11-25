#include <iostream>

using namespace std;

template <typename T>
class GenDlinkedlist;     //forward declaring the class

template <typename T>
class GenNode {
public:
  GenNode();
  GenNode(int k);
  ~GenNode();

private:
  T elem;
  GenNode<T> *prev;
  GenNode<T> *next;
  GenNode<T> *header;

  friend class GenDlinkedlist<T>;
  friend class Faculty;
  friend class Simulation;
};

template <class T>
GenNode<T>::GenNode()
{
  prev = NULL;
  next = NULL;
}

template <class T>
GenNode<T>::GenNode(int k)
{
  elem = k;
  prev = NULL;
  next = NULL;
}

template <class T>
GenNode<T>::~GenNode() {}
