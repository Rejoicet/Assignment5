#include <string>
#include <iostream>
using namespace std;

class Student: public Person {
public:
     Student();
     Student(unsigned int aIDnum, string aname, string alevel, string amajor, double aGPA, unsigned int afacID);
     ~Student();

     int getstudentID ();
     string getMajor();
     double getGPA();
     int getAdvisorID();

     void setMajor(string amajor);
     void setGPA(double aGPA);
     void setAdvisorID(unsigned int afacID);
     void setID (unsigned int ID);

     void printinfo();
     void printexit();

     friend bool operator== (const Student &s1, const Student &s2);
     friend bool operator!= (const Student &s1, const Student &s2);
     friend bool operator> (const Student &s1, const Student &s2);
     friend bool operator< (const Student &s1, const Student &s2);

     // bool equals(Object o);
     //void printStudent();

   private:
     string major;
     double GPA;
     int facID;
     friend class Simulation;
};
