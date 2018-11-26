#include "GenNode.h"
#include "GenDlinkedlist.h"
#include "Person.h"
#include "Faculty.h"
#include <string>
#include <iostream>

Faculty::Faculty()
{
  IDnum = 0;
  name = "unknown";
  level = "unknown";
  department = "unknown";
}

Faculty::Faculty(unsigned int aID, string aname, string alevel, string adepartment, GenDlinkedlist<unsigned int>* adID)
{
  adviseeIDs = new GenDlinkedlist<unsigned int>;
  IDnum = aID;
  name = aname;
  level = alevel;
  department = adepartment;
  adviseeIDs = adID;
}

Faculty::~Faculty() {}

string Faculty::getDepartment () {
     return department;
}

void Faculty::setID(unsigned int ID)
{
  IDnum = ID;
}

void Faculty::addtolist(unsigned int aID)
{
  adviseeIDs -> addBack (aID);
}

void Faculty::printinfo()
{
  cout << endl << "Id: " << IDnum << endl <<
  "Name: " << name << endl <<
  "Level: " << level << endl <<
  "Department: " << getDepartment() << endl <<
  "Advisee Ids: " << endl;
  adviseeIDs -> printList();
}

void Faculty::printexit()
{
  cout << IDnum << "\r\n" << name << "\r\n" << level << "\r\n" <<
  getDepartment() << "\r\n" << adviseeIDs -> size() << "\r\n";
  adviseeIDs -> printList();
}

int Faculty::listsize()
{
  return adviseeIDs -> size();
}

unsigned int Faculty::removeadID(unsigned int& sID)
{
  if (adviseeIDs -> isEmpty() == true) {
    cout << "There are no advisees under this faculty" << endl;
    return sID = 0;
  }
  else {
    if (adviseeIDs -> contains (sID) == false) {
      cout << "This advisee is not present under this faculty" << endl;
      return sID = 0;
    }
    else {
      adviseeIDs -> remove (sID);
      return sID;
    }
  }
}

bool operator== (const Faculty &f1, const Faculty &f2) {
     return (f1.IDnum == f2.IDnum);
}

bool operator!= (const Faculty &f1, const Faculty &f2) {
     return (f1.IDnum != f2.IDnum);
}

bool operator> (const Faculty &f1, const Faculty &f2) {
     return (f1.IDnum > f2.IDnum);
}

bool operator< (const Faculty &f1, const Faculty &f2) {
     return (f1.IDnum < f2.IDnum);
}

/*
std::string Faculty::getDepartment() {
     return "";
}

// int* Faculty::getAdviseeIDs() {
//
// }

void Faculty::printAdviseeIDs() {

}

void Faculty::setDepartment(std::string newDepartment) {

}

void Faculty::setAdviseeIDs(int* newAdviseeIDs) {

}

// bool Faculty::equals(Object o) {
//
// }

void Faculty::printFaculty() {
     printPerson();
     std::cout << "\nDepartment: " << getDepartment()
          << "\nAdviseeIDs: ";
     printAdviseeIDs();
}
*/
