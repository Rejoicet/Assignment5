#include <iostream>
using namespace std;

class Person {
public:
  Person();
  ~Person();

  friend bool operator== (const Person &p1, const Person &p2);
  friend bool operator!= (const Person &p1, const Person &p2);
  friend bool operator> (const Person &p1, const Person &p2);
  friend bool operator< (const Person &p1, const Person &p2);
//private:
  string name, level;
  unsigned int IDnum;

  friend class Simulation;
};
