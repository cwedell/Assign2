#include "GameOfLifeDriver.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

int main(int argc, char** argv) {
  int numRows;
  int numCols;
  float density;
  string filein;
  string fileout;
  int inputConfig;
  int gameMode;
  int outputType;
  cout << "Welcome to the Game of Life!" << endl;
  cout << "How do you want to set up your initial configuration?" << endl;
  cout << "1 - from file" << endl;
  cout << "2 - random" << endl;
  cout << "Enter the number of your choice: ";
  bool validInputConfig = false;
  while(!validInputConfig) {
    try {
      cin >> inputConfig;
      if(inputConfig < 1 || inputConfig > 2) { // inputConfig must be 1 or 2
        throw invalid_argument("Invalid option");
      }
      validInputConfig = true;
      break;
    } catch(exception& e) {
      cout << "Please enter a valid option: ";
    }
  }
  if(inputConfig == 1) { // configuration from file
    cout << "Please enter the file name: ";
    bool validFileIn = false;
    while(!validFileIn) {
      try {
        cin >> filein;
        ifstream fileintest (filein);
        if(!fileintest.good()) { // file must exist in current directory
          cout << "File does not exist." << endl;
          throw invalid_argument("File does not exist");
        }
        string strTest; // checking validity of file formatting
        int rowTest; // checking row number
        getline(fileintest, strTest);
        stringstream intTest(strTest);
        intTest >> rowTest;
        if(intTest.fail()) { // first line must be row number
          cout << "Dimensions not found in first line." << endl;
          throw invalid_argument("Dimensions not found");
        }
        int colTest; // checking column number
        getline(fileintest, strTest);
        stringstream intTest2(strTest);
        intTest2 >> colTest;
        if(intTest2.fail()) { // second line must be column number
          cout << "Dimensions not found in second line." << endl;
          throw invalid_argument("Dimensions not found");
        }
        int lineChecker = 1; // count number of lines in configuration
        while(getline(fileintest, strTest)) {
          if((strTest.length() - 1) != colTest) { // number of columns in row must match
            cout << "Incorrect number of columns in row " << lineChecker << "." << endl;
            throw invalid_argument("Incorrect file format");
          }
          if(strTest != " " && strTest != "\n" && strTest != "\t" && strTest != "\r") {
            ++lineChecker; // check for non-whitespace line
          }
          string charToStr; // check characters for non-compatibility
          for(int i = 0; i < (strTest.length() - 1); ++i) {
            charToStr = strTest[i];
            if(charToStr != "-" && charToStr != "X") { // characters must be either '-' or 'X'
              cout << "Text error in grid." << endl;
              throw invalid_argument("Incorrect file format");
            }
          }
        }
        if((lineChecker - 1) != rowTest) { // number of rows in file must match
          cout << "Incorrect number of rows." << endl;
          throw invalid_argument("Incorrect file format");
        }
        validFileIn = true;
        break;
      } catch(exception& e) {
        cout << "Please enter a valid file name in the current directory: ";
      }
    }
  } else { // random configuration
    cout << "Please enter the desired number of rows: ";
    bool validNumRows = false;
    while(!validNumRows) {
      try {
        cin >> numRows;
        if(numRows < 1) { // number of rows must be positive
          throw invalid_argument("Positive integer required");
        }
        validNumRows = true;
        break;
      } catch(exception& e) {
        cout << "Please enter a valid non-negative integer: ";
      }
    }
    cout << "Please enter the desired number of columns: ";
    bool validNumCols = false;
    while(!validNumCols) {
      try {
        cin >> numCols;
        if(numCols < 1) { // number of columns must be positive
          throw invalid_argument("Positive integer required");
        }
        validNumCols = true;
        break;
      } catch(exception& e) {
        cout << "Please enter a valid non-negative integer: ";
      }
    }
    cout << "Please enter the density: ";
    bool validDensity = false;
    while(!validDensity) {
      try {
        cin >> density;
        if(density < 0.0f || density > 1.0f) { // density must be in [0,1]
          throw invalid_argument("Number between 0 and 1 required");
        }
        validDensity = true;
        break;
      } catch(exception& e) {
        cout << "Please enter a valid density between 0 and 1: ";
      }
    }
  }

  cout << "What game mode do you want to play?" << endl;
  cout << "1 - standard" << endl;
  cout << "2 - mirror" << endl;
  cout << "3 - donut" << endl;
  cout << "Enter the number of your choice: ";
  bool validGameMode = false;
  while(!validGameMode) {
    try {
      cin >> gameMode;
      if(gameMode < 1 || gameMode > 3) { // gameMode must be 1, 2, or 3
        throw invalid_argument("Invalid option");
      }
      validGameMode = true;
      break;
    } catch(exception& e) {
      cout << "Please enter a valid option: ";
    }
  }

  cout << "How do you want to view the output?" << endl;
  cout << "1 - print to standard out with pause" << endl;
  cout << "2 - print to standard out and wait for keystroke" << endl;
  cout << "3 - print to file" << endl;
  cout << "Enter the number of your choice: ";
  bool validOutputType = false;
  while(!validOutputType) {
    try {
      cin >> outputType;
      if(outputType < 1 || outputType > 3) { // outputType must be 1, 2, or 3
        throw invalid_argument("Invalid option");
      }
      validOutputType = true;
      break;
    } catch(exception& e) {
      cout << "Please enter a valid option: ";
    }
  }
  if(outputType == 3) {
    cout << "Please enter the file name: ";
    bool validFileOut = false;
    while(!validFileOut) {
      try {
        cin >> fileout;
        validFileOut = true;
        break;
      } catch(exception& e) {
        cout << "Please enter a valid file name: ";
      }
    }
  }

  GameOfLifeDriver game(numRows, numCols, density, filein, fileout, inputConfig, gameMode, outputType);
  while(!game.getGameOver()) {
    game.playGame(); // play the Game of Life!
  }

  cout << "Simulation complete. Press enter to exit." << endl;
  system("pause");
  cout << "Thank you for playing!" << endl;
}
