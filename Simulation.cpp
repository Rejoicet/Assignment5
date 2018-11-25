#include "GenNode.h"
#include "GenDlinkedlist.h"
#include "GenTreeNode.h"
#include "GenBST.h"
#include "Person.h"
#include "Student.h"
#include "Faculty.h"
#include "Simulation.h"
#include <iostream>
#include <fstream>      //to input and output using files
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sstream>
using namespace std;

Simulation::Simulation ()
{
  stree = new BST <Student>;
  ftree = new BST <Faculty>;
  choice = 0;
  j = 2;
}

Simulation::~Simulation () {}

void Simulation::simulate()
{
  studentFile.open("studentTable.txt");
  if (!studentFile) {         /*this is the first time the user is using the
                              program so a new tree has to be initialized*/
    stree = new BST <Student>;
  }
  else {                    //the tree is already present, start reading!
    while (!(studentFile >> ws).eof()) {   //building the tree
      studentFile >> sID;
      while (getline(studentFile, line)) {
        if (c == 1) {
          nam = line;
        }
        else if (c == 2) {
          lev = line;
        }
        else if (c == 3) {
          maj = line;
          break;
        }
        c++;
      }

      c = 0;

      studentFile >> GP;
      studentFile >> fID;
      Student student (sID, nam, lev, maj, GP, fID);
      stree -> insert(student);
    }
  }
  studentFile.close();

  facultyFile.open ("facultyTable.txt");
  if (!facultyFile) {         /*this is the first time the user is using the
                              program so a new tree has to be initialized*/
    ftree = new BST <Faculty>;
  }
  else {                    //the tree is already present, start reading!
    while (!(facultyFile >> ws).eof()) {   //building the tree
      facultyFile >> fID;
      while (getline(facultyFile, line)) {
        if (c == 1) {
          nam = line;
        }
        else if (c == 2) {
          lev = line;
        }
        else if (c == 3) {
          dep = line;
          break;
        }
        c++;
      }

      c = 0;

      facultyFile >> a;
      GenDlinkedlist <unsigned int>* adIDs;
      adIDs = new GenDlinkedlist <unsigned int>;
      for (int i = 0; i < a; i++) {
        facultyFile >> b;
        adIDs->addBack (b);
      }

      Faculty faculty (fID, nam, lev, dep, adIDs);
      ftree -> insert(faculty);
    }
  }
  facultyFile.close();

  while(input != 14) {
       promptUser();
       cout << "Select an option between 1 and 14: ";
       cin >> input;
       /*while(!isValid(input, 1)) {
            cout << "ERROR: Not a valid option. \nEnter a number between 1 and 14: ";
            getline(cin, input);
       }
       stringstream choiceStream(input);    //parse to double
       choiceStream >> choice;*/
       switch(input) {
            case 1:
                 stree -> printAll();
                 break;
            case 2:
                 ftree -> printAll();
                 break;
            case 3:
                cout << "Please enter the ID number of the student you want the information of" << endl;
                cin >> sID;
                if (studentcheckID(sID) == false) {
                  cout << "This student is not present in the database!" << endl;
                }
                else {
                  sinfo (sID);
                }
                break;
            case 4:
                 cout << "Please enter the ID number of the faculty you want the information of" << endl;
                 cin >> fID;
                 if (facultycheckID(fID) == false) {
                 cout << "This faculty is not present in the database!" << endl;
                 }
                 else {
                   finfo(fID);
                 }
                 break;
            case 5:
              facInfo ();
              break;
            case 6:
                //stuInfo();
                break;
            case 7:
                 createStudent();
                 break;
            case 8:
                 sdelete();
                 break;
            case 9:
                 createFaculty();
                 break;
            case 10:
                 fdelete();
                 break;
            case 11:
                 // Change a student’s advisor given the student id and the new faculty id.
                 break;
            case 12:
                 // Remove an advisee from a faculty member given the ids
                 break;
            case 13:
                 // Rollback
                 break;
            case 14:
              break;
       }
  }
  //this means the user has selected 14
  cout << "Thank you for using the program. Bye." << endl;
  freopen ("studentTable.txt", "w", stdout);    /*writes the output to the
                            specified file. Creates a new file if not present*/
  stree -> exit();

  freopen ("facultyTable.txt", "w", stdout);    /*writes the output to the
                            specified file. Creates a new file if not present*/
  ftree -> exit();
  fclose (stdout);    //closing the output files
}


