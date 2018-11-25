#include "Person.h"
#include "Student.h"
#include <string>
#include <iostream>

Student::Student() {
     IDnum = 0;
     name = "unknown";
     level = "unknown";
     major = "unknown";
     GPA = 0.0;
     facID = 0;
}

Student::Student(unsigned int aIDnum, string aname, string alevel, string amajor, double aGPA, unsigned int afacID) {
     IDnum = aIDnum;
     name = aname;
     level = alevel;
     major = amajor;
     GPA = aGPA;
     facID = afacID;
}

Student::~Student() {

}

int Student::getstudentID()
{
  return IDnum;
}

string Student::getMajor() {
     return major;
}

double Student::getGPA() {
     return GPA;
}

int Student::getAdvisorID() {
     return facID;
}
/*
void Student::setStudentID(unsigned int sID)
{
  IDnum = sID;
}*/

void Student::setID (unsigned int ID)
{
  IDnum = ID;
}

void Student::setMajor(string amajor) {
  major = amajor;

}

void Student::setGPA(double aGPA) {
  GPA = aGPA;
}

void Student::setAdvisorID(unsigned int afacID) {
  facID = afacID;

}

void Student::printinfo()
{
  cout << endl << "Id: " << IDnum << endl <<
  "Name: " << name << endl <<
  "Level: " << level << endl <<
  "Major: " << getMajor() << endl <<
  "GPA: " << getGPA() << endl <<
  "Advisor Id: " << getAdvisorID() << endl;
}

void Student::printexit()
{
  cout << IDnum << "\r\n" << name << "\r\n" << level << "\r\n" <<
  getMajor() << "\r\n" << getGPA() << "\r\n" << getAdvisorID() << "\r\n";
}
/*
void Student::printexitfirst()
{
  cout << IDnum << "\r\n" << name << "\r\n" << level << "\r\n" <<
  getMajor() << "\r\n" << getGPA() << "\r\n" << getAdvisorID();
}*/

bool operator== (const Student &s1, const Student &s2) {
     return (s1.IDnum == s2.IDnum);
}

bool operator!= (const Student &s1, const Student &s2) {
     return (s1.IDnum != s2.IDnum);
}

bool operator> (const Student &s1, const Student &s2) {
     return (s1.IDnum > s2.IDnum);
}

bool operator< (const Student &s1, const Student &s2) {
     return (s1.IDnum < s2.IDnum);
}




// bool Student::equals(Object o) {
//
// }
/*
void Student::printStudent() {
     printPerson();
     std::cout << "\nMajor: " << getMajor()
          << "\nGPA: " << getGPA()
          << "\nAdvisor ID: " << getAdvisorID() << std::endl;
}
*/
