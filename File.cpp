#include "File.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

File::File() {
  line = "";
  rows = 5;
  cols = 5;
  density = 0.5f;
  Grid* current = new Grid(rows, cols);
  Grid* future = new Grid(rows, cols);
  generation = 0;
}

File::File(int rw, int cl, float dn) {
  line = "";
  rows = rw;
  cols = cl;
  density = dn;
  Grid* current = new Grid(rows, cols); // grid of the current generation
  Grid* future = new Grid(rows, cols); // grid of the next generation
  generation = 0; // generation number
  srand(static_cast <unsigned> (time(0)));
  float random = 0;
  for(int i = 0; i < rows; ++i) {
    for(int j = 0; j < cols; ++j) {
      random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // generate random number [0,1]
      if(random < density) {
        current->setCell(i, j, false);
        future->setCell(i, j, false);
      } else {
        current->setCell(i, j, true);
        future->setCell(i, j, true);
      }
    }
  }
}

File::File(string filename) {
  density = 0.0f;
  generation = 0;
  line = ""; // string to read in configuration
  ifstream filein (filename);
  string str_rows; // string to read in number of rows
  getline(filein, str_rows);
  stringstream rowsin(str_rows);
  rowsin >> rows; // insert string into int
  string str_cols; // string to read in number of columns
  getline(filein, str_cols);
  stringstream colsin(str_cols);
  colsin >> cols; // insert string into int
  Grid* current = new Grid(rows, cols); // grid of the current generation
  Grid* future = new Grid(rows, cols); // grid of the next generation
  filein.close();
  readFromFile(filename); // advance to read in configuration
}

File::~File() {

}

void File::readFromFile(string filename) {
  int lineCount = 0; // count number of lines
  ifstream instream (filename);
  if(instream.is_open()) {
    while(getline(instream, line)) {
      if(lineCount > 1) {
        char c = '\0'; // character to read in from each line
        for(int j = 0; j < line.size(); ++j) {
          c = line[j];
          if(c == '-') {
            current->setCell(lineCount, j, false); // cell dead if character is '-'
          } else {
            current->setCell(lineCount, j, true); // cell alive if character is 'X'
          }
        }
      }
      ++lineCount;
    }
    instream.close();
  }
}

bool File::nextGen() { // calculate the next generation, standard mode
  int numNeighbors = 0; // count number of neighbors
  for(int i = 0; i < rows; ++i) {
    for(int j = 0; j < cols; ++j) {
      numNeighbors = current->neighbors(i, j); // call method from grid
      if(numNeighbors < 2) {
        future->setCell(i, j, false); // dies of loneliness
      } else if(numNeighbors < 3) {
        future->setCell(i, j, current->getCell(i, j)); // stable
      } else if(numNeighbors < 4) {
        future->setCell(i, j, true); // new birth
      } else {
        future->setCell(i, j, false); // dies of overcrowding
      }
    }
  }
  if(gridEmpty() || gridStable()) { // if grid empty or stable, exit
    return true;
  } else {
    current->copyGrid(future); // copy future grid into current grid
    return false;
  }
}

bool File::nextVainGen() { // calculate the next generation, mirror mode
  int numNeighbors = 0; // count number of neighbors
  for(int i = 0; i < rows; ++i) {
    for(int j = 0; j < cols; ++j) {
      numNeighbors = current->vainNeighbors(i, j); // call method from grid
      if(numNeighbors < 2) {
        future->setCell(i, j, false); // dies of loneliness
      } else if(numNeighbors < 3) {
        future->setCell(i, j, current->getCell(i, j)); // stable
      } else if(numNeighbors < 4) {
        future->setCell(i, j, true); // new birth
      } else {
        future->setCell(i, j, false); // dies of overcrowding
      }
    }
  }
  if(gridEmpty() || gridStable()) { // if grid empty or stable, exit
    return true;
  } else {
    current->copyGrid(future); // copy future grid into current grid
    return false;
  }
}

bool File::nextFatGen() { // calculate the next generation, donut mode
  int numNeighbors = 0; // count number of neighbors
  for(int i = 0; i < rows; ++i) {
    for(int j = 0; j < cols; ++j) {
      numNeighbors = current->fatNeighbors(i, j); // call method from grid
      if(numNeighbors < 2) {
        future->setCell(i, j, false); // dies of loneliness
      } else if(numNeighbors < 3) {
        future->setCell(i, j, current->getCell(i, j)); // stable
      } else if(numNeighbors < 4) {
        future->setCell(i, j, true); // new birth
      } else {
        future->setCell(i, j, false); // dies of overcrowding
      }
    }
  }
  if(gridEmpty() || gridStable()) { // if grid empty or stable, exit
    return true;
  } else {
    current->copyGrid(future); // copy future grid into current grid
    return false;
  }
}

bool File::gridEmpty() {
  bool empty = true;
  for(int i = 0; i < rows; ++i) {
    for(int j = 0; j < cols; ++j) {
      if(future->getCell(i, j)) { // grid is not empty if cell is alive
        empty = false;
        goto EMPTYRETURN;
      }
    }
  }
  EMPTYRETURN: return empty;
}

bool File::gridStable() {
  bool stable = true;
  for(int i = 0; i < rows; ++i) {
    for(int j = 0; j < cols; ++j) {
      if(current->getCell(i, j) != future->getCell(i, j)) { // grid is not stable if cell changed in this generation
        stable = false;
        goto STABLERETURN;
      }
    }
  }
  STABLERETURN: return stable;
}

void File::printToCout(bool pause) { // print grid to standard out
  current->printGrid(pause, generation); // true to wait for input, false to sleep
}

void File::printToFile(string filename) { // print grid to file
  current->printGridToFile(filename, generation);
}
