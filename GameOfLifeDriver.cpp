#include "GameOfLifeDriver.h"
#include <iostream>

using namespace std;

GameOfLifeDriver::GameOfLifeDriver() {
  rows = 5;
  cols = 5;
  density = 0.5f;
  filein = "";
  fileout = "";
  gameOver = false;
  inputConfig = 0;
  gameMode = 0;
  outputType = 0;
}

GameOfLifeDriver::GameOfLifeDriver(int rw, int cl, float dn, string infile, string outfile, int in, int gm, int out) {
  rows = rw; // number of rows
  cols = cl; // number of columns
  density = dn;
  filein = infile; // file to read configuration from
  fileout = outfile; // file to print results to
  gameOver = false; // check if game is over
  inputConfig = in; // 1 from file, 2 random
  gameMode = gm; // 1 standard, 2 mirror, 3 donut
  outputType = out; // 1 pause, 2 user input, 3 to file
}

GameOfLifeDriver::~GameOfLifeDriver() {

}

bool GameOfLifeDriver::getGameOver() {
  return gameOver;
}

void GameOfLifeDriver::setGameOver(bool b) {
  gameOver = b;
}

int GameOfLifeDriver::getInputConfig() {
  return inputConfig;
}

void GameOfLifeDriver::setInputConfig(int in) {
  inputConfig = in;
}

int GameOfLifeDriver::getGameMode() {
  return gameMode;
}

void GameOfLifeDriver::setGameMode(int gm) {
  gameMode = gm;
}

int GameOfLifeDriver::getOutputType() {
  return outputType;
}

void GameOfLifeDriver::setOutputType(int out) {
  outputType = out;
}

void GameOfLifeDriver::playGame() {
  File f;
  if(inputConfig == 1) { // read from file
    f = File(filein);
    f.readFromFile(filein);
  } else { // random configuration
    f = File(rows, cols, density);
  }
  if(outputType == 1) { // print to standard out with pause
    if(gameMode == 1) { // standard mode
      while(!gameOver) {
        if(f.nextGen()) { // returns true if grid empty or stable
          gameOver = true;
          break;
        }
        f.printToCout(false); // print to standard out with pause
      }
    } else if(gameMode == 2) { // mirror mode
      while(!gameOver) {
        if(f.nextVainGen()) { // returns true if grid empty or stable
          gameOver = true;
          break;
        }
        f.printToCout(false); // print to standard out with pause
      }
    } else { // donut mode
      while(!gameOver) {
        if(f.nextFatGen()) { // returns true if grid empty or stable
          gameOver = true;
          break;
        }
        f.printToCout(false); // print to standard out with pause
      }
    }
  } else if(outputType == 2) { // print to standard out, wait for keystroke
    if(gameMode == 1) { // standard mode
      while(!gameOver) {
        if(f.nextGen()) { // returns true if grid empty or stable
          gameOver = true;
          break;
        }
        f.printToCout(true); // print to standard out, wait for keystroke
      }
    } else if(gameMode == 2) { // mirror mode
      while(!gameOver) {
        if(f.nextVainGen()) { // returns true if grid empty or stable
          gameOver = true;
          break;
        }
        f.printToCout(true); // print to standard out, wait for keystroke
      }
    } else { // donut mode
      while(!gameOver) {
        if(f.nextFatGen()) { // returns true if grid empty or stable
          gameOver = true;
          break;
        }
        f.printToCout(true); // print to standard out, wait for keystroke
      }
    }
  } else {
    if(gameMode == 1) { // standard mode
      while(!gameOver) {
        if(f.nextGen()) { // returns true if grid empty or stable
          gameOver = true;
          break;
        }
        f.printToFile(fileout); // print to file
      }
    } else if(gameMode == 2) { // mirror mode
      while(!gameOver) {
        if(f.nextVainGen()) { // returns true if grid empty or stable
          gameOver = true;
          break;
        }
        f.printToFile(fileout); // print to file
      }
    } else { // donut mode
      while(!gameOver) {
        if(f.nextFatGen()) { // returns true if grid empty or stable
          gameOver = true;
          break;
        }
        f.printToFile(fileout); // print to file
      }
    }
  }
}
