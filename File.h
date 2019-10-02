#include "Grid.h"
#include <iostream>
#include <fstream>

using namespace std;

class File {
public:
  File();
  File(int rw, int cl, float dn); // rw = rows, cl = columns, dn = density
  File(string filename); // filename opened to read configuration
  ~File();
  void readFromFile(string filename); // read configuration from file
  bool nextGen(); // calculate the next generation, standard mode
  bool nextVainGen(); // calculate the next generation, mirror mode
  bool nextFatGen(); // calculate the next generation, donut mode
  bool gridEmpty(); // checks for an empty grid
  bool gridStable(); // checks for a grid with no change from the previous generation
  void printToCout(bool pause); // print grid to standard out
  void printToFile(string filename); // print grid to file
private:
  string line;
  int rows;
  int cols;
  float density;
  Grid* current;
  Grid* future;
  int generation;
};
