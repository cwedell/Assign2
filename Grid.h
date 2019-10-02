#include <iostream>
#include <fstream>

using namespace std;

class Grid {
public:
  Grid();
  Grid(int x, int y); // x = rows, y = columns
  ~Grid();
  void copyGrid(Grid* g); // copy constructor
  bool getCell(int x, int y);
  void setCell(int x, int y, bool b);
  int neighbors(int x, int y); // neighbors for standard mode
  int vainNeighbors(int x, int y); // neighbors for mirror mode
  int fatNeighbors(int x, int y); // neighbors for donut mode
  void printGrid(bool pause, int gen); // print grid to standard out
  void printGridToFile(string filename, int gen); // print grid to file
private:
  int rows;
  int cols;
  bool **grid;
};
