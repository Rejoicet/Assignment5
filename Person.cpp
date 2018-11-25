#include "Person.h"
#include <iostream>
using namespace std;

Person::Person()
{
  IDnum = 0;
}

Person::~Person() {}

bool operator== (const Person &p1, const Person &p2) {
     return (p1.IDnum == p2.IDnum);
}

bool operator!= (const Person &p1, const Person &p2) {
     return (p1.IDnum != p2.IDnum);
}

bool operator> (const Person &p1, const Person &p2) {
     return (p1.IDnum > p2.IDnum);
}

bool operator< (const Person &p1, const Person &p2) {
     return (p1.IDnum < p2.IDnum);
}