void Simulation::promptUser()
{
  cout << "[1] Print all students and their information (sorted by ascending id #)" <<
       "\n[2] Print all faculty and their information (sorted by ascending id #)" <<
       "\n[3] Find and display student information given the students id" <<
       "\n[4] Find and display faculty information given the faculty id" <<
       "\n[5] Given a student’s id, print the name and info of their faculty advisor" <<
       "\n[6] Given a faculty id, print ALL the names and info of his/her advisees." <<
       "\n[7] Add a new student" <<
       "\n[8] Delete a student given the id" <<
       "\n[9] Add a new faculty member" <<
       "\n[10] Delete a faculty member given the id." <<
       "\n[11] Change a student’s advisor given the student id and the new faculty id." <<
       "\n[12] Remove an advisee from a faculty member given the ids" <<
       "\n[13] Rollback" <<
       "\n[14] Exit" << endl;
}
/*
bool Simulation::isValid(string newString, int indic) {
     //0 indicator checks for valid string, non-zero indicator checks if valid int
     if(newString.empty())
          return false;
     else {
          int idx = 0;
          char *str = &newString[0];

          while(str[idx]) {
               if(indic == 0) { if (!isalpha(str[idx]))   return false; }  //if indicator is 0, check if valid string
               else { if (!isdigit(str[idx]))   return false; }  //if indicator is not 0, check if valid digit
               idx++;
          }
     }
     return true;
}
*/
void Simulation::createStudent ()
{
  cout << "Please enter the student ID" << endl;
  cin >> sID;
  getline (cin, nam);
  cout << "Please enter the name of the student" << endl;
  getline (cin, nam);
  cout << "Please enter the level of the student (Freshman, Sophomore etc.)" << endl;
  getline (cin, lev);
  cout << "Please enter the student's major" << endl;
  getline (cin, maj);
  cout << "Please enter the GPA of the student" << endl;
  cin >> GP;
  cout << "Please enter the student's advisor's ID" << endl;
  cin >> fID;
  /*while (facultycheckID(fID) == false) {
    cout << "This faculty ID is not present in the database. Please enter the correct ID." << endl;
    cin >> fID;
  }*/
  Student student (sID, nam, lev, maj, GP, fID);
  stree -> insert(student);
}

void Simulation::createFaculty()
{
  cout << "Please enter the faculty ID" << endl;
  cin >> fID;
  getline (cin, nam);
  cout << "Please enter the name of the faculty" << endl;
  getline (cin, nam);
  cout << "Please enter the level of the faculty (Professor, Assistant Professor etc.)" << endl;
  getline (cin, lev);
  cout << "Please enter the department the faculty belongs to" << endl;
  getline (cin, dep);
  cout << "Please enter the number of advisees this faculty has" << endl;
  cin >> a;
  GenDlinkedlist <unsigned int>* adIDs;
  adIDs = new GenDlinkedlist <unsigned int>;
  for (int i = 0; i < a; i++) {
    cout << "Please enter the student id" << endl;
    cin >> b;
    /*while (studentcheckID(b) == false) {
      cout << "This student ID is not present in the database. Please enter the correct ID." << endl;
      cin >> b;
    }*/
    adIDs->addBack (b);
  }
  Faculty faculty (fID, nam, lev, dep, adIDs);
  ftree -> insert(faculty);
}

bool Simulation::studentcheckID (unsigned int cID)
{
  Student stuCheck;
  stuCheck.setID(cID);
  if(stree -> contains(stuCheck))
       return true;
  return false;
}

void Simulation::sdelete ()
{
  cout << "Please enter the ID number of the student you want to delete" << endl;
  cin >> sID;
  while (studentcheckID (sID) == false) {
    cout << "This ID is not present in the database. Please enter a valid ID number" << endl;
    cin >> sID;
  }
  Student student;
  student.setID (sID);
  stree -> deleteRec (student);
  cout << "The given ID has been deleted successfully!" << endl;
}

bool Simulation::facultycheckID (unsigned int cID)
{
  Faculty facCheck;
  facCheck.setID(cID);
  if(ftree -> contains(facCheck))
       return true;
  return false;
}

void Simulation::fdelete ()
{
  cout << "Please enter the ID number of the faculty you want to delete" << endl;
  cin >> fID;
  while (facultycheckID (fID) == false) {
    cout << "This ID is not present in the database. Please enter a valid ID number" << endl;
    cin >> fID;
  }
  Faculty faculty;
  faculty.setID (fID);
  ftree -> deleteRec (faculty);
  cout << "The given ID has been deleted successfully!" << endl;
}

void Simulation::sinfo (unsigned int sID)
{
    Student student;
    student.setID (sID);
    stree -> individualInfo (student);
}

void Simulation::finfo (unsigned int fID)
{
    Faculty faculty;
    faculty.setID (fID);
    ftree -> individualInfo (faculty);
}

void Simulation::facInfo()
{
  cout << "Please enter the id of the student whose advisor info you want to view" << endl;
  cin >> sID;
  while (studentcheckID(sID) == false) {
    cout << "Please enter the correct ID of the student." << endl;
    cin >> sID;
  }
  Student student;
  student.setID (sID);
  cout << "Faculty Advisor info -> " << endl;
  finfo(stree -> facultyInfo(student));
}
/*
void Simulation::stuInfo()
{
  cout << "Please enter the id of the faculty whose advisee info you want to view" << endl;
  cin >> fID;
  while (facultycheckID(fID) == false) {
    cout << "Please enter the correct ID of the faculty." << endl;
    cin >> fID;
  }
  Faculty faculty;
}*/
