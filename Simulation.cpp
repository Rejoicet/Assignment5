#include "GenStack.h"
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
  option = 0;
  lastEdit = -1;
  sRollback = new GenDlinkedlist<Student>;
  fRollback = new GenDlinkedlist<Faculty>;
  myStack = new GenStack<int>;
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
                if (stree -> isEmpty() == true) {
                  cout << endl << "There are no students present in the database!" << endl << endl;
                }
                else {
                  stree -> printAll();
                }
                break;
            case 2:
                if (ftree -> isEmpty() == true) {
                  cout << endl << "There are no faculties present in the database!" << endl << endl;
                }
                else {
                  ftree -> printAll();
                }
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
                stuInfo();
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
                cout << "Please enter the id of the student whose advisor you want to change." << endl;
                cin >> sID;
                while (studentcheckID(sID) == false) {
                  cout << "Please enter the correct ID of the student. The ID you entered is not in the database." << endl;
                  cin >> sID;
                }
                cout << "Please enter the new faculty ID you would like to assign to the student." << endl;
                cin >> fID;
                while (facultycheckID(fID) == false) {
                  cout << "Please enter the correct ID of the faculty. The ID you entered is not in the database." << endl;
                  cin >> fID;
                }
                changeAdvisor(sID, fID);
                break;
            case 12:
                cout << "Please enter the ID of the faculty whose advisee you want to remove." << endl;
                cin >> fID;
                while (facultycheckID(fID) == false) {
                  cout << "Please enter the correct ID of the faculty. The ID you entered is not in the database." << endl;
                  cin >> fID;
                }
                cout << "Please enter the ID of the advisee you want to remove." << endl;
                cin >> sID;
                removeAdvisee(fID, sID);
                break;
            case 13:
                rollback();
                break;
            case 14:
                break;
       }
  }
  //this means the user has selected 14
  cout << endl << "Thank you for using the program. Bye." << endl << endl;
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
  if(sRollback -> size() == 5){
    sRollback -> removeBack();
  }
  sRollback -> addFront(student);
  myStack -> push (0);
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
    /*if (studentcheckID(b) == false) {
      cout << "This student ID is not present in the database. Please enter the correct ID." << endl;
      cin >> b;
    }*/
    adIDs->addBack (b);
  }
  Faculty faculty (fID, nam, lev, dep, adIDs);
  ftree -> insert(faculty);
  if(fRollback -> size() == 5){
    fRollback -> removeBack();
  }
  fRollback -> addFront(faculty);
  myStack -> push (1);
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
  Student stu;
  stu = stree -> getobject(student);
  stree -> deleteRec (student);
  cout << "The given ID has been deleted successfully!" << endl;
  if(sRollback -> size() == 5){
    sRollback -> removeBack();
  }
  sRollback -> addFront(stu);
  myStack -> push (0);
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
  Faculty fac;
  fac = ftree -> getobject (faculty);
  ftree -> deleteRec (faculty);
  cout << "The given ID has been deleted successfully!" << endl;
  if(fRollback -> size() == 5){
    fRollback -> removeBack();
  }
  fRollback -> addFront(fac);
  myStack -> push (1);
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

void Simulation::stuInfo()
{
  cout << "Please enter the id of the faculty whose advisee info you want to view" << endl;
  cin >> fID;
  while (facultycheckID(fID) == false) {
    cout << "Please enter the correct ID of the faculty." << endl;
    cin >> fID;
  }
  stree -> adviseeInfo (fID);
}

void Simulation::changeAdvisor(unsigned int sID, unsigned int newfID)
{
  Student student;
  student.setID(sID);
  oldfID = stree -> changeFadvisor (student, newfID);
  Faculty faculty;
  faculty.setID(newfID);
  ftree -> addFadvisee (faculty, sID);
  faculty.setID(oldfID);
  if (ftree -> removeSadvisee (faculty, sID) == sID) {
    cout << endl << "The advisee has been removed sucessfully!" << endl;
  }
}

void Simulation::removeAdvisee(unsigned int fID, unsigned int sID)
{
  Faculty faculty;
  faculty.setID(fID);
  if (ftree -> removeSadvisee (faculty, sID) == sID) {
    cout << endl << "The advisee has been removed sucessfully!" << endl;
    Student student;
    student.setID(sID);
    while (stree -> checkAdvisor(student, fID) == true) {
      cout << "The student still has this faculty registered as their advisor." << endl;
      cout << "Please select one of the below options" << endl;
      cout << "1 - Delete the student" << endl;
      cout << "2 - Assign a new faculty to the student" << endl;
      cin >> option;
      if (option == 1) {
        stree -> deleteRec (student);
      }
      else if (option == 2) {
        cout << "Please enter the new faculty ID you would like to assign to the student." << endl;
        cin >> newfID;
        while (facultycheckID(newfID) == false) {
          cout << "Please enter the correct ID of the faculty. The ID you entered is not in the database." << endl;
          cin >> newfID;
        }
        oldfID = stree -> changeFadvisor (student, newfID);
        Faculty faculty;
        faculty.setID(newfID);
        ftree -> addFadvisee (faculty, sID);
      }
    }
    cout << endl << "Thank you!"<< endl;
  }
}

void Simulation::rollback() {
     if(myStack -> empty() == true)
          cout << endl << "Unable to rollback. No edits made!" << endl << endl;
     else if(myStack -> top() == 0) {
          Student stu = sRollback -> front();
          if(stree -> contains(stu))
               stree -> deleteRec(stu);
          else
               stree -> insert(stu);
          sRollback -> removeFront();
          myStack -> pop();
     }
     else {
          Faculty fac = fRollback -> front();
          if(ftree -> contains(fac))
               ftree -> deleteRec(fac);
          else
               ftree -> insert(fac);
          fRollback -> removeFront();
          myStack -> pop();
     }
}
