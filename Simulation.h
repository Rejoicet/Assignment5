#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Simulation {
public:
  Simulation();
  ~Simulation();
  void simulate();
  void promptUser();
  bool isValid(string newString, int indic);
  void createStudent();
  void createFaculty();

  bool studentcheckID (unsigned int cID);
  bool facultycheckID (unsigned int cID);
  void sdelete();
  void fdelete();
  void sinfo(unsigned int sID);
  void finfo(unsigned int fID);
  void facInfo();
  //void stuInfo();

private:
  int choice, input, j;
  ifstream studentFile;
  ifstream facultyFile;

  unsigned int sID, fID, a, b, c, number;
  string nam, lev, maj, dep, line;
  double GP;
  char ch;

  BST<Student> *stree;
  BST<Faculty> *ftree;
};
