#include "File.h"
#include <iostream>

using namespace std;

class GameOfLifeDriver {
public:
  GameOfLifeDriver();
  GameOfLifeDriver(int rw, int cl, float dn, string infile, string outfile, int in, int gm, int out);
  ~GameOfLifeDriver();
  bool getGameOver();
  void setGameOver(bool b);
  int getInputConfig();
  void setInputConfig(int in);
  int getGameMode();
  void setGameMode(int gm);
  int getOutputType();
  void setOutputType(int out);
  void playGame();
private:
  int rows;
  int cols;
  float density;
  string filein;
  string fileout;
  bool gameOver;
  int inputConfig;
  int gameMode;
  int outputType;
};
