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
using namespace std;

int main () {
  Simulation database;
  database.simulate();
}
