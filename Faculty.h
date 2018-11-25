#include <string>
#include <iostream>

class Faculty : public Person {
public:
     Faculty();
     Faculty(unsigned int aID, string aname, string alevel, string adepartment, GenDlinkedlist<unsigned int>* adID);
     ~Faculty();

     string getDepartment();
     void setID(unsigned int ID);
     void printinfo();
     void printexit();
     int listsize();

     friend bool operator== (const Faculty &f1, const Faculty &f2);
     friend bool operator!= (const Faculty &f1, const Faculty &f2);
     friend bool operator> (const Faculty &f1, const Faculty &f2);
     friend bool operator< (const Faculty &f1, const Faculty &f2);
/*
     string getDepartment();
     // int* getAdviseeIDs();
     void printAdviseeIDs();

     void setDepartment(std::string newDepartment);
     void setAdviseeIDs(int* newAdviseeIDs);

     // bool equals(Object o);
     void printFaculty();
     */

private:
   string department;
   GenDlinkedlist<unsigned int>* adviseeIDs;
   friend class Simulation;

};
