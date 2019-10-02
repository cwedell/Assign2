#include "Grid.h"
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

Grid::Grid() {
  rows = 5;
  cols = 5;
  grid = new bool *[rows];
  for(int i = 0; i < rows; ++i) {
    grid[i] = new bool[cols];
    for(int j = 0; j < cols; ++j) {
      grid[i][j] = false;
    }
  }
}

Grid::Grid(int x, int y) {
  rows = x;
  cols = y;
  grid = new bool *[rows];
  for(int i = 0; i < rows; ++i) {
    grid[i] = new bool[cols];
    for(int j = 0; j < cols; ++j) {
      grid[i][j] = false; // initialize grid
    }
  }
}

Grid::~Grid() {
  for(int i = 0; i < rows; ++i) {
    delete[] grid[i];
  }
  delete[] grid;
}

void Grid::copyGrid(Grid* g) { // copy constructor
  for(int i = 0; i < rows; ++i) {
    for(int j = 0; j < cols; ++j) {
      grid[i][j] = g->getCell(i, j);
    }
  }
}

bool Grid::getCell(int x, int y) {
  return grid[x][y];
}

void Grid::setCell(int x, int y, bool b) {
  grid[x][y] = b;
}

int Grid::neighbors(int x, int y) { // count neighboring cells, standard mode
  int count = 0;
  if(x > 0) { // count cells to the left, assuming column != 0
    if(getCell(x - 1, y)) {
      ++count;
    }
    if(y > 0) {
      if(getCell(x - 1, y - 1)) {
        ++count;
      }
    }
    if(y < cols) {
      if(getCell(x - 1, y + 1)) {
        ++count;
      }
    }
  }
  if(x < rows) { // count cells to the right, assuming column != max-row
    if(getCell(x + 1, y)) {
      ++count;
    }
    if(y > 0) {
      if(getCell(x + 1, y - 1)) {
        ++count;
      }
    }
    if(y < cols) {
      if(getCell(x + 1, y + 1)) {
        ++count;
      }
    }
  }
  if(y > 0) { // count cells to the top, assuming row != 0
    if(getCell(x, y - 1)) {
      ++count;
    }
  }
  if(y < cols) { // count cells to the bottom, assuming row != max-column
    if(getCell(x, y + 1)) {
      ++count;
    }
  }
  return count;
}

int Grid::vainNeighbors(int x, int y) { // count neighboring cells, mirror mode
  int count = 0;

  if((x == 0 && y == 0) || (x == 0 && y == cols) || (x == rows && y == 0) || (x == rows && y == cols)) {
    count += 3; // add 3 to count if cell is in corner
  } else if(x == 0 || x == rows) {
    ++count; // add 1 to count if cell is on horizontal edge
  } else if(y == 0 || y == cols) {
    ++count; // add 1 to count if cell is on vertical edge
  }

  if(x > 0) { // same counting logic as in standard mode
    if(getCell(x - 1, y)) {
      ++count;
    }
    if(y > 0) {
      if(getCell(x - 1, y - 1)) {
        ++count;
      }
    }
    if(y < cols) {
      if(getCell(x - 1, y + 1)) {
        ++count;
      }
    }
  }
  if(x < rows) {
    if(getCell(x + 1, y)) {
      ++count;
    }
    if(y > 0) {
      if(getCell(x + 1, y - 1)) {
        ++count;
      }
    }
    if(y < cols) {
      if(getCell(x + 1, y + 1)) {
        ++count;
      }
    }
  }
  if(y > 0) {
    if(getCell(x, y - 1)) {
      ++count;
    }
  }
  if(y < cols) {
    if(getCell(x, y + 1)) {
      ++count;
    }
  }
  return count;
}

int Grid::fatNeighbors(int x, int y) { // count neighboring cells, donut mode
  int count = 0;

  if(x == 0) { // add 1 to count if cell is on horizontal edge and cell on opposite side is alive
    if(getCell(rows, y)) {
      ++count;
    }
  }
  if(x == rows) {
    if(getCell(0, y)) {
      ++count;
    }
  }
  if(y == 0) { // add 1 to count if cell is on vertical edge and cell on opposite side is alive
    if(getCell(x, cols)) {
      ++count;
    }
  }
  if(y == cols) {
    if(getCell(x, 0)) {
      ++count;
    }
  }

  if((x == 0) && (y == 0)) { // add 1 to count if cell is in corner and cell in opposite corner is alive
    if(getCell(rows, cols)) {
      ++count;
    }
  }
  if((x == 0) && (y == cols)) {
    if(getCell(rows, 0)) {
      ++count;
    }
  }
  if((x == rows) && (y == 0)) {
    if(getCell(0, cols)) {
      ++count;
    }
  }
  if((x == rows) && (y == cols)) {
    if(getCell(0, 0)) {
      ++count;
    }
  }

  if(x > 0) { // same counting logic as in standard mode
    if(getCell(x - 1, y)) {
      ++count;
    }
    if(y > 0) {
      if(getCell(x - 1, y - 1)) {
        ++count;
      }
    }
    if(y < cols) {
      if(getCell(x - 1, y + 1)) {
        ++count;
      }
    }
  }
  if(x < rows) {
    if(getCell(x + 1, y)) {
      ++count;
    }
    if(y > 0) {
      if(getCell(x + 1, y - 1)) {
        ++count;
      }
    }
    if(y < cols) {
      if(getCell(x + 1, y + 1)) {
        ++count;
      }
    }
  }
  if(y > 0) {
    if(getCell(x, y - 1)) {
      ++count;
    }
  }
  if(y < cols) {
    if(getCell(x, y + 1)) {
      ++count;
    }
  }
  return count;
}

void Grid::printGrid(bool pause, int gen) { // print grid to standard out
  cout << gen << endl; // generation number
  for(int i = 0; i < rows; ++i) {
    for(int j = 0; j < cols; ++j) {
      if(getCell(i, j)) {
        cout << "X ";
      } else {
        cout << "- ";
      }
    }
    cout << endl;
    if(pause) {
      system("pause"); // wait for user keystroke
    } else {
      usleep(250000); // this value is in millionths of seconds
    }
  }
}

void Grid::printGridToFile(string filename, int gen) { // print grid to file
  ofstream outstream (filename, fstream::app); // open ofstream to append to file
  outstream << gen << endl; // generation number
  for(int i = 0; i < rows; ++i) {
    for(int j = 0; j < cols; ++j) {
      if(getCell(i, j)) {
        outstream << "X ";
      } else {
        outstream << "- ";
      }
    }
    outstream << endl;
  }
  outstream.close();
}
